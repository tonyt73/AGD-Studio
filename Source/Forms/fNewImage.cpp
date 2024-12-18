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
    // set up the controls for the current image type
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
        default:
        case 2: return "Tile";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::tbcImageTypesDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
{
    // clear the rect
    Control->Canvas->Brush->Color = ThemeManager::Background;
    Control->Canvas->FillRect(Rect);

    // get the bottom 8 pixels as a rect
    auto rect = Rect.SplitRect(srBottom, 8);
    // is active?
    if (Active) {
        // yes, change the brush color to highlight
        Control->Canvas->Brush->Color = ThemeManager::Highlight;
        // draw the bottom rect in the current brush color
        rect.Inflate(-2, 2, -1, 2);
        Control->Canvas->FillRect(rect);
        Control->Canvas->Font->Style <<= fsBold;
    } else {
        // no, draw a rectangle (not filled rect) at the bottom in the highlight color
        rect.Inflate(-2, 0, -1, 0);
        Control->Canvas->Pen->Color = ThemeManager::Highlight;
        Control->Canvas->Rectangle(rect);
        Control->Canvas->Font->Style >>= fsBold;
    }

    // draw the caption
    auto tab = dynamic_cast<TTabControl*>(Control);
    auto caption = tab->Tabs->Strings[TabIndex];
    auto tr = Control->Canvas->TextExtent(caption);
    Control->Canvas->Brush->Color = ThemeManager::Background;
    Control->Canvas->Font->Color = ThemeManager::Foreground;
    Control->Canvas->TextOut(Rect.Left + ((Rect.Width() - tr.cx) / 2), Rect.Top + ((Rect.Height() - tr.cy) / 2) - 3, caption);
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewImage::tbcImageTypesChange(TObject *Sender)
{
    // get the type of image
    auto type = (Visuals::ImageTypes)tbcImageTypes->TabIndex;
    // and its configuration
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    // enabled the edit controls, based on it config

    // width
    edtWidth->Enabled = mc.ImageSizing[type].Step.cx != 0;
    lblWidth->Enabled = mc.ImageSizing[type].Step.cx != 0;
    edtWidth->MinValue = mc.ImageSizing[type].Minimum.cx;
    edtWidth->MaxValue = mc.ImageSizing[type].Maximum.cx;
    edtWidth->Increment = mc.ImageSizing[type].Step.cx;
    edtWidth->Value = mc.ImageSizing[type].Minimum.cx;

    // and height
    edtHeight->Enabled = mc.ImageSizing[type].Step.cy != 0;
    lblHeight->Enabled = mc.ImageSizing[type].Step.cy != 0;
    edtHeight->MaxValue = mc.ImageSizing[type].Maximum.cy;
    edtHeight->MinValue = mc.ImageSizing[type].Minimum.cy;
    edtHeight->Increment = mc.ImageSizing[type].Step.cy;
    edtHeight->Value = mc.ImageSizing[type].Minimum.cy;
}
//---------------------------------------------------------------------------

