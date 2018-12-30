//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fSelectionPanel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSelectionPanelFrame::TSelectionPanelFrame(TComponent* Owner)
: TFrame(Owner)
, m_Selected(false)
, m_Highlighted(false)
, FOnClick(nullptr)
, FOnRemoveClick(nullptr)
{
    panProjectInfo->Color = StyleServices()->GetStyleColor(scGenericGradientEnd);
    panRemove->Color = StyleServices()->GetStyleColor(scGenericGradientEnd);
    lblProjectName->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    lblProjectPath->Font->Color = StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    panRemove->Visible = false;
}
//---------------------------------------------------------------------------
__fastcall TSelectionPanelFrame::~TSelectionPanelFrame()
{
    Parent = nullptr;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::panProjectInfoMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    Highlighted = true;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::SetName(String name)
{
    m_Name = name;
    lblProjectName->Caption = name;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::SetPath(String path)
{
    m_Path = path;
    lblProjectPath->Caption = path;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::SetMachine(String machine)
{
    m_Machine = machine;
    lblMachine->Caption = machine;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::SetSelected(bool state)
{
    m_Selected = state;
    UpdateControl();
    if (state)
    {
        // change all other TSelectionPanelFrames
        for (int i = 0; i < Parent->ControlCount; i++)
        {
            TSelectionPanelFrame* frame = dynamic_cast<TSelectionPanelFrame*>(Parent->Controls[i]);
            if (frame != nullptr && frame != this)
            {
                frame->Selected = false;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::SetHighlighted(bool state)
{
    m_Highlighted = state;
    UpdateControl();
    if (state)
    {
        // change all other TSelectionPanelFrames
        for (int i = 0; i < Parent->ControlCount; i++)
        {
            TSelectionPanelFrame* frame = dynamic_cast<TSelectionPanelFrame*>(Parent->Controls[i]);
            if (frame != nullptr && frame != this)
            {
                frame->Highlighted = false;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::SetLoading(bool state)
{
    ProgressBar1->Visible = state;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::UpdateControl()
{
    TColor color = StyleServices()->GetStyleColor(m_Selected ? scButtonFocused : (m_Highlighted ? scButtonHot : scGenericGradientEnd));
    panProjectInfo->Color = color;
    panRemove->Color = color;
    panRemove->Visible = m_Highlighted;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::Tick()
{
    ProgressBar1->StepIt();
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::lblProjectNameClick(TObject *Sender)
{
    Selected = true;
    if (FOnClick != nullptr) FOnClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::imgRemoveClick(TObject *Sender)
{
    if (FOnRemoveClick != nullptr) FOnRemoveClick(this);
}
//---------------------------------------------------------------------------

