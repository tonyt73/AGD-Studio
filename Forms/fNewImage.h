//---------------------------------------------------------------------------
#ifndef fNewImageH
#define fNewImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "LMDBaseEdit.hpp"
#include "LMDControl.hpp"
#include "LMDCustomBevelPanel.hpp"
#include "LMDCustomControl.hpp"
#include "LMDCustomEdit.hpp"
#include "LMDCustomExtSpinEdit.hpp"
#include "LMDCustomMaskEdit.hpp"
#include "LMDCustomPanel.hpp"
#include "LMDSpinEdit.hpp"
//---------------------------------------------------------------------------
class TfrmNewImage : public TForm
{
__published:    // IDE-managed Components
    TButton *btnOk;
    TButton *btnCancel;
    TPanel *Panel1;
    TLabel *Label1;
    TEdit *edtName;
    TRadioButton *radObject;
    TRadioButton *radSprite;
    TRadioButton *radTile;
    TLabel *lblWidth;
    TLabel *lblHeight;
    TRadioButton *radChrSet;
    TLMDSpinEdit *edtWidth;
    TLMDSpinEdit *edtHeight;
    void __fastcall radObjectClick(TObject *Sender);
    void __fastcall edtWidthExit(TObject *Sender);
    void __fastcall edtHeightExit(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall edtNameChange(TObject *Sender);
private:    // User declarations
    String  __fastcall  GetName() const;
    int     __fastcall  GetWidth() const;
    int     __fastcall  GetHeight() const;
    String  __fastcall  GetType() const;
public:    // User declarations
    __fastcall TfrmNewImage(TComponent* Owner);

    String  __property  Name = { read = GetName };
    int     __property  Width = { read = GetWidth };
    int     __property  Height = { read = GetHeight };
    String  __property  Type = { read = GetType };
};
//---------------------------------------------------------------------------
#endif
