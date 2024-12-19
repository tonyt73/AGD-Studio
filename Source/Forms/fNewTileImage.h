//---------------------------------------------------------------------------
#ifndef fNewTileImageH
#define fNewTileImageH
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
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDGraphicControl.hpp"
#include "LMDHTMLLabel.hpp"
//---------------------------------------------------------------------------
class TfrmNewTileImage : public TForm
{
__published:    // IDE-managed Components
    TButton *btnOk;
    TButton *btnCancel;
    TPanel *Panel1;
    TLabel *lblWidth;
    TLabel *lblHeight;
    TElSpinEdit *edtWidth;
    TElSpinEdit *edtHeight;
    TLMDHTMLLabel *LMDHTMLLabel1;
    TLabel *lblTiles;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall tbcImageTypesDrawTab(TCustomTabControl *Control, int TabIndex,
          const TRect &Rect, bool Active);
    void __fastcall edtWidthChange(TObject *Sender);
private:    // User declarations
    int     __fastcall  GetWidth() const;
    int     __fastcall  GetHeight() const;
public:    // User declarations
    __fastcall          TfrmNewTileImage(TComponent* Owner);

    __property  int     Width  = { read = GetWidth  };
    __property  int     Height = { read = GetHeight };
};
//---------------------------------------------------------------------------
#endif
