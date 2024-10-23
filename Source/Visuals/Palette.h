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

    TColor              GetTableColor(int index) const;
    TColor              GetGreyscale(int index) const;
    int                 GetTotalColors() const;

    TColor              GetFontColorOf(int index) const;

    void                OnEndObject(const String& object);
    void                Save();

public:
                        Palette();
                        Palette(const String& name);
                        Palette(const Palette& other);
    Palette&            operator=(const Palette& other);

    void                Load(const String& name);

    static DWORD        LuminanceOf(TColor Color);

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
