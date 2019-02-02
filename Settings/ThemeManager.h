//---------------------------------------------------------------------------
#ifndef ThemeManagerH
#define ThemeManagerH
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class ThemeManager
{
public:

    static  void            __fastcall  SetStyle(const String& styleName);
    static  void            __fastcall  LoadStyles(TComboBox* combo);
    static  void            __fastcall  ReapplyStyle();
    static  TStringDynArray __fastcall  GetStyles();
};
//---------------------------------------------------------------------------
}; // namespace Project
//---------------------------------------------------------------------------
#endif
