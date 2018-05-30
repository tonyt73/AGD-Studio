//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "fColors.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "fPaletteAttribute"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmColors::TfrmColors(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmColors::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = false;
}
//---------------------------------------------------------------------------
