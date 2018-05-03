//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fNewImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmNewImage::TfrmNewImage(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
String __fastcall TfrmNewImage::GetName() const
{
    return edtName->Text;
}
//---------------------------------------------------------------------------
int __fastcall TfrmNewImage::GetWidth() const
{
    return edtWidth->Value;
}
//---------------------------------------------------------------------------
int __fastcall TfrmNewImage::GetHeight() const
{
    return edtHeight->Value;
}
//---------------------------------------------------------------------------
String __fastcall TfrmNewImage::GetType() const
{
    if (radObject->Checked)
        return "Object";
    if (radSprite->Checked)
        return "Sprite";
    return "Tile";
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::radObjectClick(TObject *Sender)
{
    edtWidth->Value = 16;
    edtHeight->Value = 16;
    edtWidth->Enabled = false;
    edtHeight->Enabled = false;
    lblWidth->Enabled = false;
    lblHeight->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::radTileClick(TObject *Sender)
{
    edtWidth->Value = 16;
    edtHeight->Value = 16;
    edtWidth->Enabled = true;
    edtHeight->Enabled = true;
    lblWidth->Enabled = true;
    lblHeight->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::edtWidthExit(TObject *Sender)
{
    if (edtWidth->Value % 8 != 0)
    {
        edtWidth->Value = ((int)(edtWidth->Value / 8)) * 8;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::edtHeightExit(TObject *Sender)
{
    if (edtHeight->Value % 8 != 0)
    {
        edtHeight->Value = ((int)(edtHeight->Value / 8)) * 8;
    }
}
//---------------------------------------------------------------------------
