//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Forms\fMain.cpp", frmMain);
USEFORM("Frames\fEditorCode.cpp", frmEditorCode); /* TFrame: File Type */
USEFORM("Frames\fEditorImage.cpp", frmEditorImage); /* TFrame: File Type */
USEFORM("Frames\fEditorMap.cpp", frmEditorMap); /* TFrame: File Type */
USEFORM("Forms\fAbout.cpp", frmAbout);
USEFORM("Frames\fEditorMusic.cpp", frmEditorMusic); /* TFrame: File Type */
USEFORM("Frames\fIDE.cpp", frmIDE); /* TFrame: File Type */
USEFORM("Frames\fSelectionPanel.cpp", SelectionPanelFrame); /* TFrame: File Type */
USEFORM("Frames\fWelcomeDialog.cpp", frmWelcomeDialog); /* TFrame: File Type */
USEFORM("Frames\fImportDialog.cpp", frmImportDialog); /* TFrame: File Type */
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
         Application->Initialize();
         Application->MainFormOnTaskBar = true;
         if (appSettings.ActiveStyle.Trim() != "")
             TStyleManager::TrySetStyle(appSettings.ActiveStyle);
         else
             TStyleManager::TrySetStyle("Auric");
         Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->Run();
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
