//---------------------------------------------------------------------------
#ifndef ThemeManagerH
#define ThemeManagerH
//---------------------------------------------------------------------------
class ThemeManager
{
private:
    static  TColor          __fastcall  GetColor(int index);

public:

    static  void            __fastcall  SetStyle(const String& styleName);
    static  void            __fastcall  LoadStyles(TComboBox* combo);
    static  void            __fastcall  ReapplyStyle();
    static  TStringDynArray __fastcall  GetStyles();

            TColor          __property  Highlight       = { read = GetColor, index = 0 };
            TColor          __property  Background      = { read = GetColor, index = 1 };
            TColor          __property  Foreground      = { read = GetColor, index = 2 };
            TColor          __property  Shadow          = { read = GetColor, index = 3 };
};
//---------------------------------------------------------------------------
#endif
