//---------------------------------------------------------------------------
#ifndef ThemeManagerH
#define ThemeManagerH
//---------------------------------------------------------------------------
class ThemeManager
{
private:
    static  TColor           GetColor(int index);

public:

    static  void             SetStyle(const String& styleName);
    static  void             LoadStyles(TComboBox* combo);
    static  void             ReapplyStyle();
    static  TStringDynArray  GetStyles();

            TColor          __property  Highlight       = { read = GetColor, index = 0 };
            TColor          __property  Background      = { read = GetColor, index = 1 };
            TColor          __property  Foreground      = { read = GetColor, index = 2 };
            TColor          __property  Shadow          = { read = GetColor, index = 3 };
};
//---------------------------------------------------------------------------
#endif
