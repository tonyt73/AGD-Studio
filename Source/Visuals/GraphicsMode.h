//---------------------------------------------------------------------------
#ifndef GraphicsModeH
#define GraphicsModeH
//---------------------------------------------------------------------------
#include "GraphicsTypes.h"
#include "Palette.h"
#include "Services/JsonFile.h"
//---------------------------------------------------------------------------
// We only support upto 256 colour screen modes
//---------------------------------------------------------------------------
namespace Visuals
{
//---------------------------------------------------------------------------
class GraphicsMode : public Services::JsonFile
{
public:
    struct ExportInfo
    {
        bool                    BitmapDataOnly;
    };

private:
    // table of indexes
    typedef std::vector<unsigned char> Table;

    // Data used to remap a bitmap pixel into a mangled pixel for certain graphic modes
    // i.e. Amstrad CPC Mode 0, 1, 2
    struct RemapData
    {
        unsigned char           Mask;
        int                     Shift;
    };

    // The list of pixels (dependent on number of pixels per byte) and their remapping
    struct PixelRemapping
    {
        std::vector<RemapData>  Remaps;
    };

    // a list for pixel mangling remaps
    typedef std::vector<PixelRemapping> PixelRemappingList;

protected:
                String          m_Name;                     // the name of the screen/graphics mode
                String          m_PaletteName;              // the name of the palette file to load
                unsigned int    m_BitsPerPixel;             // the number of bits used to store a pixel
                unsigned char   m_PixelsHighPerAttribute;   // the number of pixels high an attribute represents
                unsigned int    m_Width;                    // the default width of the screen for this mode
                unsigned int    m_Height;                   // the default height of the screen for this mode
                unsigned int    m_TranparentColor;          // the index into the palette that represents the transparent pixel color
                float           m_ScalarX;                  // scaling factor for width
                float           m_ScalarY;                  // scaling factor for height
    std::unique_ptr<Palette> 	m_Palette;                  // the palette table for the graphics mode
                BufferType      m_BufferType;               // the type of graphics buffer we are
                Table           m_LogicalColors;            // palette table LOGICAL color indexes into the Total Colors table
                Table           m_DefaultLogicalColors;     // default palette table LOGICAL color indexes into the Total Colors table
                int             m_LogicalIndex;             // json loader
                bool            m_SupportsRemapping;        // supports remapping of the logical colors to any of the palette colors
                ExportInfo      m_ExportInfo[itEnd];        // flags for image data export
            PixelRemappingList  m_PixelRemapping;           // a list of  masks/shifts used to remap pixel bits into machine specific formats for certain graphics modes
            PixelRemapping      m_PixelRemappingLoader;     // used to load the pixel remapping list
                RemapData       m_RemapDataLoader;          // used to load the remap data into the m_PixelRemappingLoader

                int             GetLogicalColors() const;
                TColor          GetLogicalColor(int index) const;
                int             GetColorFromLogicalIndex(int index) const;
    const       ExportInfo&     GetExportInformation(ImageTypes imageType) const;
                void            OnEndObject(const String& object);
                void            Save();

public:
                                GraphicsMode();
                                GraphicsMode(const GraphicsMode& other);

                void            Load(const String& name);
                void            SaveLogicalCLUT(String path = "", String name = "");
                void            LoadLogicalCLUT(String path = "", String name = "");
                                // Remap a logical color to a new palette color
                void            RemapColor(int paletteTableIndex, int colorTableIndex);
                unsigned char   RemapPixels(unsigned char pixels) const;
                void            RestoreDefaultPalette();
    const       Palette&        Palette() const;

    __property  String          Name = { read = m_Name };
    __property  unsigned int    BitsPerPixel = { read = m_BitsPerPixel };
    __property  unsigned char   PixelsHighPerAttribute = { read = m_PixelsHighPerAttribute };
    __property  unsigned int    Width = { read = m_Width };
    __property  unsigned int    Height = { read = m_Height };
    __property  float           ScalarX = { read = m_ScalarX };
    __property  float           ScalarY = { read = m_ScalarY };
    __property  BufferType      TypeOfBuffer = { read = m_BufferType };
    __property  int             FromLogicalColor[int index] = { read = GetColorFromLogicalIndex };          // get a palette table index from a logical index
    __property  int             LogicalColors = { read = GetLogicalColors };
    __property  TColor          LogicalColor[int index] = { read = GetLogicalColor };
    __property  bool            SupportsLogicalColorRemapping = { read = m_SupportsRemapping };
    __property  ExportInfo      ExportInformation[ImageTypes imageType] = { read = GetExportInformation };
};
//---------------------------------------------------------------------------
//class GraphicsModeWriter : public GraphicsMode
//{
//public:
//                     GraphicsModeWriter();
//};
//---------------------------------------------------------------------------
} // Visuals namespace
//---------------------------------------------------------------------------
#endif
