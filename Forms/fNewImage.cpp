//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fNewImage.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmNewImage::TfrmNewImage(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::FormCreate(TObject *Sender)
{
    radObjectClick(NULL);
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
    if (radTile->Checked)
        return "Tile";
    return "Character Set";
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::radObjectClick(TObject *Sender)
{
    edtWidth->Value = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itObject].Minimum.cx;
    edtHeight->Value = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itObject].Minimum.cy;
    edtWidth->Enabled = false;
    edtHeight->Enabled = false;
    lblWidth->Enabled = false;
    lblHeight->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::radSpriteClick(TObject *Sender)
{
    edtWidth->Value = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itSprite].Minimum.cx;
    edtHeight->Value = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itSprite].Minimum.cy;
    edtWidth->Enabled = false;
    edtHeight->Enabled = false;
    lblWidth->Enabled = false;
    lblHeight->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::radTileClick(TObject *Sender)
{
    edtWidth->Value = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itTile].Minimum.cx;
    edtHeight->Value = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itTile].Minimum.cy;
    edtWidth->Enabled = true;
    edtHeight->Enabled = true;
    lblWidth->Enabled = true;
    lblHeight->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::radChrSetClick(TObject *Sender)
{
    edtWidth->Value = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itCharacterSet].Minimum.cx;
    edtHeight->Value = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itCharacterSet].Minimum.cy;
    edtWidth->Enabled = false;
    edtHeight->Enabled = false;
    lblWidth->Enabled = false;
    lblHeight->Enabled = false;
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
void __fastcall TfrmNewImage::edtNameChange(TObject *Sender)
{
    btnOk->Enabled = edtName->Text.Trim() != "";
}
//---------------------------------------------------------------------------

