//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#include "Frames/MapEditor/AssetSelection.h"
#include "Frames/MapEditor/LabelledImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
static int g_NextAssetId = 0;
//---------------------------------------------------------------------------
__fastcall TfrmAssetSelection::TfrmAssetSelection(TComponent* Owner)
: TFrame(Owner)
, FOnImageClick(nullptr)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::Clear()
{
    for (auto c = panList->ControlCount - 1; c >= 0 ; c--)
    {
        auto cc = dynamic_cast<TfrmLabelledImage*>(panList->Controls[c]);
        if (cc)
        {
            delete cc;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::Add(ImageDocument* image, bool enabled)
{
    auto control = new TfrmLabelledImage(this);
    control->Name = "LabelledImage" + IntToStr(++g_NextAssetId);
    control->Parent = panList;
    control->Image = image;
    control->Enabled = enabled;
    control->OnSelectedClick = OnImageClick;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::Select(const ImageDocument* image)
{
    for (auto i = 0; i < panList->ControlCount; i++)
    {
        auto control = dynamic_cast<TfrmLabelledImage*>(panList->Controls[i]);
        if (control != nullptr && control->Image->Id == image->Id)
        {
            control->Selected = true;
            control->Refresh();
            sbxList->VertScrollBar->Position = control->Top;
            sbxList->Update();
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::UpdateDocument(const ImageDocument* image)
{
    for (auto i = 0; i < panList->ControlCount; i++)
    {
        auto control = dynamic_cast<TfrmLabelledImage*>(panList->Controls[i]);
        if (control != nullptr && control->Image->Id == image->Id)
        {
            control->Update();
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::OnImageClick(TObject* Sender)
{
    auto image = dynamic_cast<TfrmLabelledImage*>(Sender);
    if (image != nullptr && FOnImageClick != nullptr)
    {
        FOnImageClick(image->Image);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::sbxListMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    Handled = true;
    sbxList->VertScrollBar->Position -= WheelDelta;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::sbxListResize(TObject *Sender)
{
    auto my = 0;
    for (auto c = 0; c < panList->ControlCount; c++)
    {
        my = std::max(my, panList->Controls[c]->Top + panList->Controls[c]->Height);
    }
    panList->Height = std::max(my, sbxList->Height);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::mnuToggleLabelsClick(TObject *Sender)
{
    for (auto c = 0; c < panList->ControlCount; c++)
    {
        auto label = dynamic_cast<TfrmLabelledImage*>(panList->Controls[c]);
        if (label)
        {
            label->ShowCaption = mnuToggleLabels->Checked;
        }
    }
    sbxListResize(nullptr);
}
//---------------------------------------------------------------------------
int __fastcall TfrmAssetSelection::FindSelected()
{
    for (auto c = 0; c < panList->ControlCount; c++)
    {
        auto label = dynamic_cast<TfrmLabelledImage*>(panList->Controls[c]);
        if (label && label->Selected)
        {
            return c;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::Next()
{
    auto ci = FindSelected();
    if (ci != -1)
    {
        ci = (ci + 1) % panList->ControlCount;
        if (ci == 0) ci = 1;
        auto label = dynamic_cast<TfrmLabelledImage*>(panList->Controls[ci]);
        if (label)
        {
            label->Selected = true;
            Select(label->Image);
            OnImageClick(label);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::Prev()
{
    auto ci = FindSelected();
    if (ci != -1)
    {
        ci = (panList->ControlCount + (ci - 1)) % panList->ControlCount;
        if (ci == 0) ci = panList->ControlCount - 1;
        auto label = dynamic_cast<TfrmLabelledImage*>(panList->Controls[ci]);
        if (label)
        {
            label->Selected = true;
            Select(label->Image);
            OnImageClick(label);
        }
    }
}
//---------------------------------------------------------------------------

