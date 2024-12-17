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
    String                          m_Name;
    String                          m_Color;            // json loader
    std::vector<TColor>             m_ColorTable;       // the table of Total Palette Colors

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
            Palette&    __fastcall  operator=(const Palette& other);

            bool        __fastcall  Load(const String& name);

    static  DWORD       __fastcall  LuminanceOf(TColor Color);
    static  bool        __fastcall  IsGrey(TColor Color);
    static  int         __fastcall  Diff(TColor Color);

            String      __property  Name                    = { read = m_Name         };
            TColor      __property  Greyscale[int index]    = { read = GetGreyscale   };
            TColor      __property  Color[int index]        = { read = GetTableColor  };
            int         __property  Colors                  = { read = GetTotalColors };
            TColor      __property  FontColorOf[int index]  = { read = GetFontColorOf };
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
