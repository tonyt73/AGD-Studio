//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "fNewImage.h"
#include "Project/Documents/DocumentManager.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ElEdits"
#pragma link "ElSpin"
#pragma link "ElXPThemedControl"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmNewImage::TfrmNewImage(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::FormCreate(TObject *Sender)
{
    // do not allow multiple character sets
    if (dynamic_cast<Project::Document*>(theDocumentManager.Get("Image", "Character Set", "Game Font")) != nullptr) {
        // remove font as an image option
        tbcImageTypes->Tabs->Delete(3);
        tbcImageTypes->TabWidth = (tbcImageTypes->Width / 3) - 1;
    }

    // check current type values
    tbcImageTypesChange(nullptr);
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
    switch (tbcImageTypes->TabIndex) {
        case 0: return "Object";
        case 1: return "Sprite";
        case 2: return "Tile";
        default: return "Character Set";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::edtWidthExit(TObject *Sender)
{
    if (edtWidth->Enabled && (int)edtWidth->Value % (int)edtWidth->Increment != 0) {
        edtWidth->Value = ((int)((edtWidth->Value + edtWidth->Increment / 2) / edtWidth->Increment)) * edtWidth->Increment;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::edtHeightExit(TObject *Sender)
{
    if (edtHeight->Enabled && (int)edtHeight->Value % (int)edtHeight->Increment != 0) {
        edtHeight->Value = ((int)((edtHeight->Value + edtHeight->Increment / 2) / edtHeight->Increment)) * edtHeight->Increment;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::tbcImageTypesDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
{
    Control->Canvas->Brush->Color = ThemeManager::Background;
    Control->Canvas->FillRect(Rect);

    auto rect = Rect.SplitRect(srBottom, 8);
    Control->Canvas->Brush->Color = Active ? ThemeManager::Highlight : ThemeManager::Shadow;
    auto dy = Active ? 2 : -1;
    rect.Inflate(-2, dy, -1, dy);
    Control->Canvas->FillRect(rect);

    // draw the caption
    auto tab = dynamic_cast<TTabControl*>(Control);
    auto caption = tab->Tabs->Strings[TabIndex];
    auto tr = Control->Canvas->TextExtent(caption);
    Control->Canvas->Brush->Color = ThemeManager::Background;
    tab->Font->Color = ThemeManager::Foreground;
    Control->Canvas->TextOut(Rect.Left + ((Rect.Width() - tr.cx) / 2), Rect.Top + ((Rect.Height() - tr.cy) / 2) - 3, caption);
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::tbcImageTypesChange(TObject *Sender)
{
    auto type = (Visuals::ImageTypes)tbcImageTypes->TabIndex;
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

