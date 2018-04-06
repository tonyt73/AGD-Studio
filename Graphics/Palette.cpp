//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Palette.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Palette::Palette()
{
}
//---------------------------------------------------------------------------
TColor __fastcall Palette::GetColor(int index) const
{
    if (0 < index && index < m_Table.size())
    {
        return m_Colors[m_Table[index]];
    }
    return clBlack;
}
//---------------------------------------------------------------------------
TColor __fastcall Palette::GetGreyscale(int index) const
{
    auto color = GetColor(index);
    unsigned char r = (color & 0x000000FF);
    unsigned char g = (color & 0x0000FF00) >>  8;
    unsigned char b = (color & 0x00FF0000) >> 16;
    auto linearIntensity = (unsigned int)(0.2126f * r + 0.7512f * g + 0.0722 * b) & 0x000000FF;
    color = (TColor)(linearIntensity | (linearIntensity << 8) | (linearIntensity << 16));
    return color;
}
//---------------------------------------------------------------------------

