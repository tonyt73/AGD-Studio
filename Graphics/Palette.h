//---------------------------------------------------------------------------
#ifndef PaletteH
#define PaletteH
//---------------------------------------------------------------------------
#include "System/JsonFile.h"
//---------------------------------------------------------------------------
class Palette : public JsonFile
{
protected:
    String                      m_Name;
    String                      m_Color;            // json loader
    int                         m_Index;            // json loader

    std::vector<unsigned char>  m_PaletteTable;     // palette table LOGICAL color indexes into the Total Colors table
    std::vector<TColor>         m_ColorTable;       // the table of Total Palette Colors

    TColor      __fastcall      GetTableColor(int index) const;
    TColor      __fastcall      GetPaletteColor(int index) const;
    TColor      __fastcall      GetPaletteGreyscale(int index) const;
    int         __fastcall      GetTotalColors() const;
    int         __fastcall      GetLogicalColors() const;

    void        __fastcall      OnEndObject(const String& object);
    void        __fastcall      Save();

public:
                __fastcall      Palette();
                __fastcall      Palette(const String& name);
                __fastcall      Palette(const Palette& other);

                                // Remap a palette table color to a pale
    void        __fastcall      RemapColor(int paletteTableIndex, int colorTableIndex);

    TColor      __property      Color[int index] = { read = GetPaletteColor };
    TColor      __property      Greyscale[int index] = { read = GetPaletteGreyscale };
    TColor      __property      ColorTable[int index] = { read = GetTableColor };
    int         __property      TotalColors = { read = GetTotalColors };
    int         __property      LogicalColors = { read = GetLogicalColors };
};
//---------------------------------------------------------------------------
class PaletteWriter : public Palette
{
private:
    void        __fastcall      Validate();
public:
                __fastcall      PaletteWriter();
};

//---------------------------------------------------------------------------
#endif
