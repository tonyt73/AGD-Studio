//---------------------------------------------------------------------------
#ifndef PaletteH
#define PaletteH
//---------------------------------------------------------------------------
#include "Services/JsonFile.h"
//---------------------------------------------------------------------------
namespace Visuals
{
//---------------------------------------------------------------------------
class Palette : public Services::JsonFile
{
protected:
    String              m_Name;
    String              m_Color;            // json loader
    std::vector<TColor> m_ColorTable;       // the table of Total Palette Colors

    TColor              __fastcall  GetTableColor(int index) const;
    TColor              __fastcall  GetGreyscale(int index) const;
    int                 __fastcall  GetTotalColors() const;

    TColor              __fastcall  GetFontColorOf(int index) const;

    void                __fastcall  OnEndObject(const String& object);
    void                __fastcall  Save();

public:
                        __fastcall  Palette();
                        __fastcall  Palette(const String& name);
                        __fastcall  Palette(const Palette& other);
    Palette&            __fastcall  operator=(const Palette& other);

    void                __fastcall  Load(const String& name);

    static DWORD        __fastcall  LuminanceOf(TColor Color);

    __property  String  Name                    = { read = m_Name         };
    __property  TColor  Greyscale[int index]    = { read = GetGreyscale   };
    __property  TColor  Color[int index]        = { read = GetTableColor  };
    __property  int     Colors                  = { read = GetTotalColors };
    __property  TColor  FontColorOf[int index]  = { read = GetFontColorOf };
};
//---------------------------------------------------------------------------
//class PaletteWriter : public Palette
//{
//private:
//    void             Validate();
//public:
//                     PaletteWriter();
//};
//---------------------------------------------------------------------------
} // Visual namespace
#endif
