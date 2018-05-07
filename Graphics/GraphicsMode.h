//---------------------------------------------------------------------------
#ifndef GraphicsModeH
#define GraphicsModeH
//---------------------------------------------------------------------------
#include <memory>
#include "Graphics/GraphicsTypes.h"
#include "Graphics/Palette.h"
#include "System/JsonFile.h"
//---------------------------------------------------------------------------
// We only support upto 256 colour screen modes
//---------------------------------------------------------------------------
namespace Agdx
{
class GraphicsMode : public System::JsonFile
{
public:
    struct ExportInfo
    {
        bool    BitmapDataOnly;
    };

private:
    typedef std::vector<unsigned char> Table;

    struct RemapData
    {
        unsigned char Mask;
        int           Shift;
    };

    struct PixelRemapping
    {
        std::vector<RemapData>  Remaps;
    };

    typedef std::vector<PixelRemapping> PixelRemappingList;

protected:
    String                      m_Name;                     // the name of the screen/graphics mode
    String                      m_PaletteName;              // the name of the palette file to load
    unsigned int                m_BitsPerPixel;             // the number of bits used to store a pixel
    unsigned char               m_PixelsHighPerAttribute;   // the number of pixels high an attribute represents
    unsigned int                m_Width;                    // the default width of the screen for this mode
    unsigned int                m_Height;                   // the default height of the screen for this mode
    unsigned int                m_TranparentColor;          // the index into the palette that represents the transparent pixel color
    float                       m_ScalarX;                  // scaling factor for width
    float                       m_ScalarY;                  // scaling factor for height
 std::unique_ptr<Agdx::Palette> m_Palette;                  // the palette table for the graphics mode
    BufferType                  m_BufferType;               // the type of graphics buffer we are
    Table                       m_LogicalColors;            // palette table LOGICAL color indexes into the Total Colors table
    int                         m_LogicalIndex;             // json loader
    bool                        m_SupportsRemapping;        // supports remapping of the logical colors to any of the palette colors
    ExportInfo                  m_ExportInfo[itEnd];        // flags for image data export
    PixelRemappingList          m_PixelRemapping;           // a list of  masks/shifts used to remap pixel bits into contiguous pixel bits for certain graphics modes
    PixelRemapping              m_PixelRemappingLoader;     // used to load the pixel remapping list
    RemapData                   m_RemapDataLoader;          // used to load the remap data into the m_PixelRemappingLoader

    int             __fastcall  GetLogicalColors() const;
    TColor          __fastcall  GetLogicalColor(int index) const;
  const ExportInfo& __fastcall  GetExportInformation(ImageTypes imageType) const;
    void            __fastcall  OnEndObject(const String& object);
    void            __fastcall  Save();

public:
                    __fastcall  GraphicsMode();
                    __fastcall  GraphicsMode(const GraphicsMode& other);

            void    __fastcall  Load(const String& name);
                                // Remap a logical color to a new palettle color
    void            __fastcall  RemapColor(int paletteTableIndex, int colorTableIndex);
    const Palette&  __fastcall  Palette() const;

    String          __property  Name = { read = m_Name };
    unsigned int    __property  BitsPerPixel = { read = m_BitsPerPixel };
    unsigned char   __property  PixelsHighPerAttribute = { read = m_PixelsHighPerAttribute };
    unsigned int    __property  Width = { read = m_Width };
    unsigned int    __property  Height = { read = m_Height };
    float           __property  ScalarX = { read = m_ScalarX };
    float           __property  ScalarY = { read = m_ScalarY };
    BufferType      __property  TypeOfBuffer = { read = m_BufferType };
    int             __property  LogicalColors = { read = GetLogicalColors };
    TColor          __property  LogicalColor[int index] = { read = GetLogicalColor };
    bool            __property  SupportsLogicalColorRemapping = { read = m_SupportsRemapping };
    ExportInfo      __property  ExportInformation[ImageTypes imageType] = { read = GetExportInformation };
};
//---------------------------------------------------------------------------
//class GraphicsModeWriter : public GraphicsMode
//{
//public:
//                __fastcall      GraphicsModeWriter();
//};
//---------------------------------------------------------------------------
}  //Agdx
#endif
