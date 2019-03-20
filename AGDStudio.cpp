//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <System.IOUtils.hpp>
#include <System.SysUtils.hpp>
//---------------------------------------------------------------------------
USEFORM("Forms\fHidden.cpp", AppBuilder);
//---------------------------------------------------------------------------
void __fastcall LaunchStudio()
{
    SHELLEXECUTEINFO ShExecInfo;
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = NULL;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = L"open";
    ShExecInfo.lpFile = L"AGD Studio.exe";
    ShExecInfo.lpParameters = ParamStr(1).c_str();
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_NORMAL;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
}
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
         Application->Initialize();
         Application->MainFormOnTaskBar = false;
         Application->CreateForm(__classid(TAppBuilder), &AppBuilder);
         for (auto i = 0; i < 100; i++)
         {
             Sleep(10);
             Application->ProcessMessages();
         }
         LaunchStudio();
         Sleep(1000);
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
