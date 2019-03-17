//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Palette.h"
#include "System.Math.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Agdx;
//---------------------------------------------------------------------------
__fastcall Palette::Palette()
: JsonFile()
, m_Name("unknown")
{
    // json loading properties
    m_PropertyMap["Palette.Name"] = &m_Name;
    m_PropertyMap["ColorTable[]"] = &m_Color;
}
//---------------------------------------------------------------------------
__fastcall Palette::Palette(const String& name)
: Palette()
{
    m_Name = name;
}
//---------------------------------------------------------------------------
__fastcall Palette::Palette(const Palette& other)
: Palette()
{
    m_Name = other.m_Name;
    m_ColorTable.clear();
    m_ColorTable.assign(other.m_ColorTable.begin(), other.m_ColorTable.end());
}
//---------------------------------------------------------------------------
Palette& __fastcall Palette::operator=(const Palette& other)
{
    m_Name = other.m_Name;
    m_ColorTable.clear();
    m_ColorTable.assign(other.m_ColorTable.begin(), other.m_ColorTable.end());
    return *this;
}
//---------------------------------------------------------------------------
TColor __fastcall Palette::GetTableColor(int index) const
{
    if (0 <= index && index < m_ColorTable.size())
    {
        return m_ColorTable[index];
    }
    return m_ColorTable[1];
}
//---------------------------------------------------------------------------
TColor __fastcall Palette::GetGreyscale(int index) const
{
    auto color = GetTableColor(index);
    unsigned char r = (color & 0x000000FF);
    unsigned char g = (color & 0x0000FF00) >>  8;
    unsigned char b = (color & 0x00FF0000) >> 16;
    auto linearIntensity = (unsigned int)(0.2126f * r + 0.7512f * g + 0.0722 * b) & 0x000000FF;
    color = (TColor)(linearIntensity | (linearIntensity << 8) | (linearIntensity << 16));
    return color;
}
//---------------------------------------------------------------------------
int __fastcall Palette::GetTotalColors() const
{
    return m_ColorTable.size();
}
//---------------------------------------------------------------------------
TColor __fastcall Palette::GetFontColorOf(int index) const
{
    return (LuminanceOf(GetTableColor(index)) < 128) ? clWhite : clBlack;
}
//---------------------------------------------------------------------------
DWORD __fastcall Palette::LuminanceOf(TColor Color)
{
    // get the luminance of the color
    DWORD dwRed       = (Color & 0x000000FF) >>  0;
    DWORD dwGreen     = (Color & 0x0000FF00) >>  8;
    DWORD dwBlue      = (Color & 0x00FF0000) >> 16;
    DWORD dwLuminance = (0.299f * (double)dwRed + 0.587f * (double)dwGreen + 0.114f * (double)dwBlue);
    return dwLuminance;
}
//---------------------------------------------------------------------------
void __fastcall Palette::OnEndObject(const String& object)
{
    if (object == "ColorTable[]")
    {
        m_ColorTable.push_back((TColor)(StrToInt(m_Color)));
    }
}
//---------------------------------------------------------------------------
void __fastcall Palette::Load(const String& name)
{
    m_ColorTable.clear();
    JsonFile::Load(System::File::Combine(System::Path::Application, "Palettes" + System::Path::Separator + name + ".json"));
}
//---------------------------------------------------------------------------
void __fastcall Palette::Save()
{
//    // {
//    Open(System::File::Combine(System::Path::Application, "Palettes" + System::Path::Separator + m_Name + ".json"));
//    Push("Palette"); // {
//        Write("Name", m_Name);
//    Pop(); // }
//    ArrayStart("ColorTable"); // [
//    for (auto color : m_ColorTable)
//    {
//        Write("$" + IntToHex(color, 6));
//    }
//    ArrayEnd(); // ] ColorTable
//    // }
//    Close();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//void __fastcall PaletteWriter::Validate()
//{
//    Save();
//    auto file = System::File::Combine(System::Path::Application, "Palettes" + System::Path::Separator + m_Name + ".json");
//    std::vector<TColor>         oldColorTable;
//    oldColorTable.assign(m_ColorTable.begin(), m_ColorTable.end());
//    m_ColorTable.clear();
//    Load(file);
//    auto c1 = m_ColorTable.size();
//    auto c2 = oldColorTable.size();
//    if (m_ColorTable != oldColorTable)
//    {
//        assert(0);
//    }
//}
//---------------------------------------------------------------------------
//__fastcall PaletteWriter::PaletteWriter()
//: Palette("ZX Spectrum")
//{
//    m_ColorTable.push_back(clBlack);
//    m_ColorTable.push_back((TColor)0x00BF0000);
//    m_ColorTable.push_back((TColor)0x000000BF);
//    m_ColorTable.push_back((TColor)0x00BF00BF);
//    m_ColorTable.push_back((TColor)0x0000BF00);
//    m_ColorTable.push_back((TColor)0x00BFBF00);
//    m_ColorTable.push_back((TColor)0x0000BFBF);
//    m_ColorTable.push_back((TColor)0x00BFBFBF);
//    m_ColorTable.push_back(clBlack);
//    m_ColorTable.push_back(clBlue);
//    m_ColorTable.push_back(clRed);
//    m_ColorTable.push_back(clFuchsia);
//    m_ColorTable.push_back(clLime);
//    m_ColorTable.push_back(clAqua);
//    m_ColorTable.push_back(clYellow);
//    m_ColorTable.push_back(clWhite);
//    for (auto i = 0; i < 16; i++)
//    {
//        m_PaletteTable.push_back(i);
//    }
//    Validate();
//}
//---------------------------------------------------------------------------
//unsigned char c3_to_c8(unsigned char c3)
//{
//    return (unsigned char) SimpleRoundTo((c3 * 255.0) / 7.0);
//}
////---------------------------------------------------------------------------
//__fastcall PaletteWriter::PaletteWriter()
//: Palette("ZX Spectrum Next 256")
//{
//    for (auto i = 0; i < 256; i++)
//    {
//        unsigned char r3 = (i >> 5) & 0x07;
//        unsigned char g3 = (i >> 2) & 0x07;
//        unsigned char b2 = (i >> 0) & 0x03;
//        unsigned char b3 = (b2 << 1) | (((b2 >> 1) | b2) & 0x01);
//        // Convert the standard RGB333 color back to an RGB888 color.
//        unsigned char r8 = c3_to_c8(r3);
//        unsigned char g8 = c3_to_c8(g3);
//        unsigned char b8 = c3_to_c8(b3);
//
//        auto color = (TColor)(b8 << 16 | g8 << 8 | r8);
//        m_ColorTable.push_back(color);
//    }
//    for (auto i = 0; i < 256; i++)
//    {
//        m_PaletteTable.push_back(i);
//    }
//    Validate();
//}
//---------------------------------------------------------------------------
//__fastcall PaletteWriter::PaletteWriter()
//: Palette("Amstrad CPC Mode 0")
//{
//    m_ColorTable.push_back(clBlack);
//    m_ColorTable.push_back(clNavy);
//    m_ColorTable.push_back(clBlue);
//    m_ColorTable.push_back(clMaroon);
//    m_ColorTable.push_back(clPurple);
//    m_ColorTable.push_back((TColor)0x00FF0080);
//    m_ColorTable.push_back(clRed);
//    m_ColorTable.push_back((TColor)0x008000FF);
//    m_ColorTable.push_back(clFuchsia);
//    m_ColorTable.push_back(clGreen);
//    m_ColorTable.push_back(clTeal);
//    m_ColorTable.push_back((TColor)0x00FF8000);
//    m_ColorTable.push_back(clOlive);
//    m_ColorTable.push_back(clGray);
//    m_ColorTable.push_back((TColor)0x00FF8080);
//    m_ColorTable.push_back((TColor)0x000080FF);
//    m_ColorTable.push_back((TColor)0x008080FF);
//    m_ColorTable.push_back((TColor)0x00FF80FF);
//    m_ColorTable.push_back(clLime);
//    m_ColorTable.push_back((TColor)0x0080FF00);
//    m_ColorTable.push_back(clAqua);
//    m_ColorTable.push_back((TColor)0x0000FF80);
//    m_ColorTable.push_back((TColor)0x0080FF80);
//    m_ColorTable.push_back((TColor)0x00FFFF80);
//    m_ColorTable.push_back(clYellow);
//    m_ColorTable.push_back((TColor)0x0080FFFF);
//    m_ColorTable.push_back(clWhite);
//    for (auto i = 0; i < 16; i++)
//    {
//        m_PaletteTable.push_back(i);
//    }
//    Validate();
//}
////---------------------------------------------------------------------------
//__fastcall PaletteWriter::PaletteWriter()
//: Palette("Amstrad CPC Mode 1")
//{
//    m_ColorTable.push_back(clBlack);
//    m_ColorTable.push_back(clNavy);
//    m_ColorTable.push_back(clBlue);
//    m_ColorTable.push_back(clMaroon);
//    m_ColorTable.push_back(clPurple);
//    m_ColorTable.push_back((TColor)0x00FF0080);
//    m_ColorTable.push_back(clRed);
//    m_ColorTable.push_back((TColor)0x008000FF);
//    m_ColorTable.push_back(clFuchsia);
//    m_ColorTable.push_back(clGreen);
//    m_ColorTable.push_back(clTeal);
//    m_ColorTable.push_back((TColor)0x00FF8000);
//    m_ColorTable.push_back(clOlive);
//    m_ColorTable.push_back(clGray);
//    m_ColorTable.push_back((TColor)0x00FF8080);
//    m_ColorTable.push_back((TColor)0x000080FF);
//    m_ColorTable.push_back((TColor)0x008080FF);
//    m_ColorTable.push_back((TColor)0x00FF80FF);
//    m_ColorTable.push_back(clLime);
//    m_ColorTable.push_back((TColor)0x0080FF00);
//    m_ColorTable.push_back(clAqua);
//    m_ColorTable.push_back((TColor)0x0000FF80);
//    m_ColorTable.push_back((TColor)0x0080FF80);
//    m_ColorTable.push_back((TColor)0x00FFFF80);
//    m_ColorTable.push_back(clYellow);
//    m_ColorTable.push_back((TColor)0x0080FFFF);
//    m_ColorTable.push_back(clWhite);
//    for (auto i = 0; i < 16; i++)
//    {
//        m_PaletteTable.push_back(i);
//    }
//    Validate();
//}
//---------------------------------------------------------------------------
//__fastcall PaletteWriter::PaletteWriter()
//: Palette("Amstrad CPC Mode 2")
//{
//    m_ColorTable.push_back(clBlack);
//    m_ColorTable.push_back(clNavy);
//    m_ColorTable.push_back(clBlue);
//    m_ColorTable.push_back(clMaroon);
//    m_ColorTable.push_back(clPurple);
//    m_ColorTable.push_back((TColor)0x00FF0080);
//    m_ColorTable.push_back(clRed);
//    m_ColorTable.push_back((TColor)0x008000FF);
//    m_ColorTable.push_back(clFuchsia);
//    m_ColorTable.push_back(clGreen);
//    m_ColorTable.push_back(clTeal);
//    m_ColorTable.push_back((TColor)0x00FF8000);
//    m_ColorTable.push_back(clOlive);
//    m_ColorTable.push_back(clGray);
//    m_ColorTable.push_back((TColor)0x00FF8080);
//    m_ColorTable.push_back((TColor)0x000080FF);
//    m_ColorTable.push_back((TColor)0x008080FF);
//    m_ColorTable.push_back((TColor)0x00FF80FF);
//    m_ColorTable.push_back(clLime);
//    m_ColorTable.push_back((TColor)0x0080FF00);
//    m_ColorTable.push_back(clAqua);
//    m_ColorTable.push_back((TColor)0x0000FF80);
//    m_ColorTable.push_back((TColor)0x0080FF80);
//    m_ColorTable.push_back((TColor)0x00FFFF80);
//    m_ColorTable.push_back(clYellow);
//    m_ColorTable.push_back((TColor)0x0080FFFF);
//    m_ColorTable.push_back(clWhite);
//    m_PaletteTable.push_back(0);
//    m_PaletteTable.push_back(15);
//    Validate();
//}
//---------------------------------------------------------------------------
//__fastcall PaletteWriter::PaletteWriter()
//: Palette("Monochrome")
//{
//    m_ColorTable.push_back(clBlack);
//    m_ColorTable.push_back(clWhite);
//    m_PaletteTable.push_back(0);
//    m_PaletteTable.push_back(1);
//    Validate();
//}
//---------------------------------------------------------------------------
//__fastcall PaletteWriter::PaletteWriter()
//: Palette("Acorn Atom")
//{
//    m_ColorTable.push_back(clBlack);
//    m_ColorTable.push_back(clLime);
//    m_PaletteTable.push_back(0);
//    m_PaletteTable.push_back(1);
//    Validate();
//}
//---------------------------------------------------------------------------
//__fastcall PaletteWriter::PaletteWriter()
//: Palette("Sam Coupe Mode 3")
//{
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00480000);
//    m_ColorTable.push_back(0x00000048);
//    m_ColorTable.push_back(0x00480048);
//    m_ColorTable.push_back(0x00004800);
//    m_ColorTable.push_back(0x00004848);
//    m_ColorTable.push_back(0x00484800);
//    m_ColorTable.push_back(0x00484848);
//    m_ColorTable.push_back(0x00242424);
//    m_ColorTable.push_back(0x006D2424);
//    m_ColorTable.push_back(0x0024246D);
//    m_ColorTable.push_back(0x006D246D);
//    m_ColorTable.push_back(0x00246D24);
//    m_ColorTable.push_back(0x006D6D24);
//    m_ColorTable.push_back(0x00246D6D);
//    m_ColorTable.push_back(0x006D6D6D);
//
//    m_ColorTable.push_back(0x00910000);
//    m_ColorTable.push_back(0x00DA0000);
//    m_ColorTable.push_back(0x00910048);
//    m_ColorTable.push_back(0x00DA0048);
//    m_ColorTable.push_back(0x00914800);
//    m_ColorTable.push_back(0x00DA4800);
//    m_ColorTable.push_back(0x00914848);
//    m_ColorTable.push_back(0x00DA4848);
//    m_ColorTable.push_back(0x00B62424);
//    m_ColorTable.push_back(0x00FF2424);
//    m_ColorTable.push_back(0x00B6246D);
//    m_ColorTable.push_back(0x00FF246D);
//    m_ColorTable.push_back(0x00B66D24);
//    m_ColorTable.push_back(0x00FF6D24);
//    m_ColorTable.push_back(0x00B66D6D);
//    m_ColorTable.push_back(0x00FF6D6D);
//
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    m_ColorTable.push_back(0x00000000);
//    for (auto i = 0; i < 16; i++)
//    {
//        m_PaletteTable.push_back(i);
//    }
//    Validate();
//}
//---------------------------------------------------------------------------

