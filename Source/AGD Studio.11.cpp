//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Messaging/Messaging.h"
#include "Project/Documents/Settings.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include <assert.h>
#include <windows.h>
//---------------------------------------------------------------------------
USEFORM("Frames\IDE\fIDE.cpp", frmIDE); /* TFrame: File Type */
USEFORM("Frames\WelcomeDialog\fSelectionPanel.cpp", SelectionPanelFrame); /* TFrame: File Type */
USEFORM("Frames\WelcomeDialog\fWelcomeDialog.cpp", frmWelcomeDialog); /* TFrame: File Type */
USEFORM("Frames\Editors\Map\fAssetSelection.cpp", frmAssetSelection); /* TFrame: File Type */
USEFORM("Frames\Editors\Map\fEditorMap.cpp", frmEditorMap); /* TFrame: File Type */
USEFORM("Frames\Editors\Map\fLabelledImage.cpp", frmLabelledImage); /* TFrame: File Type */
USEFORM("Frames\Editors\Music\fEditorMusic.cpp", frmEditorMusic); /* TFrame: File Type */
USEFORM("Frames\Editors\Window\fEditorWindow.cpp", frmEditorWindow); /* TFrame: File Type */
USEFORM("Frames\Editors\Messages\fEditorMessages.cpp", frmEditorMessages); /* TFrame: File Type */
USEFORM("Forms\fAbout.cpp", frmAbout);
USEFORM("Frames\Editors\Images\fEditorImage.cpp", frmEditorImage); /* TFrame: File Type */
USEFORM("Frames\Editors\Images\fMultiImageView.cpp", MultiImageViewFrame); /* TFrame: File Type */
USEFORM("Frames\Editors\Images\fPaletteAttribute.cpp", frmPaletteAttribute); /* TFrame: File Type */
USEFORM("Frames\Editors\Images\fBlockTypes.cpp", frmBlockTypes); /* TFrame: File Type */
USEFORM("Frames\Editors\Images\fPaletteBitmap.cpp", frmPaletteBitmap); /* TFrame: File Type */
USEFORM("Frames\Editors\Images\fToolbarShape.cpp", frmToolbarShape); /* TFrame: File Type */
USEFORM("Frames\Editors\Images\fULAplusBitmap.cpp", frmULAplusBitmap); /* TFrame: File Type */
USEFORM("Frames\Editors\JumpTable\fEditorJumpTable.cpp", frmEditorJumpTable); /* TFrame: File Type */
USEFORM("Frames\Editors\Images\fPaletteMonoAttribute.cpp", frmPaletteMonoAttribute); /* TFrame: File Type */
USEFORM("Frames\Editors\Images\fSelectionImage.cpp", SelectionImageFrame); /* TFrame: File Type */
USEFORM("Frames\Editors\Images\fToolbar.cpp", frmToolbar); /* TFrame: File Type */
USEFORM("Forms\fSettings.cpp", frmSettings);
USEFORM("Frames\Editors\Code\fEditorCode.cpp", frmEditorCode); /* TFrame: File Type */
USEFORM("Frames\Editors\Controls\fEditorControls.cpp", frmEditorControls); /* TFrame: File Type */
USEFORM("Forms\fAdvancedSettings.cpp", frmAdvancedSettings);
USEFORM("Forms\fMain.cpp", frmMain);
USEFORM("Forms\fNewImage.cpp", frmNewImage);
USEFORM("Frames\Editors\Controls\fKeyCapture.cpp", frmKeyCode); /* TFrame: File Type */
USEFORM("Frames\Editors\fEditor.cpp", frmEditor); /* TFrame: File Type */
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
    try
    {
         Application->Initialize();
         Application->MainFormOnTaskBar = true;
         ThemeManager::SetStyle(theAppSettings.ActiveStyle.Trim() != "" ? theAppSettings.ActiveStyle : "Windows 10 Black Pearl");
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
