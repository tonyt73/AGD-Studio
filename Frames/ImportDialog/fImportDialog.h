//---------------------------------------------------------------------------

#ifndef fImportDialogH
#define fImportDialogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TfrmImportDialog : public TFrame
{
__published:	// IDE-managed Components
    TImage *Image1;
    TLabel *lblFile;
    TLabel *lblProjectName;
    TLabel *lblMachine;
    TButton *btnCancel;
    TButton *btnImport;
    TEdit *edtFile;
    TComboBox *cmbMac;
    TEdit *edtProjectName;
    TButton *btnOpen;
    TLabel *lblDestMachine;
    TComboBox *cmbDestMachine;
    TOpenTextFileDialog *dlgImport;
    void __fastcall edtFileChange(TObject *Sender);
    void __fastcall btnOpenClick(TObject *Sender);
    void __fastcall btnImportClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
    void __fastcall UpdateColors();

private:    // Events
    TNotifyEvent            FOnDone;

public:		// User declarations
            __fastcall      TfrmImportDialog(TComponent* Owner);

    void    __fastcall      Initialise();

    __property TNotifyEvent OnDone = { read = FOnDone, write = FOnDone };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmImportDialog *frmImportDialog;
//---------------------------------------------------------------------------
#endif
