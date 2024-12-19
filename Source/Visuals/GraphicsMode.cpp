//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "GraphicsMode.h"
#include "GraphicsBuffer.h"
#include "Messaging/Messaging.h"
#include "Messaging/Event.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Visuals;
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
    m_PropertyMap["Name"] = &m_Name;
    m_PropertyMap["Palette"] = &m_PaletteName;
    m_PropertyMap["BitsPerPixel"] = &m_BitsPerPixel;
    m_PropertyMap["PixelsHighPerAttribute"] = &m_PixelsHighPerAttribute;
    m_PropertyMap["Width"] = &m_Width;
    m_PropertyMap["Height"] = &m_Height;
    m_PropertyMap["ScalarX"] = &m_ScalarX;
    m_PropertyMap["ScalarY"] = &m_ScalarY;
    m_PropertyMap["TranparentColor"] = &m_TranparentColor;
    m_PropertyMap["SupportsLogicalColorRemapping"] = &m_SupportsRemapping;
    m_PropertyMap["BufferType"] = &m_BufferTypeName;
    m_PropertyMap["LogicalColors[]"] = &m_LogicalIndex;
    m_PropertyMap["PixelBitRemapping[].Remap[].Mask"] = &m_RemapDataLoader.Mask;
    m_PropertyMap["PixelBitRemapping[].Remap[].Shift"] = &m_RemapDataLoader.Shift;
    m_PropertyMap["ExportInformation.Object.BitmapDataOnly"] = &m_ExportInfo[itObject].BitmapDataOnly;
    m_PropertyMap["ExportInformation.Sprite.BitmapDataOnly"] = &m_ExportInfo[itSprite].BitmapDataOnly;
    m_PropertyMap["ExportInformation.Tile.BitmapDataOnly"] = &m_ExportInfo[itTile].BitmapDataOnly;
    m_PropertyMap["ExportInformation.CharacterSet.BitmapDataOnly"] = &m_ExportInfo[itCharacterSet].BitmapDataOnly;

    m_Palette = std::make_unique<::Palette>();
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
    m_DefaultLogicalColors.clear();
    m_DefaultLogicalColors.assign(other.m_DefaultLogicalColors.begin(), other.m_DefaultLogicalColors.end());
}
//---------------------------------------------------------------------------
void __fastcall GraphicsMode::OnEndObject(const String& object)
{
    if (object == "LogicalColors[]")
    {
        m_LogicalColors.push_back(m_LogicalIndex);
    }
    else if (object == "PixelBitRemapping[].Remap[]")
    {
        m_PixelRemappingLoader.Remaps.push_back(m_RemapDataLoader);
    }
    else if (object == "PixelBitRemapping[]")
    {
        m_PixelRemapping.push_back(m_PixelRemappingLoader);
    }
}
//---------------------------------------------------------------------------
void __fastcall GraphicsMode::RemapColor(int logicalIndex, int paletteIndex)
{
    if (0 <= logicalIndex && logicalIndex < m_LogicalColors.size() && 0 <= paletteIndex && paletteIndex < m_Palette->Colors)
    {
        m_LogicalColors[logicalIndex] = paletteIndex;
        Bus::Publish<Event>(Event("palette.remapped"));
    }
}
//---------------------------------------------------------------------------
unsigned char __fastcall GraphicsMode::RemapPixels(unsigned char pixels) const
{
    if (m_PixelRemapping.size() == 0)
        return pixels;
    // mangle the pixel
    unsigned char mangledByte;
    for (const auto& remaps : m_PixelRemapping)
    {
        for (const auto& remap : remaps.Remaps)
        {
            auto bit = pixels & remap.Mask;
            bit = remap.Shift >= 0 ? bit >> remap.Shift : bit << abs(remap.Shift);
            mangledByte |= bit;
        }
    }
    return mangledByte;
}
//---------------------------------------------------------------------------
void __fastcall GraphicsMode::RestoreDefaultPalette()
{
    m_LogicalColors = m_DefaultLogicalColors;
    Bus::Publish<Event>(Event("palette.remapped"));
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
    if (0 <= index && index < m_LogicalColors.size())
    {
        return m_Palette->Color[m_LogicalColors[index]];
    }
    return clFuchsia;
}
//---------------------------------------------------------------------------
int __fastcall GraphicsMode::GetColorFromLogicalIndex(int index) const
{
    if (0 <= index && index < m_LogicalColors.size())
    {
        return m_LogicalColors[index];
    }
    return 0;
}
//---------------------------------------------------------------------------
const __fastcall GraphicsMode::ExportInfo& __fastcall GraphicsMode::GetExportInformation(ImageTypes imageType) const
{
    return m_ExportInfo[imageType];
}
//---------------------------------------------------------------------------
bool __fastcall GraphicsMode::Load(const String& name)
{
    m_LogicalColors.clear();
    auto loaded = Services::JsonFile::Load(Services::File::Combine(Services::Folders::Application, "Graphics Modes" + Services::Folders::Separator + name + ".json"));
    if (loaded) {
        m_BufferType = BufferTypeByName(m_BufferTypeName);
        loaded = m_Palette->Load(m_PaletteName);
        auto path = Services::File::Combine("Saved Palettes", Name);
        path = Services::Folders::Create(Services::Folders::lpCommon, path);
        SaveLogicalCLUT(path, "Default");
        LoadLogicalCLUT();
        m_DefaultLogicalColors.clear();
        m_DefaultLogicalColors = m_LogicalColors;
    }
    return loaded;
}
//---------------------------------------------------------------------------
void __fastcall GraphicsMode::Save()
{
    // {
    Open(Services::File::Combine(Services::Folders::Application, "Graphics Modes" + Services::Folders::Separator + m_Name + ".json"));
    Write("Name", m_Name);
    Write("Palette", m_PaletteName);
    Write("BufferType", BufferTypeName(m_BufferType));
    Write("Width", m_Width);
    Write("Height", m_Height);
    Write("ScalarX", m_ScalarX);
    Write("ScalarY", m_ScalarY);
    Write("BitsPerPixel", m_BitsPerPixel);
    if (m_BufferType == btBitmap && BitsPerPixel > 1)
    {
        Write("TranparentColor", m_TranparentColor);
    }
    if (m_BufferType == btBitmap && BitsPerPixel > 1 && m_PixelRemapping.size() > 0)
    {
        ArrayStart("PixelBitRemapping");
        for (const auto& pixels : m_PixelRemapping)
        {
            ArrayStart("Pixel");
            for (const auto& remap : pixels.Remaps)
            {
                StartObject();
                    Write("Mask", remap.Mask);
                    Write("Shift", remap.Shift);
                EndObject();
            }
            ArrayStart("Pixel");
        }
        ArrayEnd();
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
void __fastcall GraphicsMode::SaveLogicalCLUT(String path, String name)
{
    if (m_SupportsRemapping)
    {
        if (name == "")
        {
            name = "Logical.clut.json";
        }
        if (path == "")
        {
            path = Services::Folders::Project;
        }
        if (name.Pos(".clut.json") == 0)
        {
            name += ".clut.json";
        }
        auto file = Services::File::Combine(path, name);
        Open(file);
        Write("Palette", m_PaletteName);
        ArrayStart("LogicalColors"); // [
        for (auto index : m_LogicalColors)
        {
            Write(index);
        }
        ArrayEnd(); // ] LogicalColors
        Close();
    }
}
//---------------------------------------------------------------------------
void __fastcall GraphicsMode::LoadLogicalCLUT(String path, String name)
{
    if (m_SupportsRemapping)
    {
        if (name == "")
        {
            name = "Logical.CLUT.json";
        }
        if (path == "")
        {
            path = Services::Folders::Project;
        }
        auto file = Services::File::Combine(path, name);
        if (Services::File::Exists(file))
        {
            auto oldLogicalCount = m_LogicalColors.size();
            auto oldLogicalColors = m_LogicalColors;
            auto oldPaletteName = m_PaletteName;
            m_LogicalColors.clear();
            JsonFile::Load(file);
            if (oldPaletteName != m_PaletteName || oldLogicalCount != m_LogicalColors.size())
            {
                // CLUT mismatch; can't use this CLUT for the palette.
                m_LogicalColors = oldLogicalColors;
                m_PaletteName = oldPaletteName;
            }
            // re-define the default CLUT
            m_DefaultLogicalColors.clear();
            m_DefaultLogicalColors = m_LogicalColors;
            Bus::Publish<Event>(Event("palette.remapped"));
        }
    }
}
//---------------------------------------------------------------------------
int __fastcall GraphicsMode::GetSizeOfPixels(int width, int height) const
{
    return (width / (8 / m_BitsPerPixel)) * height;
}
//---------------------------------------------------------------------------
int __fastcall GraphicsMode::GetSizeOfAttributes(int width, int height) const
{
    return (width / 8) * (height / PixelsHighPerAttribute);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//GraphicsModeWriter::GraphicsModeWriter()
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

