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
//- STL ---------------------------------------------------------------------
#include <memory>
#include <Frames/fAppFrame.h>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:    // IDE-managed Components
    void            __fastcall  FormCreate(TObject *Sender);
    void            __fastcall  FormDestroy(TObject *Sender);
    void            __fastcall  FormCloseQuery(TObject *Sender, bool &CanClose);
    void            __fastcall  FormActivate(TObject *Sender);
    void            __fastcall  FormBeforeMonitorDpiChanged(TObject *Sender, int OldDPI, int NewDPI);
    void            __fastcall  FormAfterMonitorDpiChanged(TObject *Sender, int OldDPI, int NewDPI);
    void            __fastcall  FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);

private:    // User declarations
    void            __fastcall  OnIDEClose(TObject *Sender);
    void            __fastcall  OnWelcomeDone(TObject *Sender);
    void            __fastcall  ShowWelcomeDialog();
    void            __fastcall  ShowIDE();
    void            __fastcall  SaveSettings();

    TfrmAppFrame*   __fastcall  GetWelcome();
    TfrmAppFrame*   __fastcall  GetIDE();
    TfrmAppFrame*   __fastcall  GetActiveForm();

private:

    enum TFormView
    {
        fvNone,
        fvWelcomeDialog,
        fvGameIDE
    };

    TFormView                       m_FormView;
    std::unique_ptr<TfrmAppFrame>   m_WelcomeFrame;
    std::unique_ptr<TfrmAppFrame>   m_IDEFrame;

    __property      TfrmAppFrame*   Welcome = { read = GetWelcome    };
    __property      TfrmAppFrame*   IDE     = { read = GetIDE        };
    __property      TfrmAppFrame*   Active  = { read = GetActiveForm };

public:        // User declaration
                    __fastcall  TfrmMain(TComponent* Owner) override;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
