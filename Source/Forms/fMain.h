//---------------------------------------------------------------------------
#ifndef fMainH
#define fMainH
//- VCL ---------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
//- STL ---------------------------------------------------------------------
#include <memory>
//- APP ---------------------------------------------------------------------
#include "Frames/WelcomeDialog/fWelcomeDialog.h"
#include "Frames/IDE/fIDE.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:    // IDE-managed Components
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormBeforeMonitorDpiChanged(TObject *Sender, int OldDPI, int NewDPI);
    void __fastcall FormAfterMonitorDpiChanged(TObject *Sender, int OldDPI, int NewDPI);

private:    // User declarations
    __fastcall  void                OnIDEClose(TObject *Sender);
    __fastcall  void                OnWelcomeDone(TObject *Sender);
    __fastcall  void                ShowWelcomeDialog();
    __fastcall  void                ShowIDE();
    __fastcall  void                SaveSettings();

    __fastcall  TfrmWelcomeDialog*  GetWelcome();
    __fastcall  TfrmIDE*            GetIDE();
    __fastcall  TFrame*             GetActiveForm();

private:

    enum TFormView
    {
        fvNone,
        fvWelcomeDialog,
        fvGameIDE,
    };

    TFormView                           m_FormView;
    std::unique_ptr<TfrmWelcomeDialog>  m_WelcomeFrame;
    std::unique_ptr<TfrmIDE>            m_IDEFrame;

    __property      TfrmWelcomeDialog*  Welcome = { read = GetWelcome    };
    __property      TfrmIDE*            IDE     = { read = GetIDE        };
    __property      TFrame*             Active  = { read = GetActiveForm };

public:        // User declaration
                        __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
