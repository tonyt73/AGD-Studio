//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Graphics/GraphicsTypes.h"
#include "Graphics/GraphicsMode.h"
#include "ULAPlusGraphicsBuffer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Agdx;
//---------------------------------------------------------------------------
//const unsigned char g_Transparent =    8; // attribute is transparent
const unsigned char g_InkMask     = 0x07; // ink bits from attribute byte
const unsigned char g_PaperMask   = 0x38; // paper bits from attribute byte
const unsigned char g_PaletteMask = 0xC0; // palette bits from attribute byte
const unsigned char g_PaperShift  =    3; // bits to shift paper color
const unsigned char g_PaletteShift=    6; // bits to shift palette index
//---------------------------------------------------------------------------
__fastcall ULAPlusGraphicsBuffer::ULAPlusGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode)
: GraphicsBuffer(width, height, mode)
{
    assert(mode.BitsPerPixel == 1);
    assert(mode.PixelsHighPerAttribute == 1 || mode.PixelsHighPerAttribute == 8);
    // allocate the buffers
    // m_Buffers[0] : pixels buffer
    PushBuffer(m_Stride * height);
    // m_Buffers[1] : attributes buffer
    PushBuffer(m_Stride * (height / m_GraphicsMode.PixelsHighPerAttribute));
    // color attributes
    m_SetColors.push_back(0);   // ink
    m_SetColors.push_back(7);   // paper
    m_SetColors.push_back(0);   // palette index

    m_Registrar.Subscribe<Event>(OnEvent);
}
//---------------------------------------------------------------------------
__fastcall ULAPlusGraphicsBuffer::~ULAPlusGraphicsBuffer()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void __fastcall ULAPlusGraphicsBuffer::SetPixel(unsigned int X, unsigned int Y, bool set)
{
    if (X < m_Width && Y < m_Height)
    {
        auto ix = X / m_PixelsPerByte;
        auto pixelOffset = (Y * m_Stride) + ix;
        auto pixelPos = X % m_PixelsPerByte;
        // reset pixel
        auto pixel = m_Buffers[0][pixelOffset] & ~g_PixelMasks[m_GraphicsMode.BitsPerPixel][pixelPos];
        if (set)
        {
            // set pixel
            pixel |= g_PixelMasks[m_GraphicsMode.BitsPerPixel][pixelPos];
        }
        m_Buffers[0][pixelOffset] = pixel;
        // set attribute
        ix = X >> 3;
        auto iy = Y / m_GraphicsMode.PixelsHighPerAttribute;
        auto attrOffset = (iy * m_Stride) + ix;
        auto ink     = m_SetColors[0];
        auto paper   = m_SetColors[1];
        auto palette = m_SetColors[2];
        // set the attribute
        auto attribute = ink | (paper << g_PaperShift) | (palette << g_PaletteShift);
        m_Buffers[1][attrOffset] = attribute;
        Render();
    }
}
//---------------------------------------------------------------------------
void __fastcall ULAPlusGraphicsBuffer::GetColor(unsigned int X, unsigned int Y, unsigned char colorIndex)
{
    if (X < m_Width && Y < m_Height)
    {
        auto ix = X >> 3;
        auto iy = Y / m_GraphicsMode.PixelsHighPerAttribute;
        auto attrOffset = (iy * m_Stride) + ix;
        auto color = m_Buffers[1][attrOffset];
        switch (colorIndex)
        {
            case 0: m_SetColors[0] =  color & g_InkMask;                        break;
            case 1: m_SetColors[1] = (color & g_PaperMask  ) >> g_PaperShift;   break;
            case 2: m_SetColors[2] = (color & g_PaletteMask) >> g_PaletteShift; break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ULAPlusGraphicsBuffer::Render() const
{
    if (m_Drawing) return;
    for (auto y = 0; y < m_Height; y += m_GraphicsMode.PixelsHighPerAttribute)
    {
        for (auto x = 0; x < m_Width; x += 8)
        {
            auto ix = x >> 3;
            auto attr = m_Buffers[1][((y / m_GraphicsMode.PixelsHighPerAttribute) * m_Stride) + ix];
            auto ink    =  attr & g_InkMask;
            auto paper  = (attr & g_PaperMask  ) >> g_PaperShift;
            auto palette= (attr & g_PaletteMask) >> g_PaletteShift;
            ink = m_GraphicsMode.FromLogicalColor[(palette * 16) + ink];
            paper = m_GraphicsMode.FromLogicalColor[(palette * 16) + 8 + paper];
            auto cInk   = m_RenderInGreyscale ? clWhite : m_GraphicsMode.Palette().Color[ink];
            auto cPaper = m_RenderInGreyscale ? clBlack : m_GraphicsMode.Palette().Color[paper];
            for (auto i = 0; i < m_GraphicsMode.PixelsHighPerAttribute; i++)
            {
                auto pixels = m_Buffers[0][((y + i) * m_Stride) + ix];
                auto masks = g_PixelMasks[m_GraphicsMode.BitsPerPixel];
                m_Bitmap->Canvas->Pixels[x+0][y+i] = (pixels & masks[0]) ? cInk : cPaper;
                m_Bitmap->Canvas->Pixels[x+1][y+i] = (pixels & masks[1]) ? cInk : cPaper;
                m_Bitmap->Canvas->Pixels[x+2][y+i] = (pixels & masks[2]) ? cInk : cPaper;
                m_Bitmap->Canvas->Pixels[x+3][y+i] = (pixels & masks[3]) ? cInk : cPaper;
                m_Bitmap->Canvas->Pixels[x+4][y+i] = (pixels & masks[4]) ? cInk : cPaper;
                m_Bitmap->Canvas->Pixels[x+5][y+i] = (pixels & masks[5]) ? cInk : cPaper;
                m_Bitmap->Canvas->Pixels[x+6][y+i] = (pixels & masks[6]) ? cInk : cPaper;
                m_Bitmap->Canvas->Pixels[x+7][y+i] = (pixels & masks[7]) ? cInk : cPaper;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ULAPlusGraphicsBuffer::Set(const String& data)
{
    auto size = data.Length() / 2;
    if (size == (SizeOfBuffer[0] + SizeOfBuffer[1]))
    {
        // convert hex to byte
        for (auto i = 0; i < SizeOfBuffer[0]; i++)
        {
            auto byte = (unsigned char)StrToInt("0x" + data.SubString(1 + i * 2, 2));
            m_Buffers[0][i] = byte;
        }
        // convert hex to byte
        auto attrOffset = (SizeOfBuffer[0] * 2) + 1;
        for (auto i = 0; i < SizeOfBuffer[1]; i++)
        {
            m_Buffers[1][i] = (unsigned char)StrToInt("0x" + data.SubString(attrOffset + (i * 2), 2));
        }
    }
    Render();
}
//---------------------------------------------------------------------------
void __fastcall ULAPlusGraphicsBuffer::OnEvent(const Event& event)
{
    if (event.Id == "palette.remapped")
    {
        Render();
    }
}
//---------------------------------------------------------------------------

