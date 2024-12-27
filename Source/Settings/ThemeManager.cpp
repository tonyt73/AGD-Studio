//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "ThemeManager.h"
#include "Project/Documents/Settings.h"
#include "Services/File.h"
#include "Services/Folders.h"
#include "Visuals/Palette.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall ThemeManager::SetStyle(const String& styleName)
{
    // check if the style has already been loaded into the Style manager
    auto styleNameNoSpaces = StringReplace(styleName, " ", "", TReplaceFlags(rfReplaceAll | rfIgnoreCase)).LowerCase();
    for (auto name : TStyleManager::StyleNames) {
        auto nameWithoutSpaces = StringReplace(name, " ", "", TReplaceFlags(rfReplaceAll | rfIgnoreCase)).LowerCase();
        if (styleNameNoSpaces == nameWithoutSpaces) {
            // yep, so change to the style
            auto style = TStyleManager::Style[name];
            TStyleManager::SetStyle(style);
            theAppSettings.ActiveStyle = styleName;
            Bus::Publish<ThemeChangedEvent>(ThemeChangedEvent());
            return;
        }
    }
    // no, so load the new style into the Style manager
    auto styleFile = Services::File::Combine(Services::Folders::GetFolder(Services::Folders::lpApplication, "Styles"), styleName + ".vsf");
    if (Services::File::Exists(styleFile)) {
        // and if loaded, then set it
        TStyleManager::SetStyle(TStyleManager::LoadFromFile(styleFile));
        theAppSettings.ActiveStyle = styleName;
        Bus::Publish<ThemeChangedEvent>(ThemeChangedEvent());
    }
}
//---------------------------------------------------------------------------
void __fastcall ThemeManager::LoadStyles(TComboBox* combo)
{
    combo->Items->Clear();
    // load the styles from the styles folder
    const auto activeStyle = theAppSettings.ActiveStyle;
    auto styles = GetStyles();
    // load them into the combo box
    for (auto styleFile : styles) {
        auto styleName = Services::File::NameWithoutExtension(styleFile);
        combo->Items->Add(styleName);
        if (styleName == activeStyle) {
            // set the current style as the selected item
            combo->ItemIndex = combo->Items->Count - 1;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ThemeManager::ReapplyStyle()
{
    // force a change back to the current style to reapply it for a hidden form on activation
    auto style = TStyleManager::ActiveStyle->Name;
    // force a change to a different style
    TStyleManager::SetStyle(style == TStyleManager::StyleNames[0] ? TStyleManager::StyleNames[1] : TStyleManager::StyleNames[0]);
    // then change back to the active style
    TStyleManager::SetStyle(style);
}
//---------------------------------------------------------------------------
TStringDynArray __fastcall ThemeManager::GetStyles()
{
    return Services::Folders::GetFiles(Services::Folders::lpApplication, "*.vsf", "Styles");
}
//---------------------------------------------------------------------------
TColor __fastcall ThemeManager::GetColor(int index)
{
    switch (index) {
    // highlight
    case 0: {
        auto c1 = StyleServices()->GetSystemColor(clHighlight);
        auto c2 = StyleServices()->GetSystemColor(clActiveCaption);
        auto d1 = Visuals::Palette::Diff(c1);
        auto d2 = Visuals::Palette::Diff(c2);
        return d1 > d2 ? c1 : c2;
    }
    // background
    case 1: {
        auto c1 = StyleServices()->GetSystemColor(clBackground);
        auto c2 = StyleServices()->GetSystemColor(clBtnFace);
        auto d1 = Visuals::Palette::LuminanceOf(c1);
        auto d2 = Visuals::Palette::LuminanceOf(c2);
        return d1 > d2 ? c1 : c2;
    }
    // shadow
    case 3: {
        auto c1 = StyleServices()->GetSystemColor(clBtnShadow);
        auto c2 = StyleServices()->GetSystemColor(clInactiveCaption);
        auto d1 = Visuals::Palette::LuminanceOf(c1);
        auto d2 = Visuals::Palette::LuminanceOf(c2);
        return d1 > d2 ? c1 : c2;
    }
    // foreground
    default:
        return StyleServices()->GetSystemColor(clBtnText);
    }
}
//---------------------------------------------------------------------------

