//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
//---------------------------------------------------------------------------
//USEFORM("Forms\fNewImage.cpp", frmNewImage);
USEFORM("Frames\IDE\fIDE.cpp", frmIDE); /* TFrame: File Type */
USEFORM("Frames\CodeEditor\fEditorCode.cpp", frmEditorCode); /* TFrame: File Type */
USEFORM("Forms\fSettings.cpp", frmSettings);
USEFORM("Forms\fNewImage.cpp", frmNewImage);
USEFORM("Forms\fMain.cpp", frmMain);
USEFORM("Forms\fAbout.cpp", frmAbout);
USEFORM("Frames\MusicEditor\fEditorMusic.cpp", frmEditorMusic); /* TFrame: File Type */
USEFORM("Frames\MapEditor\fEditorMap.cpp", frmEditorMap); /* TFrame: File Type */
USEFORM("Frames\ImportDialog\fImportDialog.cpp", frmImportDialog); /* TFrame: File Type */
USEFORM("Frames\WelcomeDialog\fWelcomeDialog.cpp", frmWelcomeDialog); /* TFrame: File Type */
USEFORM("Frames\WelcomeDialog\fSelectionPanel.cpp", SelectionPanelFrame); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fToolbarShape.cpp", frmToolbarShape); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fPaletteAttribute.cpp", frmPaletteAttribute); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fMultiImageView.cpp", MultiImageViewFrame); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fEditorImage.cpp", frmEditorImage); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fToolbar.cpp", frmToolbar); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fSelectionImage.cpp", SelectionImageFrame); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fPaletteBitmap.cpp", frmPaletteBitmap); /* TFrame: File Type */
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
