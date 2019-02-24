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
    radObjectClick(radObject);
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
    edtWidth->Increment = mc.ImageSizing[type].Step.cx;
    edtWidth->Value = mc.ImageSizing[type].Minimum.cx;

    edtHeight->Enabled = mc.ImageSizing[type].Step.cy != 0;
    lblHeight->Enabled = mc.ImageSizing[type].Step.cy != 0;
    edtHeight->MaxValue = mc.ImageSizing[type].Maximum.cy;
    edtHeight->MinValue = mc.ImageSizing[type].Minimum.cy;
    edtHeight->Increment = mc.ImageSizing[type].Step.cy;
    edtHeight->Value = mc.ImageSizing[type].Minimum.cy;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::edtWidthExit(TObject *Sender)
{
    if (edtWidth->Value % edtWidth->Increment != 0)
    {
        edtWidth->Value = ((int)((edtWidth->Value + edtWidth->Increment / 2) / edtWidth->Increment)) * edtWidth->Increment;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::edtHeightExit(TObject *Sender)
{
    if (edtHeight->Value % edtHeight->Increment != 0)
    {
        edtHeight->Value = ((int)((edtHeight->Value + edtHeight->Increment / 2) / edtHeight->Increment)) * edtHeight->Increment;
    }
}
//---------------------------------------------------------------------------

