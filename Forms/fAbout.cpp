//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fAbout.h"
#include <ctime>
#include <iomanip>
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//--------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormDeactivate(TObject *Sender)
{
    Close();
    delete this;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormCreate(TObject *Sender)
{
    lblVersion->Font->Color = ThemeManager::Foreground;
    lblBuild->Font->Color = ThemeManager::Foreground;
    lblCopyright->Font->Color = ThemeManager::Foreground;
    lblAGDCopyright->Font->Color = ThemeManager::Foreground;
    shpFrame->Pen->Color = ThemeManager::Highlight;
    Color = ThemeManager::Background;
    // read application file version and update the labels
    int Major, Minor, Release, Build;
    GetBuildVersion(Major, Minor, Release, Build);
    lblVersion->Caption = "Version " + IntToStr(Major) + "." + IntToStr(Minor);
    lblBuild->Caption = "Build #AGDx-" + IntToStr(Major)+"."+IntToStr(Minor)+", built on " + DatePlusDays(Release);
}
//---------------------------------------------------------------------------
String __fastcall TfrmAbout::DatePlusDays(int days) const
{
    struct tm date = {0, 0, 12, 1, 0, 2000 - 1900};
    char datestr[64];
    time_t date_seconds = mktime(&date) + (days * 24 * 60 * 60);
    strftime(datestr, 64, "%B %d, %Y", localtime(&date_seconds));
    return String(datestr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::GetBuildVersion(int& Major, int& Minor, int& Release, int& Build) const
{
    Major       = 0;
    Minor       = 0;
    Release     = 0;
    Build       = 0;
    DWORD temp  = 0;
    DWORD infoLen = GetFileVersionInfoSize(Application->ExeName.c_str(), &temp);
    if (infoLen > 0)
    {
        VS_FIXEDFILEINFO* fileInfo;
        auto pBuf = (char*)malloc(infoLen);
        auto res = GetFileVersionInfo(Application->ExeName.c_str(), 0, infoLen, pBuf);
        if (VerQueryValue((void*)pBuf, L"\\", (LPVOID*)(&fileInfo), (unsigned int*)&temp))
        {
            Major   = (int)((fileInfo->dwFileVersionMS >> 16) & 0xffff);
            Minor   = (int)((fileInfo->dwFileVersionMS      ) & 0xffff);
            Release = (int)((fileInfo->dwFileVersionLS >> 16) & 0xffff);
            Build   = (int)((fileInfo->dwFileVersionLS      ) & 0xffff);
        }
        free(pBuf);
    }
}
//---------------------------------------------------------------------------
