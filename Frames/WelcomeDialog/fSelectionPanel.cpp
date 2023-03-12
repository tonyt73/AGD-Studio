//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#include <Vcl.Imaging.pngimage.hpp>
#include "fSelectionPanel.h"
#include "System/File.h"
#include "Project/MachineConfig.h"
#include "Settings/ThemeManager.h"
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
    panProjectInfo->Color = ThemeManager::Background;//StyleServices()->GetStyleColor(scGenericGradientEnd);
    panRemove->Color = ThemeManager::Background;//StyleServices()->GetStyleColor(scGenericGradientEnd);
    lblProjectName->Font->Color = ThemeManager::Foreground;//StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    lblProjectPath->Font->Color = ThemeManager::Foreground;//StyleServices()->GetStyleFontColor(sfSmCaptionTextNormal);
    imgRemove->Visible = false;
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
    lblProjectPath->Caption = System::File::PathOf(path);

    auto file = System::File::Combine(System::File::Combine(System::Path::Projects, m_Name), m_Name + ".png");
    if (System::File::Exists(file))
    {
        auto image = std::make_unique<TPngImage>();
        image->LoadFromFile(file);
        imgLogo->Picture->Assign(image.get());
        imgLogo->Visible = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::SetMachine(String machine)
{
    m_Machine = machine;
    lblMachine->Caption = machine;

    if (!imgLogo->Visible)
    {
        auto mc = std::make_unique<MachineConfig>(machine);
        mc->Load(machine);
        if (mc->Image.Trim() != "")
        {
            auto file = System::File::Combine(System::Path::Application, mc->Image);
            if (System::File::Exists(file))
            {
                auto image = std::make_unique<TPngImage>();
                image->LoadFromFile(file);
                imgLogo->Picture->Assign(image.get());
                imgLogo->Visible = true;
            }
        }
    }
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
    prgLoading->Visible = state;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::UpdateControl()
{
    TColor color = m_Selected ? ThemeManager::Highlight : (m_Highlighted ? ThemeManager::Highlight : ThemeManager::Background);
    panProjectInfo->Color = color;
    panRemove->Color = color;
    imgRemove->Visible = m_Highlighted;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionPanelFrame::Tick()
{
    prgLoading->StepIt();
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

