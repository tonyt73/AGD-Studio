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
    String                      m_Name;
    String                      m_Color;            // json loader
    std::vector<TColor>         m_ColorTable;       // the table of Total Palette Colors

    TColor           GetTableColor(int index) const;
    TColor           GetGreyscale(int index) const;
    int              GetTotalColors() const;

    TColor           GetFontColorOf(int index) const;

    void             OnEndObject(const String& object);
    void             Save();

public:
                     Palette();
                     Palette(const String& name);
                     Palette(const Palette& other);
    Palette&         operator=(const Palette& other);

    void             Load(const String& name);

   static DWORD      LuminanceOf(TColor Color);

    String      __property      Name = { read = m_Name };
    TColor      __property      Greyscale[int index] = { read = GetGreyscale };
    TColor      __property      Color[int index] = { read = GetTableColor };
    int         __property      Colors = { read = GetTotalColors };
    TColor      __property      FontColorOf[int index] = { read = GetFontColorOf };
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
