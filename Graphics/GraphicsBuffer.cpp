//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "GraphicsBuffer.h"
#include "AttributeGraphicsBuffer.h"
#include "BitmapGraphicsBuffer.h"
#include "ULAPlusGraphicsBuffer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Pixel Masks
const unsigned char g_PixelMask8[1] = { 0xFF };                                             // 8 bits per pixel
const unsigned char g_PixelMask4[2] = { 0xF0, 0x0F };                                       // 4 bits per pixel
const unsigned char g_PixelMask2[4] = { 0xC0, 0x30, 0x0C, 0x03 };                           // 2 bits per pixel
const unsigned char g_PixelMask1[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };   // 1 bit  per pixel
const unsigned char g_PixelShft8[1] = { 0 };
const unsigned char g_PixelShft4[2] = { 4, 0 };
const unsigned char g_PixelShft2[4] = { 6, 4, 2, 0 };
const unsigned char g_PixelShft1[8] = { 7, 6, 5, 4, 3, 2, 1, 0 };
// Pixel Masks for 1, 2, 4 and 8 pixels per byte
const unsigned char* g_PixelMasks[9] = { NULL, g_PixelMask1, g_PixelMask2, NULL, g_PixelMask4, NULL, NULL, NULL, g_PixelMask8 };
const unsigned char* g_PixelShfts[9] = { NULL, g_PixelShft1, g_PixelShft2, NULL, g_PixelShft4, NULL, NULL, NULL, g_PixelShft8 };
//---------------------------------------------------------------------------
using namespace Agdx;
//---------------------------------------------------------------------------
__fastcall GraphicsBuffer::GraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode)
: m_GraphicsMode(mode)
, m_BufferType(mode.TypeOfBuffer)
, m_Width(width)
, m_Height(height)
, m_ScalarX(mode.ScalarX)
, m_ScalarY(mode.ScalarY)
, m_Stride(width / (8 / mode.BitsPerPixel))
, m_PixelsPerByte(8 / mode.BitsPerPixel)
, m_RenderInGreyscale(false)
, m_Drawing(false)
{
    assert(width > 0 && width % 2 == 0);
    assert(height > 0 && height % 2 == 0);
    m_Bitmap = std::make_unique<Graphics::TBitmap>();
    m_Bitmap->Width = width;
    m_Bitmap->Height = height;
    m_Bitmap->PixelFormat = pf32bit;
    PatBlt(m_Bitmap->Canvas->Handle, 0, 0, width, height, BLACKNESS);
}
//---------------------------------------------------------------------------
__fastcall GraphicsBuffer::~GraphicsBuffer()
{
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::Make(unsigned int width, unsigned int height, const Agdx::GraphicsMode& mode, std::unique_ptr<GraphicsBuffer>& buffer)
{
    buffer = nullptr;
    switch (mode.TypeOfBuffer)
    {
        case btBitmap:      buffer = std::make_unique<BitmapGraphicsBuffer>(width, height, mode);   break;
        case btAttribute:   buffer = std::make_unique<AttributeGraphicsBuffer>(width, height, mode);break;
        case btULAplus:     buffer = std::make_unique<ULAPlusGraphicsBuffer>(width, height, mode);break;
        default: assert(0); break;
    }
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::PushBuffer(unsigned int size)
{
    m_Buffers.push_back(ByteBuffer(size, 0));
}
//---------------------------------------------------------------------------
unsigned int __fastcall GraphicsBuffer::GetNumberOfBuffers() const
{
    return m_Buffers.size();
}
//---------------------------------------------------------------------------
unsigned int __fastcall GraphicsBuffer::GetSizeOfBuffer(int index) const
{
    auto size = 0;
    if (0 <= index && index < m_Buffers.size())
    {
        size = m_Buffers[index].size();
    }
    return size;
}
//---------------------------------------------------------------------------
unsigned char __fastcall GraphicsBuffer::GetColorIndex(unsigned char index) const
{
    if (0 <= index && index < m_SetColors.size())
    {
        return m_SetColors[index];
    }
    return 0;
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::SetColorIndex(unsigned char index, int logicalIndex)
{
    if (0 <= index && index < m_SetColors.size() && 0 <= logicalIndex && logicalIndex < m_GraphicsMode.LogicalColors)
    {
        m_SetColors[index] = logicalIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::SetRenderInGreyscale(bool value)
{
    m_RenderInGreyscale = value;
    Render();
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::GetBuffer(int index, ByteBuffer& buffer) const
{
    if (0 <= index && index < m_Buffers.size())
    {
        buffer.assign(m_Buffers[index].begin(), m_Buffers[index].end());
    }
}
//---------------------------------------------------------------------------
std::vector<unsigned char> __fastcall GraphicsBuffer::GetNative(ImageTypes type) const
{
    std::vector<unsigned char> data;
    for (auto buffer = 0; buffer < m_Buffers.size(); buffer++)
    {
        if ((buffer == 0 && m_GraphicsMode.ExportInformation[type].BitmapDataOnly) || !m_GraphicsMode.ExportInformation[type].BitmapDataOnly)
        {
            for (const auto& byte : m_Buffers[buffer])
            {
                data.push_back(m_GraphicsMode.RemapPixels(byte));
            }
        }
    }
    return data;
}
//---------------------------------------------------------------------------
String __fastcall GraphicsBuffer::Get() const
{
    String data;
    for (const auto& buffer : m_Buffers)
    {
        for (const auto& byte : buffer)
        {
            data += IntToHex(byte, 2);
        }
    }
    return data;
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::Draw(TBitmap* bitmap) const
{
    StretchBlt(bitmap->Canvas->Handle, 0, 0, bitmap->Width, bitmap->Height, m_Bitmap->Canvas->Handle, 0, 0, Width, Height, SRCCOPY);
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::Assign(TBitmap* bitmap) const
{
    bitmap->Assign(m_Bitmap.get());
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::Begin()
{
    m_Drawing = true;
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::End()
{
    m_Drawing = false;
    Render();
}
//---------------------------------------------------------------------------

