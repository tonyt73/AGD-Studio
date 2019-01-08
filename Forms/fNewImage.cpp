//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fNewImage.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDBaseEdit"
#pragma link "LMDControl"
#pragma link "LMDCustomBevelPanel"
#pragma link "LMDCustomControl"
#pragma link "LMDCustomEdit"
#pragma link "LMDCustomExtSpinEdit"
#pragma link "LMDCustomMaskEdit"
#pragma link "LMDCustomPanel"
#pragma link "LMDSpinEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmNewImage::TfrmNewImage(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::FormCreate(TObject *Sender)
{
    radObjectClick(radObject);
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
    auto type = (ImageTypes)((TControl*)Sender)->Tag;
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    edtWidth->Enabled = mc.ImageSizing[type].Step.cx != 0;
    lblWidth->Enabled = mc.ImageSizing[type].Step.cx != 0;
    edtWidth->MinValue = mc.ImageSizing[type].Minimum.cx;
    edtWidth->MaxValue = mc.ImageSizing[type].Maximum.cx;
    edtWidth->Step = mc.ImageSizing[type].Step.cx;
    edtWidth->Value = mc.ImageSizing[type].Minimum.cx;

    edtHeight->Enabled = mc.ImageSizing[type].Step.cy != 0;
    lblHeight->Enabled = mc.ImageSizing[type].Step.cy != 0;
    edtHeight->MaxValue = mc.ImageSizing[type].Maximum.cy;
    edtHeight->MinValue = mc.ImageSizing[type].Minimum.cy;
    edtHeight->Step = mc.ImageSizing[type].Step.cy;
    edtHeight->Value = mc.ImageSizing[type].Minimum.cy;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::edtWidthExit(TObject *Sender)
{
    if (((int)edtWidth->Value % (int)edtWidth->Step) != 0)
    {
        edtWidth->Value = ((int)((edtWidth->Value + edtWidth->Step / 2) / edtWidth->Step)) * edtWidth->Step;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::edtHeightExit(TObject *Sender)
{
    if (((int)edtHeight->Value % (int)edtHeight->Step) != 0)
    {
        edtHeight->Value = ((int)((edtHeight->Value + edtHeight->Step / 2) / edtHeight->Step)) * edtHeight->Step;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::edtNameChange(TObject *Sender)
{
    btnOk->Enabled = edtName->Text.Trim() != "";
}
//---------------------------------------------------------------------------

