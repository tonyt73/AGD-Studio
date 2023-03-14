//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fMultiImageView.h"
#include "fSelectionImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TMultiImageViewFrame::TMultiImageViewFrame(TComponent* Owner)
: TFrame(Owner)
, m_Scale(4)
, FOnClick(nullptr)
{
}
//---------------------------------------------------------------------------
void __fastcall TMultiImageViewFrame::SetScale(int scale)
{
    m_Scale = scale;
    for (auto i = 0; i < panImages->ControlCount; i++)
    {
        auto control = panImages->Controls[i];
        if (control->ClassNameIs("TSelectionImageFrame"))
        {
            auto image = static_cast<TSelectionImageFrame*>(control);
            image->Scale = scale;
            auto w = image->Width;
            image->Left = i * w;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMultiImageViewFrame::Clear()
{
    while (panImages->ControlCount)
    {
        panImages->RemoveControl(panImages->Controls[0]);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMultiImageViewFrame::Add(const Agdx::GraphicsBuffer& image, const String& hint)
{
    static int i = 0;
    auto control = new TSelectionImageFrame(this, image, hint);
    control->Name = "SelectionImageFrame" + IntToStr(++i);
    control->Update();
    panImages->InsertControl(control);
    control->Scale = m_Scale;
    control->Selected = panImages->ControlCount == 1;
    control->Top = 0;
    control->Left = (panImages->ControlCount - 1) * control->Width;
    control->Tag = (panImages->ControlCount - 1);
    control->OnSelectedClick = OnFrameClicked;
    panImages->Width = panImages->ControlCount * control->Width;
    panImages->Height = control->Height;
    panImages->Left = 0;
    panImages->Top = 0;
    Height = panImages->Height + 20;
}
//---------------------------------------------------------------------------
void __fastcall TMultiImageViewFrame::Select(int index)
{
    for (auto i = 0; i < panImages->ControlCount; i++)
    {
        auto control = panImages->Controls[i];
        if (control->ClassNameIs("TSelectionImageFrame"))
        {
            static_cast<TSelectionImageFrame*>(control)->Selected = control->Tag == index;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMultiImageViewFrame::FrameMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    if (Shift.Contains(ssCtrl))
    {
        Handled = true;
        auto adjust = WheelDelta != 0 ? (WheelDelta / (WheelDelta > 0 ? WheelDelta : -WheelDelta)) : 0;
        Scale = std::max(1, std::min(16 , m_Scale + adjust));
        panImages->Width = panImages->ControlCount * panImages->Controls[0]->Width;
        panImages->Height = panImages->Controls[0]->Height;
        Height = panImages->Height + 20;
    }
    else if (!Shift.Contains(ssShift))
    {
        Handled = true;
        HorzScrollBar->Position += WheelDelta;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMultiImageViewFrame::Timer1Timer(TObject *Sender)
{
    for (auto i = 0; i < panImages->ControlCount; i++)
    {
        auto control = panImages->Controls[i];
        if (control->ClassNameIs("TSelectionImageFrame"))
        {
            auto image = ((TSelectionImageFrame*)control);
            image->Update();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMultiImageViewFrame::OnFrameClicked(TObject *Sender)
{
    if (FOnClick != nullptr) FOnClick(Sender);
}
//---------------------------------------------------------------------------
