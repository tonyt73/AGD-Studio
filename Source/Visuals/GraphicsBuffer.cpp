//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "GraphicsBuffer.h"
#include "AttributeGraphicsBuffer.h"
#include "BitmapGraphicsBuffer.h"
#include "ULAPlusGraphicsBuffer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Visuals;
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
const unsigned char* g_PixelMasks[9] = { nullptr, g_PixelMask1, g_PixelMask2, nullptr, g_PixelMask4, nullptr, nullptr, nullptr, g_PixelMask8 };
const unsigned char* g_PixelShfts[9] = { nullptr, g_PixelShft1, g_PixelShft2, nullptr, g_PixelShft4, nullptr, nullptr, nullptr, g_PixelShft8 };
//---------------------------------------------------------------------------
GraphicsBuffer::GraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode)
: m_GraphicsMode(mode)
, m_Width(width)
, m_Height(height)
, m_ScalarX(mode.ScalarX)
, m_ScalarY(mode.ScalarY)
, m_Stride(width / (8 / mode.BitsPerPixel))
, m_PixelsPerByte(8 / mode.BitsPerPixel)
, m_BufferType(mode.TypeOfBuffer)
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
GraphicsBuffer::~GraphicsBuffer()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void GraphicsBuffer::Make(unsigned int width, unsigned int height, const GraphicsMode& mode, std::unique_ptr<GraphicsBuffer>& buffer)
{
    buffer = nullptr;
    switch (mode.TypeOfBuffer) {
    case btBitmap:      buffer = std::make_unique<BitmapGraphicsBuffer>(width, height, mode);   break;
    case btAttribute:   buffer = std::make_unique<AttributeGraphicsBuffer>(width, height, mode);break;
    case btULAplus:     buffer = std::make_unique<ULAPlusGraphicsBuffer>(width, height, mode);  break;
    case btCharacterMap: break;
    case btInvalid: assert(0); break;
    }
}
//---------------------------------------------------------------------------
void GraphicsBuffer::PushBuffer(unsigned int size)
{
    m_Buffers.push_back(ByteBuffer(size, 0));
}
//---------------------------------------------------------------------------
unsigned int GraphicsBuffer::GetNumberOfBuffers() const
{
    return static_cast<unsigned int>(m_Buffers.size());
}
//---------------------------------------------------------------------------
unsigned int GraphicsBuffer::GetSizeOfBuffer(unsigned char index) const
{
    auto size = 0;
    if (index < m_Buffers.size()) {
        size = static_cast<unsigned int>(m_Buffers[index].size());
    }
    return size;
}
//---------------------------------------------------------------------------
unsigned char GraphicsBuffer::GetColorIndex(unsigned char index) const
{
    if (index < m_SetColors.size()) {
        return m_SetColors[index];
    }
    return 0;
}
//---------------------------------------------------------------------------
void GraphicsBuffer::SetColorIndex(unsigned char index, unsigned char logicalIndex)
{
    if (index < m_SetColors.size() && logicalIndex < m_GraphicsMode.LogicalColors) {
        m_SetColors[index] = logicalIndex;
    }
}
//---------------------------------------------------------------------------
void GraphicsBuffer::SetRenderInGreyscale(bool value)
{
    m_RenderInGreyscale = value;
    Render();
}
//---------------------------------------------------------------------------
void GraphicsBuffer::GetBuffer(unsigned char index, ByteBuffer& buffer) const
{
    if (index < m_Buffers.size()) {
        buffer.assign(m_Buffers[index].begin(), m_Buffers[index].end());
    }
}
//---------------------------------------------------------------------------
ByteBuffer GraphicsBuffer::GetNative(ImageTypes type, const TRect& rect) const
{
    ByteBuffer data;
    if (rect.Width() == 0 || rect.Height() == 0) {
        // get the entire set of buffers as required by the graphics mode configuration
        for (auto buffer = 0; buffer < m_Buffers.size(); buffer++) {
            if ((buffer == 0 && m_GraphicsMode.ExportInformation[type].BitmapDataOnly) || !m_GraphicsMode.ExportInformation[type].BitmapDataOnly) {
                for (const auto& byte : m_Buffers[buffer]) {
                    data.push_back(m_GraphicsMode.RemapPixels(byte));
                }
            }
        }
    } else {
        // extract a section of the graphics pixel buffer
        for (auto y = rect.Top; y < rect.Bottom; y++) {
            for (auto x = rect.Left; x < rect.Right; x += m_PixelsPerByte) {
                auto offset = (x / m_PixelsPerByte) + ((y * m_Width) / m_PixelsPerByte);
                auto byte = m_Buffers[0][offset];
                data.push_back(m_GraphicsMode.RemapPixels(byte));
            }
        }
        // if required, extract part of the attribute buffer
        if (m_Buffers.size() > 1 && m_BufferType == btAttribute && !m_GraphicsMode.ExportInformation[type].BitmapDataOnly) {
            for (int y = rect.Top; y < rect.Bottom; y += m_GraphicsMode.PixelsHighPerAttribute) {
                for (int x = rect.Left; x < rect.Right; x += m_PixelsPerByte) {
                    auto offset = (x / m_PixelsPerByte) + ((y * m_Width) / m_PixelsPerByte / m_GraphicsMode.PixelsHighPerAttribute);
                    auto byte = m_Buffers[1][offset];
                    data.push_back(byte);
                }
            }
        }
    }
    return data;
}
//---------------------------------------------------------------------------
String GraphicsBuffer::Get() const
{
    String data;
    for (const auto& buffer : m_Buffers) {
        for (const auto& byte : buffer) {
            data += IntToHex(byte, 2);
        }
    }
    return data;
}
//---------------------------------------------------------------------------
void GraphicsBuffer::Draw(TBitmap* bitmap, bool inMonochrome) const
{
    StretchBlt(bitmap->Canvas->Handle, 0, 0, bitmap->Width, bitmap->Height, m_Bitmap->Canvas->Handle, 0, 0, Width, Height, SRCCOPY);
    if (inMonochrome) {
        for (auto y = 0; y < bitmap->Height; y++) {
            auto sl = static_cast<TRGBA*>(bitmap->ScanLine[y]);
            for (auto x = 0; x < bitmap->Width; x++) {
                auto gray = static_cast<unsigned char>((0.299 * sl[x].R) + (0.587 * sl[x].G) + (0.114 * sl[x].B));
                sl[x].R = gray;
                sl[x].G = gray;
                sl[x].B = gray;
            }
        }
    }
}
//---------------------------------------------------------------------------
void GraphicsBuffer::Assign(TBitmap* bitmap) const
{
    bitmap->Assign(m_Bitmap.get());
}
//---------------------------------------------------------------------------
void GraphicsBuffer::Begin()
{
    m_Drawing = true;
}
//---------------------------------------------------------------------------
void GraphicsBuffer::End()
{
    m_Drawing = false;
    Render();
}
//---------------------------------------------------------------------------

