//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Vcl.Themes.hpp"
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
    auto styleFile = System::File::Combine(System::Path::GetFolder(System::Path::lpApplication, "Styles"), styleName + ".vsf");
    if (!TStyleManager::TrySetStyle(styleName, false) && System::File::Exists(styleFile))
    {
        try
        {
            TStyleManager::SetStyle(TStyleManager::LoadFromFile(styleFile));
        }
        catch(...)
        {
        }
    }
    appSettings.ActiveStyle = styleName;
    ::Messaging::Bus::Publish<ThemeChangedEvent>(ThemeChangedEvent());
}
//---------------------------------------------------------------------------
void __fastcall ThemeManager::LoadStyles(TComboBox* combo)
{
    combo->Items->Clear();
    auto sl = std::make_unique<TStringList>();
    // default application style
    sl->Add("Onyx Blue");
    // load the styles from the styles folder
    auto styles = Project::ThemeManager::GetStyles();
    TStyleInfo si;
    for (auto styleFile : styles)
    {
        sl->Add(System::File::NameWithoutExtension(styleFile));
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
