//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "GraphicsMode.h"
#include "GraphicsBuffers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace Agdx;
//---------------------------------------------------------------------------
__fastcall GraphicsMode::GraphicsMode()
: JsonFile()
, m_Name("unknown")
, m_BitsPerPixel(0)
, m_PixelsHighPerAttribute(0)
, m_Width(0)
, m_Height(0)
, m_TranparentColor(0)
, m_ScalarX(1.f)
, m_ScalarY(1.f)
, m_Palette(nullptr)
, m_BufferType(btInvalid)
{
    m_PropertyMap[".{}.Name"] = &m_Name;
    m_PropertyMap[".{}.Palette"] = &m_PaletteName;
    m_PropertyMap[".{}.BitsPerPixel"] = &m_BitsPerPixel;
    m_PropertyMap[".{}.PixelsHighPerAttribute"] = &m_PixelsHighPerAttribute;
    m_PropertyMap[".{}.Width"] = &m_Width;
    m_PropertyMap[".{}.Height"] = &m_Height;
    m_PropertyMap[".{}.ScalarX"] = &m_ScalarX;
    m_PropertyMap[".{}.ScalarY"] = &m_ScalarY;
    m_PropertyMap[".{}.TranparentColor"] = &m_TranparentColor;
    m_PropertyMap[".{}.SupportsLogicalColorRemapping"] = &m_SupportsRemapping;
    m_PropertyMap[".{}.BufferType"] = &m_BufferType;
    m_PropertyMap[".{}.LogicalColors.[]"] = &m_LogicalIndex;
    m_PropertyMap[".{}.PixelBitRemapping.[].{}.Pixel.{}.Mask"] = &m_RemapDataLoader.Mask;
    m_PropertyMap[".{}.PixelBitRemapping.[].{}.Pixel.{}.Shift"] = &m_RemapDataLoader.Shift;
    m_PropertyMap[".{}.ExportInformation.{}.Object.{}.BitmapDataOnly"] = &m_ExportInfo[itObject].BitmapDataOnly;
    m_PropertyMap[".{}.ExportInformation.{}.Sprite.{}.BitmapDataOnly"] = &m_ExportInfo[itSprite].BitmapDataOnly;
    m_PropertyMap[".{}.ExportInformation.{}.Tile.{}.BitmapDataOnly"] = &m_ExportInfo[itTile].BitmapDataOnly;
    m_PropertyMap[".{}.ExportInformation.{}.CharacterSet.{}.BitmapDataOnly"] = &m_ExportInfo[itCharacterSet].BitmapDataOnly;

    m_Palette = std::make_unique<Agdx::Palette>();
}
//---------------------------------------------------------------------------
__fastcall GraphicsMode::GraphicsMode(const GraphicsMode& other)
{
    m_Name = other.m_Name;
    m_PaletteName = other.m_PaletteName;
    m_BitsPerPixel = other.m_BitsPerPixel;
    m_PixelsHighPerAttribute = other.m_PixelsHighPerAttribute;
    m_Width = other.m_Width;
    m_Height = other.m_Height;
    m_TranparentColor = other.m_TranparentColor;
    m_ScalarX = other.m_ScalarX;
    m_ScalarY = other.m_ScalarY;
    m_BufferType = other.m_BufferType;
    *m_Palette = *other.m_Palette;
    m_LogicalColors.clear();
    m_LogicalColors.assign(other.m_LogicalColors.begin(), other.m_LogicalColors.end());
}
//---------------------------------------------------------------------------
void __fastcall GraphicsMode::OnEndObject(const String& object)
{
    if (object == ".{}.LogicalColors.[]")
    {
        m_LogicalColors.push_back(m_LogicalIndex);
    }
    else if (object == ".{}.PixelBitRemapping.[].{}.Pixel.{}")
    {
        m_PixelRemappingLoader.Remaps.push_back(m_RemapDataLoader);
    }
    else if (object == ".{}.PixelBitRemapping.[].{}.Pixel")
    {
        m_PixelRemapping.push_back(m_PixelRemappingLoader);
    }
}
//---------------------------------------------------------------------------
void __fastcall GraphicsMode::RemapColor(int logicalIndex, int paletteIndex)
{
    if (0 < logicalIndex && logicalIndex < m_LogicalColors.size() && 0 < paletteIndex && paletteIndex < m_Palette->Colors)
    {
        m_LogicalColors[logicalIndex] = m_Palette->Color[paletteIndex];
    }
}
//---------------------------------------------------------------------------
const Palette& __fastcall GraphicsMode::Palette() const
{
    return *m_Palette;
}
//---------------------------------------------------------------------------
int __fastcall GraphicsMode::GetLogicalColors() const
{
    return m_LogicalColors.size();
}
//---------------------------------------------------------------------------
TColor __fastcall GraphicsMode::GetLogicalColor(int index) const
{
    if (0 < index && index < m_LogicalColors.size())
    {
        return m_Palette->Color[m_LogicalColors[index]];
    }
    return clFuchsia;
}
//---------------------------------------------------------------------------
const GraphicsMode::ExportInfo& __fastcall GraphicsMode::GetExportInformation(ImageTypes imageType) const
{
    return m_ExportInfo[imageType];
}
//---------------------------------------------------------------------------
void __fastcall GraphicsMode::Load(const String& name)
{
    m_LogicalColors.clear();
    JsonFile::Load(System::File::Combine(System::Path::Application, "GraphicsModes" + System::Path::Separator + name + ".json"));
    m_Palette->Load(m_PaletteName);
}
//---------------------------------------------------------------------------
void __fastcall GraphicsMode::Save()
{
    // {
    Open(System::File::Combine(System::Path::Application, "GraphicsModes" + System::Path::Separator + m_Name + ".json"));
    Write("Name", m_Name);
    Write("Palette", m_PaletteName);
    Write("BufferType", m_BufferType);
    Write("Width", (int)m_Width);
    Write("Height", (int)m_Height);
    Write("ScalarX", m_ScalarX);
    Write("ScalarY", m_ScalarY);
    Write("BitsPerPixel", m_BitsPerPixel);
    if (m_BufferType == btBitmap && BitsPerPixel > 1)
    {
        Write("TranparentColor", m_TranparentColor);
    }
    if (m_BufferType == btAttribute)
    {
        Write("PixelsHighPerAttribute", m_PixelsHighPerAttribute);
    }
    ArrayStart("LogicalColors"); // [
    for (auto index : m_LogicalColors)
    {
        Write(index);
    }
    ArrayEnd(); // ] LogicalColors
    // }
    Close();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//__fastcall GraphicsModeWriter::GraphicsModeWriter()
//: GraphicsMode()
//{
//    m_Name = "Amstrad CPC Mode 1";
//    m_PaletteName = "Amstrad CPC";
//    m_BufferType = btBitmap;
//    m_BitsPerPixel = 4;
//    m_Width = 160;
//    m_Height = 200;
//    m_ScalarX = 2;
//
//    Save();
//}
//---------------------------------------------------------------------------

