//---------------------------------------------------------------------------
#ifndef ThemeManagerH
#define ThemeManagerH
//---------------------------------------------------------------------------
class ThemeManager
{
private:
    static  TColor              GetColor(int index);

public:

    static  void                SetStyle(const String& styleName);
    static  void                LoadStyles(TComboBox* combo);
    static  void                ReapplyStyle();
    static  TStringDynArray     GetStyles();

    __property  TColor          Highlight  = { read = GetColor, index = 0 };
    __property  TColor          Background = { read = GetColor, index = 1 };
    __property  TColor          Foreground = { read = GetColor, index = 2 };
    __property  TColor          Shadow     = { read = GetColor, index = 3 };
};
//---------------------------------------------------------------------------
#endif
