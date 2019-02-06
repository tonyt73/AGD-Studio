//---------------------------------------------------------------------------
#ifndef ThemeManagerH
#define ThemeManagerH
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class ThemeManager
{
private:

    static  TColor          __fastcall  GetSelectionColor();
    static  TColor          __fastcall  GetHighlightColor();
    static  TColor          __fastcall  GetBackgroundColor();
    static  TColor          __fastcall  GetForegroundColor();

public:

    static  void            __fastcall  SetStyle(const String& styleName);
    static  void            __fastcall  LoadStyles(TComboBox* combo);
    static  void            __fastcall  ReapplyStyle();
    static  TStringDynArray __fastcall  GetStyles();

            TColor          __property  Selection  = { read = GetSelectionColor  };
            TColor          __property  Highlight  = { read = GetHighlightColor  };
            TColor          __property  Background = { read = GetBackgroundColor };
            TColor          __property  Foreground = { read = GetForegroundColor };
};
//---------------------------------------------------------------------------
}; // namespace Project
//---------------------------------------------------------------------------
#endif
