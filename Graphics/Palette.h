//---------------------------------------------------------------------------
#ifndef PaletteH
#define PaletteH
//---------------------------------------------------------------------------
#include "System/JsonFile.h"
//---------------------------------------------------------------------------
class PaletteDefinitionFile;
//---------------------------------------------------------------------------
class Palette
{
private:
    int                         m_TotalColors;
    int                         m_LogicalColors;
    int                         m_ColorsPerTable;

    std::vector<unsigned char>  m_Table;
    std::vector<TColor>         m_Colors;

    TColor      __fastcall      GetColor(int index) const;
    TColor      __fastcall      GetGreyscale(int index) const;

public:
    friend class PaletteDefinitionFile;

                __fastcall      Palette();

     TColor     __property      Color[int index] = { read = GetColor };
     TColor     __property      Greyscale[int index] = { read = GetGreyscale };
};
//---------------------------------------------------------------------------
class PaletteDefinition : public System::JsonFile
{
};
//---------------------------------------------------------------------------
#endif
