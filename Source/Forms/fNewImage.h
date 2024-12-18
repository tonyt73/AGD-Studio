//---------------------------------------------------------------------------
#ifndef fNewImageH
#define fNewImageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Tabs.hpp>
#include "ElEdits.hpp"
#include "ElSpin.hpp"
#include "ElXPThemedControl.hpp"
//---------------------------------------------------------------------------
class TfrmNewImage : public TForm
{
__published:    // IDE-managed Components
    TButton *btnOk;
    TButton *btnCancel;
    TPanel *Panel1;
    TLabel *lblWidth;
    TLabel *lblHeight;
    TElSpinEdit *edtWidth;
    TElSpinEdit *edtHeight;
    TTabControl *tbcImageTypes;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall tbcImageTypesDrawTab(TCustomTabControl *Control, int TabIndex,
          const TRect &Rect, bool Active);
    void __fastcall tbcImageTypesChange(TObject *Sender);
private:    // User declarations
    int     __fastcall  GetWidth() const;
    int     __fastcall  GetHeight() const;
    String  __fastcall  GetType() const;

    bool                m_FontEnabled;
public:    // User declarations
    __fastcall          TfrmNewImage(TComponent* Owner);

    __property  int     Width  = { read = GetWidth  };
    __property  int     Height = { read = GetHeight };
    __property  String  Type   = { read = GetType   };
};
//---------------------------------------------------------------------------
#endif
