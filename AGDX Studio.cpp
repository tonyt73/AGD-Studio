//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
#include "Settings/Settings.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include <assert.h>
//---------------------------------------------------------------------------
//USEFORM("Forms\fNewImage.cpp", frmNewImage);
USEFORM("Frames\WindowEditor\fEditorWindow.cpp", frmEditorWindow); /* TFrame: File Type */
USEFORM("Frames\WelcomeDialog\fWelcomeDialog.cpp", frmWelcomeDialog); /* TFrame: File Type */
USEFORM("Frames\WelcomeDialog\fSelectionPanel.cpp", SelectionPanelFrame); /* TFrame: File Type */
USEFORM("Frames\MapEditor\LabelledImage.cpp", frmLabelledImage); /* TFrame: File Type */
USEFORM("Frames\MapEditor\fEditorMap.cpp", frmEditorMap); /* TFrame: File Type */
USEFORM("Frames\MapEditor\AssetSelection.cpp", frmAssetSelection); /* TFrame: File Type */
USEFORM("Frames\JumpEditor\fEditorJump.cpp", frmEditorJump); /* TFrame: File Type */
USEFORM("Frames\MusicEditor\fEditorMusic.cpp", frmEditorMusic); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fULAplusBitmap.cpp", frmULAplusBitmap); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fEditorImage.cpp", frmEditorImage); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fBlockTypes.cpp", frmBlockTypes); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fMultiImageView.cpp", MultiImageViewFrame); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fToolbarShape.cpp", frmToolbarShape); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fToolbar.cpp", frmToolbar); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fSelectionImage.cpp", SelectionImageFrame); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fPaletteBitmap.cpp", frmPaletteBitmap); /* TFrame: File Type */
USEFORM("Frames\ImageEditor\fPaletteAttribute.cpp", frmPaletteAttribute); /* TFrame: File Type */
USEFORM("Forms\fNewImage.cpp", frmNewImage);
USEFORM("Forms\fMain.cpp", frmMain);
USEFORM("Forms\fAbout.cpp", frmAbout);
USEFORM("Forms\fSettings.cpp", frmSettings);
USEFORM("Frames\IDE\fIDE.cpp", frmIDE); /* TFrame: File Type */
USEFORM("Frames\CodeEditor\fEditorCode.cpp", frmEditorCode); /* TFrame: File Type */
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    try
    {
         Application->Initialize();
         Application->MainFormOnTaskBar = true;
         TStyleManager::TrySetStyle("Onyx Blue");
         TStyleManager::TrySetStyle(appSettings.ActiveStyle.Trim() != "" ? appSettings.ActiveStyle : "Onyx Blue");
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
