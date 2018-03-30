//---------------------------------------------------------------------------
#ifndef fMainH
#define fMainH
//- VCL ---------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
//- STL ---------------------------------------------------------------------
#include <memory>
//- APP ---------------------------------------------------------------------
#include "fWelcomeDialog.h"
#include "fIDE.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
	void __fastcall AppMessage(tagMSG &Msg, bool &Handled);
	void __fastcall OnIDEClose(TObject *Sender);
	void __fastcall OnWelcomeDone(TObject *Sender);
	void __fastcall ShowWelcomeDialog();
	void __fastcall ShowIDE();
    void __fastcall SaveSettings();

private:

	enum TFormView
	{
		fvNone,
		fvWelcomeDialog,
		fvGameIDE,
		//fvPluginIDE,
	};

	TFormView   						    m_FormView;
	std::unique_ptr<TfrmWelcomeDialog>	    m_WelcomeDialog;
	std::unique_ptr<TfrmIDE>			    m_IDEDialog;

public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
