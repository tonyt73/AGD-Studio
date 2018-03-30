//---------------------------------------------------------------------------
#ifndef PaletteH
#define PaletteH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <fmx.graphics.hpp>
#include <vector>
//---------------------------------------------------------------------------
namespace Graphics
{
//---------------------------------------------------------------------------
// Palette definition
//
//---------------------------------------------------------------------------
class TPalette : public TObject
{
protected:
    String                      m_Name;
    int                         m_Colors;

    std::vector<TAlphaColor>    m_Palette;

    virtual void    __fastcall  Generate() = 0;
    TAlphaColor     __fastcall  GetColor(int index);

public:

                    __fastcall  TPalette(const String name);


    __property String           Name = { read = m_Name, write = m_Name };
    __property int              Colors = { read = m_Colors };
    __property TAlphaColor      Color[int index] = { read = GetColor };
};
//---------------------------------------------------------------------------
class TNext8bitPalette : public TPalette
{
private:
    void            __fastcall  Generate();

public:
                    __fastcall  TNext8bitPalette();
};
//---------------------------------------------------------------------------
class TNext9bitPalette : public TPalette
{
private:
    void            __fastcall  Generate();

public:
                    __fastcall  TNext9bitPalette();
};
//---------------------------------------------------------------------------
} // graphics namespace
//---------------------------------------------------------------------------
#endif
