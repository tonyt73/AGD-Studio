//---------------------------------------------------------------------------
#ifndef fColorsH
#define fColorsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "fPaletteAttribute.h"
//---------------------------------------------------------------------------
class TfrmColors : public TForm
{
__published:	// IDE-managed Components
    TfrmPaletteAttribute *frmAttribute;
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmColors(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
