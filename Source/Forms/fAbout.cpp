//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include <ctime>
#include <iomanip>
#include <systdate.h>
#include <System.StrUtils.hpp>
#include "Settings/ThemeManager.h"
#include "fAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//--------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormDeactivate(TObject* /*Sender*/)
{
    Close();
    delete this;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormCreate(TObject* /*Sender*/)
{
    lblVersion->Font->Color = ThemeManager::Foreground;
    lblBuild->Font->Color = ThemeManager::Foreground;
    lblCopyright->Font->Color = ThemeManager::Foreground;
    lblAGDCopyright->Font->Color = ThemeManager::Foreground;
    shpFrame->Pen->Color = ThemeManager::Highlight;
    Color = ThemeManager::Background;
    // read application file version and update the labels
    int Major, Minor, BuildDate, BuildTime, Patch;
    GetBuildVersion(Major, Minor, BuildDate, BuildTime, Patch);
    auto version = IntToStr(Major) + "." + IntToStr(Minor);
    if (Patch != 0) {
        version += "." + IntToStr(Patch);
    }
    lblVersion->Caption = "Version " + version;
    lblBuild->Caption = "Build# AGD Studio " + version + ", built on " + DatePlusDays(BuildDate);
    lblCopyright->Caption = ReplaceStr(lblCopyright->Caption, "(c)", TDateTime::CurrentDate().FormatString("yyyy"));
}
//---------------------------------------------------------------------------
String __fastcall TfrmAbout::DatePlusDays(int days) const
{
    struct tm date = { 0, 0, 12, 1, 0, 2000 - 1900, 0, 0, 0 };
    char datestr[64];
    time_t date_seconds = mktime(&date) + (days * 24 * 60 * 60);
    strftime(datestr, 64, "%B %d, %Y", localtime(&date_seconds));
    return String(datestr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::GetBuildVersion(int& Major, int& Minor, int& Date, int& Time, int& Patch) const
{
    Major = 0;
    Minor = 0;
    Date  = 0;
    Time  = 0;
    DWORD temp  = 0;
    DWORD infoLen = GetFileVersionInfoSize(Application->ExeName.c_str(), &temp);
    if (infoLen > 0) {
        VS_FIXEDFILEINFO* fileInfo;
        auto pBuf = static_cast<char*>(malloc(infoLen));
        GetFileVersionInfo(Application->ExeName.c_str(), 0, infoLen, pBuf);
        if (VerQueryValue(static_cast<void*>(pBuf), L"\\", reinterpret_cast<LPVOID*>(&fileInfo), reinterpret_cast<unsigned int*>(&temp))) {
            Major = HIWORD(fileInfo->dwFileVersionMS);
            Minor = LOWORD(fileInfo->dwFileVersionMS);
            Date  = HIWORD(fileInfo->dwFileVersionLS);
            Time  = LOWORD(fileInfo->dwFileVersionLS);
            Patch = HIWORD(fileInfo->dwProductVersionLS);
        }
        free(pBuf);
    }
}
//---------------------------------------------------------------------------
