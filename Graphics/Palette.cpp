//---------------------------------------------------------------------------
#include "Arcadium.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Palette.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace std;
//---------------------------------------------------------------------------
namespace Graphics
{
//---------------------------------------------------------------------------
__fastcall TPalette::TPalette(const String name)
: m_Name(name)
{
}
//---------------------------------------------------------------------------
TAlphaColor __fastcall TPalette::GetColor(int index)
{
    if (0 <= index && index < m_Colors)
    {
        return m_Palette[index];
    }
    return TAlphaColorRec::Black;
}
//---------------------------------------------------------------------------
__fastcall TNext8bitPalette::TNext8bitPalette()
: TPalette("Spectrum Next 256 Colour")
{
    m_Colors = 256;
    Generate();
}
//---------------------------------------------------------------------------
void __fastcall TNext8bitPalette::Generate()
{
    // RRRGGGBB
    m_Palette.clear();
    // convert the rgb bits into TColor
    for (unsigned int i = 0; i < m_Colors; i++)
    {
        // get RGB bits into top of byte
        unsigned char r = (i & 0xE0);
        unsigned char g = (i & 0x1C) << 3;
        unsigned char b = (i & 0x03) << 6;
        r = r | r >> 3 | r >> 6;
        g = g | g >> 3 | g >> 6;
        b = b | b >> 2 | b >> 4 | b >> 6;
        // make a color from the rgb values
        TAlphaColor color((TAlphaColor)(0xFF000000 | r << 16 | g << 8 | b));
        // add it to the palette
        m_Palette.push_back(color);
    }
}
//---------------------------------------------------------------------------
__fastcall TNext9bitPalette::TNext9bitPalette()
: TPalette("Spectrum Next 512 Colour")
{
    m_Colors = 512;
    Generate();
}
//---------------------------------------------------------------------------
void __fastcall TNext9bitPalette::Generate()
{
    // RRRGGGBBB
    m_Palette.clear();
    // convert the rgb bits into TColor
    for (unsigned int i = 0; i < m_Colors; i++)
    {
        // get RGB bits into top of byte
        unsigned char r = (i & 0x1C0) >> 1;
        unsigned char g = (i & 0x038) << 2;
        unsigned char b = (i & 0x007) << 5;
        r = r | r >> 3 | r >> 6;
        g = g | g >> 3 | g >> 6;
        b = b | b >> 3 | b >> 6;
        // make a color from the rgb values
        TAlphaColor color((TAlphaColor)(0xFF000000 | r << 16 | g << 8 | b));
        // add it to the palette
        m_Palette.push_back(color);
    }
}
//---------------------------------------------------------------------------
} // graphics namespace
//---------------------------------------------------------------------------
