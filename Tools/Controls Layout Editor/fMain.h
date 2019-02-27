//---------------------------------------------------------------------------
#ifndef fMainH
#define fMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.VirtualImageList.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <list>
#include "..\..\Frames\WndProcHandlers.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TActionList *actMain;
    TFileOpen *actFileOpen;
    TFileSaveAs *actFileSaveAs;
    TFileExit *actFileExit;
    TAction *actFileSave;
    TToolBar *ToolBar1;
    TImageCollection *ImageCollection1;
    TVirtualImageList *VirtualImageList1;
    TToolButton *btnNew;
    TToolButton *btnOpen;
    TToolButton *btnSave;
    TToolButton *ToolButton5;
    TToolButton *btnKeyboard;
    TAction *actAddKeyboard;
    TToolButton *ToolButton7;
    TAction *actModeRectangle;
    TToolButton *btnRect;
    TAction *actFileNew;
    TAction *actModeSelect;
    TToolButton *btnSelect;
    TOpenDialog *dlgOpen;
    TToolButton *ToolButton4;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomActual;
    TAction *actZoomFit;
    TToolButton *btnZoomIn;
    TToolButton *btnZoomOut;
    TToolButton *btnZoomActual;
    TToolButton *btnZoomFit;
    TAction *actModeTest;
    TToolButton *ToolButton1;
    TPanel *Panel1;
    TPanel *panView;
    TImage *imgView;
    TPanel *Panel2;
    TListBox *ListBox1;
    void __fastcall actAddKeyboardExecute(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall actFileSaveExecute(TObject *Sender);
    void __fastcall actModeRectangleExecute(TObject *Sender);
    void __fastcall actModeSelectExecute(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomActualExecute(TObject *Sender);
    void __fastcall actZoomFitExecute(TObject *Sender);
    void __fastcall actFileOpenAccept(TObject *Sender);
    void __fastcall actModeTestExecute(TObject *Sender);
    void __fastcall actFileNewExecute(TObject *Sender);
private:	// User declarations
    enum EditMode { emSelect, emDrawRect };

    EditMode                m_EditMode;
    float                   m_Scale;
    TPngImage*              m_Keyboard;
    std::list<EraseHandler> m_EraseHandlers;    // stops flicking
public:		// User declarations
            __fastcall  TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
