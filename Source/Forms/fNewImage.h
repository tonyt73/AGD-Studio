//---------------------------------------------------------------------------
#ifndef fNewImageH
#define fNewImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Samples.Spin.hpp>
//---------------------------------------------------------------------------
class TfrmNewImage : public TForm
{
__published:    // IDE-managed Components
    TButton *btnOk;
    TButton *btnCancel;
    TPanel *Panel1;
    TRadioButton *radObject;
    TRadioButton *radSprite;
    TRadioButton *radTile;
    TLabel *lblWidth;
    TSpinEdit *edtWidth;
    TLabel *lblHeight;
    TSpinEdit *edtHeight;
    TRadioButton *radChrSet;
    void __fastcall radObjectClick(TObject *Sender);
    void __fastcall edtWidthExit(TObject *Sender);
    void __fastcall edtHeightExit(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:    // User declarations
    int     __fastcall  GetWidth() const;
    int     __fastcall  GetHeight() const;
    String  __fastcall  GetType() const;
public:    // User declarations
    __fastcall TfrmNewImage(TComponent* Owner);

    int     __property  Width  = { read = GetWidth  };
    int     __property  Height = { read = GetHeight };
    String  __property  Type   = { read = GetType   };
};
//---------------------------------------------------------------------------
#endif
