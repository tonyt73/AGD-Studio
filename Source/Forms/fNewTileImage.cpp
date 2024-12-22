//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "fNewTileImage.h"
#include "Project/Documents/DocumentManager.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ElEdits"
#pragma link "ElSpin"
#pragma link "ElXPThemedControl"
#pragma link "LMDBaseControl"
#pragma link "LMDBaseGraphicControl"
#pragma link "LMDGraphicControl"
#pragma link "LMDHTMLLabel"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmNewTileImage::TfrmNewTileImage(TComponent* Owner)
: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewTileImage::FormCreate(TObject *Sender)
{
    // get the type of image
    auto type = Visuals::itTile;
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
int __fastcall TfrmNewTileImage::GetWidth() const
{
    return edtWidth->Value;
}
//---------------------------------------------------------------------------
int __fastcall TfrmNewTileImage::GetHeight() const
{
    return edtHeight->Value;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewTileImage::tbcImageTypesDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect, bool Active)
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
void __fastcall TfrmNewTileImage::edtWidthChange(TObject *Sender)
{
    auto tx = edtWidth->Value  / edtWidth->MinValue;
    auto ty = edtHeight->Value / edtHeight->MinValue;
    auto tc = tx * ty;
    lblTiles->Caption = IntToStr(tx) + " x " + IntToStr(ty) + " is " + IntToStr(tc) + (tc == 1 ? " tile" : " tiles");
}
//---------------------------------------------------------------------------

