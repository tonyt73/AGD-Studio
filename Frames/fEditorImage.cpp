//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fEditorImage.h"
#include "DocumentManager.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDDckSite"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorImage::TfrmEditorImage(TComponent* Owner)
: TFrame(Owner)
, m_Magnification(8)
{
    ::Messaging::Bus::Subscribe<Event>(OnEvent);
}
//---------------------------------------------------------------------------
__fastcall TfrmEditorImage::~TfrmEditorImage()
{
	::Messaging::Bus::Unsubscribe<Event>(OnEvent);
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditorImage::IsActive() const
{
    return static_cast<TLMDDockPanel*>(m_Image->DockPanel)->Active;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::OnEvent(const Event& event)
{
    if (IsActive() && m_ActionMap.count(event.Id) == 1)
    {
        m_ActionMap[event.Id]->Execute();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::SetDocument(Document* document)
{
    m_ActionMap["zoom.in"] = actZoomIn;
    m_ActionMap["zoom.out"] = actZoomOut;
    m_ActionMap["zoom.reset"] = actZoomReset;

    m_Image = dynamic_cast<ImageDocument*>(document);
    //Color = StyleServices()->GetStyleColor(scGenericGradientBase);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::FrameEndDock(TObject *Sender, TObject *Target, int X, int Y)
{
    TLMDDockPanel* dp = dynamic_cast<TLMDDockPanel*>(Sender);
    assert(dp != nullptr);
    barStatus->Visible = dp->Site->IsFloatingDoc;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actSelectExecute(TObject *Sender)
{
    if (IsActive())
    {
        actSelect->Checked = true;
        btnTool->ImageIndex = actSelect->ImageIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actPencilExecute(TObject *Sender)
{
    if (IsActive())
    {
        actPencil->Checked = true;
        btnTool->ImageIndex = actPencil->ImageIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actBrushExecute(TObject *Sender)
{
    if (IsActive())
    {
        actBrush->Checked = true;
        btnTool->ImageIndex = actBrush->ImageIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actFillExecute(TObject *Sender)
{
    if (IsActive())
    {
        actFill->Checked = true;
        btnTool->ImageIndex = actFill->ImageIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actSprayBrushExecute(TObject *Sender)
{
    if (IsActive())
    {
        actSprayBrush->Checked = true;
        btnTool->ImageIndex = actSprayBrush->ImageIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actEraserExecute(TObject *Sender)
{
    if (IsActive())
    {
        actEraser->Checked = true;
        btnTool->ImageIndex = actEraser->ImageIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actLineExecute(TObject *Sender)
{
    if (IsActive())
    {
        actLine->Checked = true;
        btnTool->ImageIndex = actLine->ImageIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actShapeExecute(TObject *Sender)
{
    if (IsActive())
    {
        actShape->Checked = true;
        btnTool->ImageIndex = actShape->ImageIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actTextExecute(TObject *Sender)
{
    if (IsActive())
    {
        actText->Checked = true;
        btnTool->ImageIndex = actText->ImageIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actDropperExecute(TObject *Sender)
{
    if (IsActive())
    {
        actDropper->Checked = true;
        btnTool->ImageIndex = actDropper->ImageIndex;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actGridPixelExecute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actGridCharacterExecute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateLeftExecute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateRightExecute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateUpExecute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateDownExecute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actFlipVerticalExecute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actFlipHorizontalExecute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateLeft90Execute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateRight90Execute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actMonoOnExecute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actMonoOffExecute(TObject *Sender)
{
    if (IsActive())
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::panEditorContainerClick(TObject *Sender)
{
    SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actZoomInExecute(TObject *Sender)
{
    m_Magnification = std::min(64, m_Magnification + 2);
    sbxViewResize(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actZoomOutExecute(TObject *Sender)
{
    m_Magnification = std::max(8, m_Magnification - 2);
    sbxViewResize(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actZoomResetExecute(TObject *Sender)
{
    m_Magnification = 8;
    sbxViewResize(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::sbxViewResize(TObject *Sender)
{
    if (theDocumentManager.ProjectConfig())
    {

        const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
        const auto& gm = mc.GraphicsMode();
        auto vw = (int)(m_Image->Width  * gm->ScalarX * m_Magnification);
        auto vh = (int)(m_Image->Height * gm->ScalarY * m_Magnification);
        if (vw + 256 > sbxView->Width || vh + 256 > sbxView->Height)
        {
            // no auto alignment
            panEditorContainer->Align = alNone;
            panEditorContainer->Left = 0;
            panEditorContainer->Top = 0;
            panEditorContainer->Width = std::max(vw + 256, sbxView->Width);
            panEditorContainer->Height = std::max(vh + 256, sbxView->Height);
        }
        else
        {
            panEditorContainer->Align = alClient;
        }
        // work out the padding to center the image
        auto pw = (panEditorContainer->Width  - vw) >> 1;
        auto ph = (panEditorContainer->Height - vh) >> 1;
        panEditorContainer->Padding->Left = pw;
        panEditorContainer->Padding->Top = ph;
        panEditorContainer->Padding->Right = (panEditorContainer->Width - vw) - pw;
        panEditorContainer->Padding->Bottom = (panEditorContainer->Height - vh) - ph;
    }
}
//---------------------------------------------------------------------------

