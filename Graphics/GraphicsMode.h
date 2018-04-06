//---------------------------------------------------------------------------
#ifndef GraphicsModeH
#define GraphicsModeH
//---------------------------------------------------------------------------
#include <memory>
#include "Graphics/GraphicsTypes.h"
#include "Graphics/Palette.h"
#include "System/JsonFile.h"
//---------------------------------------------------------------------------
class GraphicsModeDefinitionFile;
//---------------------------------------------------------------------------
// We only support upto 256 colour screen modes
//---------------------------------------------------------------------------
class GraphicsMode
{
private:
    String          m_Name;                     // the name of the screen/graphics mode
    unsigned int    m_BitsPerPixel;             // the number of bits used to store a pixel
    unsigned char   m_PixelsHighPerAttribute;   // the number of pixels high an attribute represents
    unsigned int    m_Width;                    // the default width of the screen for this mode
    unsigned int    m_Height;                   // the default height of the screen for this mode
    unsigned int    m_TranparentColor;          // the index into the palette that represents the transparent pixel color
    float           m_ScalarX;                  // scaling factor for width
    float           m_ScalarY;                  // scaling factor for height
    Palette         m_Palette;                  // the palette table for the graphics mode
    BufferType      m_BufferType;               // the type of graphics buffer

public:
    friend          class       GraphicsModeDefinitionFile;

                    __fastcall  GraphicsMode();

    String          __property  Name = { read = m_Name };
    unsigned int    __property  BitsPerPixel = { read = m_BitsPerPixel };
    unsigned char   __property  PixelsHighPerAttribute = { read = m_PixelsHighPerAttribute };
    unsigned int    __property  Width = { read = m_Width };
    unsigned int    __property  Height = { read = m_Height };
    float           __property  ScalarX = { read = m_ScalarX };
    float           __property  ScalarY = { read = m_ScalarY };
    BufferType      __property  TypeOfBuffer = { read = m_BufferType };
    const Palette   __property  Palette = { read = m_Palette };
};
//---------------------------------------------------------------------------
class GraphicsModeFile : public System::JsonFile
{
private:
    GraphicsMode              m_GraphicsMode;

public:
                    __fastcall  GraphicsModeFile(const String& file);
                    __fastcall ~GraphicsModeFile();

    GraphicsMode    __property  Definition = { read = m_GraphicsMode };
};
//---------------------------------------------------------------------------
#endif
