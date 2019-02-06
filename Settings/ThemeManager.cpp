//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Settings/ThemeManager.h"
#include "Settings/Settings.h"
#include "System/File.h"
#include "System/Path.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
void __fastcall ThemeManager::SetStyle(const String& styleName)
{
    if (!TStyleManager::TrySetStyle(styleName, false))
    {
        TStyleManager::LoadFromFile(System::File::Combine(System::Path::GetFolder(System::Path::lpApplication, "Styles"), styleName + ".vsf"));
        TStyleManager::SetStyle(styleName);
    }
    appSettings.ActiveStyle = styleName;
}
//---------------------------------------------------------------------------
void __fastcall ThemeManager::LoadStyles(TComboBox* combo)
{
    combo->Items->Clear();
    auto sl = std::make_unique<TStringList>();
    // load the styles defined in the application
    for (auto i = 0; i < TStyleManager::StyleNames.Length; i++)
    {
        if (TStyleManager::StyleNames[i] != "Windows")
        {
            sl->Add(TStyleManager::StyleNames[i]);
        }
    }
    // load the styles from the styles folder
    auto styles = Project::ThemeManager::GetStyles();
    for (auto style : styles)
    {
        sl->Add(System::File::NameWithoutExtension(style));
    }
    sl->Sort();
    // add to the combo box
    const String style = appSettings.ActiveStyle;
    for (auto i = 0; i < sl->Count; i++)
    {
        combo->Items->Add(sl->Strings[i]);
        if (sl->Strings[i] == style)
        {
            combo->ItemIndex = combo->Items->Count - 1;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ThemeManager::ReapplyStyle()
{
    // force a change back to the current style to reapply it for a hidden form on activation
    auto style = TStyleManager::ActiveStyle->Name;
    TStyleManager::SetStyle(style == TStyleManager::StyleNames[0] ? TStyleManager::StyleNames[1] : TStyleManager::StyleNames[0]);
    TStyleManager::SetStyle(style);
}
//---------------------------------------------------------------------------
TStringDynArray __fastcall ThemeManager::GetStyles()
{
    return System::Path::GetFiles(System::Path::lpApplication, "*.vsf", "Styles");
}
//---------------------------------------------------------------------------
TColor __fastcall ThemeManager::GetSelectionColor()
{
    return StyleServices()->GetStyleColor(scButtonFocused);
}
//---------------------------------------------------------------------------
TColor __fastcall ThemeManager::GetHighlightColor()
{
    return StyleServices()->GetStyleColor(scButtonHot);
}
//---------------------------------------------------------------------------
TColor __fastcall ThemeManager::GetBackgroundColor()
{
    return StyleServices()->GetStyleColor(scButtonNormal);
}
//---------------------------------------------------------------------------
TColor __fastcall ThemeManager::GetForegroundColor()
{
    return StyleServices()->GetStyleFontColor(sfTextLabelNormal);
}
//---------------------------------------------------------------------------
} // namespace Project
