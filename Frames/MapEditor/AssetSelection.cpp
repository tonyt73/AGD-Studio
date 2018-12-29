//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "AssetSelection.h"
#include "LabelledImage.h"
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
void __fastcall TfrmAssetSelection::Add(ImageDocument* image)
{
	auto control = new TfrmLabelledImage(this);
	control->Name = "LabelledImage" + IntToStr(++g_NextAssetId);
	control->Parent = panList;
	control->Image = image;
	control->OnSelectedClick = OnImageClick;
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
void __fastcall TfrmAssetSelection::ScrollBox1MouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    int a = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAssetSelection::ScrollBox1Resize(TObject *Sender)
{
    auto my = 0;
    for (auto c = 0; c < panList->ControlCount; c++)
    {
        my = std::max(my, panList->Controls[c]->Top + panList->Controls[c]->Height);
    }
    panList->Height = my;
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
    ScrollBox1Resize(nullptr);
}
//---------------------------------------------------------------------------
