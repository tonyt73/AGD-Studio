//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "GraphicsBuffers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Pixel Masks
const unsigned char g_PixelMask1[1] = { 0xFF };
const unsigned char g_PixelMask2[2] = { 0xF0, 0x0F };
const unsigned char g_PixelMask4[4] = { 0xC0, 0x30, 0x0C, 0x03 };
const unsigned char g_PixelMask8[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
const unsigned char g_PixelShft1[1] = { 0 };
const unsigned char g_PixelShft2[2] = { 4, 0 };
const unsigned char g_PixelShft4[4] = { 6, 4, 2, 0 };
const unsigned char g_PixelShft8[8] = { 7, 6, 5, 4, 3, 2, 1, 0 };
// Pixel Masks for 1, 2, 4 and 8 pixels per byte
const unsigned char* g_PixelMasks[9] = { NULL, g_PixelMask1, g_PixelMask2, NULL, g_PixelMask4, NULL, NULL, NULL, g_PixelMask8 };
const unsigned char* g_PixelShfts[9] = { NULL, g_PixelShft1, g_PixelShft2, NULL, g_PixelShft4, NULL, NULL, NULL, g_PixelShft8 };
using namespace Agdx;
//---------------------------------------------------------------------------
__fastcall GraphicsBuffer::GraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode)
: m_GraphicsMode(mode)
, m_BufferType(mode.TypeOfBuffer)
, m_Width(width)
, m_Height(height)
, m_Stride(width / (8 / mode.BitsPerPixel))
, m_PixelsPerByte(8 / mode.BitsPerPixel)
{
    assert(width > 0 && width % 2 == 0);
    assert(height > 0 && height % 2 == 0);
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
unsigned char __fastcall GraphicsBuffer::GetColorIndex(ColorIndex index) const
{
    return m_SetColors[index % 2];
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::SetColorIndex(ColorIndex index, int colorIndex)
{
    m_SetColors[index % 2] = colorIndex;
}
//---------------------------------------------------------------------------
void __fastcall GraphicsBuffer::GetBuffer(int index, ByteBuffer& buffer) const
{
    if (index < m_Buffers.size())
    {
        buffer.assign(m_Buffers[index].begin(), m_Buffers[index].end());
    }
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
__fastcall BitmapGraphicsBuffer::BitmapGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode)
: GraphicsBuffer(width, height, mode)
{
    assert(mode.BitsPerPixel != 1 && mode.BitsPerPixel != 2 && mode.BitsPerPixel != 4 && mode.BitsPerPixel != 8);
    // allocate the buffer
    // m_Buffers[0] : pixels buffer
    PushBuffer(m_Stride * height);
}
//---------------------------------------------------------------------------
__fastcall BitmapGraphicsBuffer::~BitmapGraphicsBuffer()
{
}
//---------------------------------------------------------------------------
void __fastcall BitmapGraphicsBuffer::SetPixel(unsigned int X, unsigned int Y, bool set)
{
    if (0 < X && X < m_Width && 0 < Y && Y < m_Height)
    {
        auto ix = X / m_PixelsPerByte;
        auto pixelOffset = (Y * m_Stride) + ix;
        auto pixelPos = ix % m_PixelsPerByte;
        auto pixel = m_SetColors[set ? 0 : 1] << g_PixelShfts[m_GraphicsMode.BitsPerPixel][pixelPos];
        // reset the pixel bits
        m_Buffers[0][pixelOffset] &= ~g_PixelMasks[m_GraphicsMode.BitsPerPixel][pixelPos];
        // set the new color
        m_Buffers[0][pixelOffset] |= pixel;
    }
}
//---------------------------------------------------------------------------
void __fastcall BitmapGraphicsBuffer::GetColor(unsigned int X, unsigned int Y, ColorIndex colorIndex)
{
    if (0 < X && X < m_Width && 0 < Y && Y < m_Height)
    {
        auto ix = X / m_PixelsPerByte;
        auto pixelOffset = (Y * m_Stride) + ix;
        auto pixelPos = ix % m_PixelsPerByte;
        // get the color index at the position in the byte
        auto color = m_Buffers[0][pixelOffset] & ~g_PixelMasks[m_GraphicsMode.BitsPerPixel][pixelPos];
        // shift down into a color index
        color >>= g_PixelShfts[m_GraphicsMode.BitsPerPixel][pixelPos];
        m_SetColors[colorIndex] = color;
    }
}
//---------------------------------------------------------------------------
void __fastcall BitmapGraphicsBuffer::Render(TBitmap* bitmap, bool inGreyscale) const
{
    bitmap->PixelFormat = pf32bit;
    bitmap->Width = m_Width;
    bitmap->Height = m_Height;
    for (auto y = 0; y < m_Height; y++)
    {
        for (auto x = 0; x < m_Width; x += m_PixelsPerByte)
        {
            auto ix = x / m_PixelsPerByte;
            auto pixels = m_Buffers[0][(y * m_Stride) + ix];
            for (auto i = 0; i < m_PixelsPerByte; i++)
            {
                auto color = (pixels & g_PixelMasks[m_GraphicsMode.BitsPerPixel][i]) >> g_PixelShfts[m_GraphicsMode.BitsPerPixel][i];
                bitmap->Canvas->Pixels[x+i][y] = inGreyscale ? m_GraphicsMode.Palette().Greyscale[color] : m_GraphicsMode.Palette().Color[color];
            }
        }
    }
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
const unsigned char g_Transparent =    8; // attribute is transparent
const unsigned char g_InkMask     = 0x07; // ink bits from attribute byte
const unsigned char g_PaperMask   = 0x38; // paper bits from attribute byte
const unsigned char g_BrightMask  = 0x40; // bright bit from attribute byte
const unsigned char g_FlashMask   = 0x80; // flash bit from attribute byte
const unsigned char g_PaperShift  = 3;
//---------------------------------------------------------------------------
__fastcall AttributeGraphicsBuffer::AttributeGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode)
: GraphicsBuffer(width, height, mode)
{
    assert(mode.BitsPerPixel != 1);
    assert(mode.PixelsHighPerAttribute != 1 && mode.PixelsHighPerAttribute != 8);
    // allocate the buffers
    // m_Buffers[0] : pixels buffer
    PushBuffer(m_Stride * height);
    // m_Buffers[1] : attributes buffer
    PushBuffer(m_Stride * (height / m_GraphicsMode.PixelsHighPerAttribute));
}
//---------------------------------------------------------------------------
__fastcall AttributeGraphicsBuffer::~AttributeGraphicsBuffer()
{
}
//---------------------------------------------------------------------------
void __fastcall AttributeGraphicsBuffer::SetPixel(unsigned int X, unsigned int Y, bool set)
{
    if (0 < X && X < m_Width && 0 < Y && Y < m_Height)
    {
        auto ix = X / m_PixelsPerByte;
        auto pixelOffset = (Y * m_Stride) + ix;
        auto pixelPos = ix % m_PixelsPerByte;
        // reset
        auto pixel = m_Buffers[0][pixelOffset] & ~g_PixelMasks[m_GraphicsMode.BitsPerPixel][pixelPos];
        if (set)
        {
            pixel |= g_PixelMasks[m_GraphicsMode.BitsPerPixel][pixelPos];
        }
        m_Buffers[0][pixelOffset] = pixel;
    }
}
//---------------------------------------------------------------------------
void __fastcall AttributeGraphicsBuffer::GetColor(unsigned int X, unsigned int Y, ColorIndex colorIndex)
{
    if (0 < X && X < m_Width && 0 < Y && Y < m_Height)
    {
        auto ix = X / m_PixelsPerByte;
        auto iy = Y / m_GraphicsMode.PixelsHighPerAttribute;
        auto attrOffset = (iy * m_Stride) + ix;
        auto color = m_Buffers[1][attrOffset];
        m_SetColors[colorIndex] = (colorIndex == ciPrimary ? (color & g_InkMask) : ((color & g_PaperMask) >> g_PaperShift)) + (color & g_BrightMask ? 8 : 0);
    }
}
//---------------------------------------------------------------------------
void __fastcall AttributeGraphicsBuffer::Render(TBitmap* bitmap, bool inGreyscale) const
{
    bitmap->PixelFormat = pf32bit;
    bitmap->Width = m_Width;
    bitmap->Height = m_Height;
    for (auto y = 0; y < m_Height; y += m_GraphicsMode.PixelsHighPerAttribute)
    {
        for (auto x = 0; x < m_Width; x += 8)
        {
            auto ix = x >> 3;
            auto attr = m_Buffers[1][((y >> 3) * m_Stride) + ix];
            auto bright =  (attr & g_BrightMask) ? 8 : 0;
            auto ink    = ((attr & g_InkMask   )     ) + bright;
            auto paper  = ((attr & g_PaperMask ) >> 3) + bright;
            auto cInk   = inGreyscale ? clWhite : m_GraphicsMode.Palette().Color[ink];
            auto cPaper = inGreyscale ? clBlack : m_GraphicsMode.Palette().Color[ink];
            for (auto i = 0; i < m_GraphicsMode.PixelsHighPerAttribute; i++)
            {
                auto pixels = m_Buffers[0][((y + i) * m_Stride) + ix];
                auto masks = g_PixelMasks[m_GraphicsMode.BitsPerPixel];
                bitmap->Canvas->Pixels[x+0][y+i] = (pixels & masks[0]) ? cInk : cPaper;
                bitmap->Canvas->Pixels[x+1][y+i] = (pixels & masks[1]) ? cInk : cPaper;
                bitmap->Canvas->Pixels[x+2][y+i] = (pixels & masks[2]) ? cInk : cPaper;
                bitmap->Canvas->Pixels[x+3][y+i] = (pixels & masks[3]) ? cInk : cPaper;
                bitmap->Canvas->Pixels[x+4][y+i] = (pixels & masks[4]) ? cInk : cPaper;
                bitmap->Canvas->Pixels[x+5][y+i] = (pixels & masks[5]) ? cInk : cPaper;
                bitmap->Canvas->Pixels[x+6][y+i] = (pixels & masks[6]) ? cInk : cPaper;
                bitmap->Canvas->Pixels[x+7][y+i] = (pixels & masks[7]) ? cInk : cPaper;
            }
        }
    }
}
//---------------------------------------------------------------------------

