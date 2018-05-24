//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fEditorImage.h"
#include "DocumentManager.h"
#include "Messaging/Messaging.h"
#include "Frames/fSelectionImage.h"
#include "Frames/ImageEditor/PencilTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDDckSite"
#pragma link "fMultiImageView"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorImage::TfrmEditorImage(TComponent* Owner)
: TFrame(Owner)
, m_Magnification(8.f)
, m_SelectedFrame(0)
, m_ImageDocument(nullptr)
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
    return static_cast<TLMDDockPanel*>(m_ImageDocument->DockPanel)->Active;
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
    m_ActionMap["edit.undo"] = actUndo;
    m_ActionMap["edit.redo"] = actRedo;

//    m_ToolMap[btnSelect.Tag] = std::make_unique<SelectTool>();
//    m_ToolMap[btnText.Tag] = std::make_unique<TextTool>();
    m_ToolMap[btnPencil->Tag] = std::make_unique<PencilTool>();
//    m_ToolMap[btnBrush.Tag] = std::make_unique<BrushTool>();
//    m_ToolMap[btnLine.Tag] = std::make_unique<LineTool>();
//    m_ToolMap[btnShape.Tag] = std::make_unique<ShapeTool>();
//    m_ToolMap[btnDropper.Tag] = std::make_unique<DropperTool>();
//    m_ToolMap[btnSprayBrush.Tag] = std::make_unique<SprayBrushTool>();
//    m_ToolMap[btnFill.Tag] = std::make_unique<FillTool>();
//    m_ToolMap[btnEraser.Tag] = std::make_unique<EraserTool>();

//    m_ToolMap[btnRotateLeft.Tag] = std::make_unique<RotateLeftTool>();
//    m_ToolMap[btnRotateRight.Tag] = std::make_unique<RotateRightTool>();
//    m_ToolMap[btnRotateDown.Tag] = std::make_unique<RotateDownTool>();
//    m_ToolMap[btnRotateUp.Tag] = std::make_unique<RotateUpTool>();
//    m_ToolMap[btnFlipHorizontal.Tag] = std::make_unique<FlipHorizontalTool>();
//    m_ToolMap[btnFlipvertical.Tag] = std::make_unique<FlipverticalTool>();
//    m_ToolMap[btnRotateLeft90.Tag] = std::make_unique<RotateLeft90Tool>();
//    m_ToolMap[btnRotateRight90.Tag] = std::make_unique<RotateRight90Tool>();

    m_ImageDocument = dynamic_cast<ImageDocument*>(document);
    panEditorContainer->Color = StyleServices()->GetStyleColor(scGenericGradientBase);

    // convert the documents images into frames
    fFrameView->OnSelectedClick = OnFrameSelected;
    RefreshFramesView();
    imgEditor->Picture->Bitmap->PixelFormat = pf32bit;
    if (m_ImageDocument->CanModifyFrames)
    {
        fFrameView->PopupMenu = popFrames;
    }

    // default tool: pencil
    actPencil->Checked = true;
    btnTool->ImageIndex = actPencil->ImageIndex;
    m_PaintTool = btnPencil->Tag;
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
        m_PaintTool = btnPencil->Tag;
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
        RefreshView();
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
        for (int i = 0; i < m_ImageDocument->Frames; i++)
        {
            m_Frames[i]->Canvas().RenderInGreyscale = true;
        }
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actMonoOffExecute(TObject *Sender)
{
    if (IsActive())
    {
        for (int i = 0; i < m_ImageDocument->Frames; i++)
        {
            m_Frames[i]->Canvas().RenderInGreyscale = false;
        }
        RefreshView();
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
    sbxView->HorzScrollBar->Position = 0;
    sbxView->VertScrollBar->Position = 0;
    m_Magnification = std::min(64.f, m_Magnification + 2.f);
    sbxViewResize(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actZoomOutExecute(TObject *Sender)
{
    sbxView->HorzScrollBar->Position = 0;
    sbxView->VertScrollBar->Position = 0;
    m_Magnification = std::max(8.f, m_Magnification - 2.f);
    sbxViewResize(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actZoomResetExecute(TObject *Sender)
{
    m_Magnification = 8.f;
    sbxViewResize(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::sbxViewResize(TObject *Sender)
{
    if (theDocumentManager.ProjectConfig())
    {

        const auto& gm = theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode();
        auto vw = (int)(m_ImageDocument->Width  * gm->ScalarX * m_Magnification) + 2;
        auto vh = (int)(m_ImageDocument->Height * gm->ScalarY * m_Magnification) + 2;
        if (vw + 256 > sbxView->Width || vh + 256 > sbxView->Height)
        {
            // no auto alignment
            panEditorContainer->Align = alNone;
            panEditorContainer->Width = std::max(vw + 256, sbxView->Width);
            panEditorContainer->Height = std::max(vh + 256, sbxView->Height);
            panEditorContainer->Left = 0;
            panEditorContainer->Top = 0;
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
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::DrawGrids()
{
    const auto& gm = *(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode());
    auto fScalarX = gm.ScalarX;
    auto fScalarY = gm.ScalarY;
    auto Canvas = imgEditor->Picture->Bitmap->Canvas;

    auto xs = 0;
    auto xe = m_ImageDocument->Width * fScalarX * m_Magnification;
    auto ys = 0;
    auto ye = m_ImageDocument->Height * fScalarY * m_Magnification;
    if (true == btnGridPixel->Down && 4 <= m_Magnification)
    {
        Canvas->Pen->Color = (TColor)0x00004080;
        for (auto x = xs; x <= xe; x++)
        {
            Canvas->MoveTo(x * fScalarX * m_Magnification, ys);
            Canvas->LineTo(x * fScalarX * m_Magnification, ye);
        }
        for (auto y = ys; y <= ye; y++)
        {
            Canvas->MoveTo(xs, y * fScalarY * m_Magnification);
            Canvas->LineTo(xe, y * fScalarY * m_Magnification);
        }
    }
    if (true == btnGridCharacter->Down)
    {
        Canvas->Pen->Color = (TColor)0x0048BAF7;
        for (auto x = xs; x <= xe; x += (8 / gm.ScalarX))
        {
            Canvas->MoveTo(x * fScalarX * m_Magnification, ys);
            Canvas->LineTo(x * fScalarX * m_Magnification, ye);
        }
        for (auto y = ys; y <= ye; y += (8 / gm.ScalarY))
        {
            Canvas->MoveTo(xs    , y * fScalarY * m_Magnification);
            Canvas->LineTo(xe + 1, y * fScalarY * m_Magnification);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::RefreshView()
{
    fFrameView->Select(m_SelectedFrame);
    if (m_ImageDocument != nullptr)
    {
        // match the internal bitmap to the image components size (this stops the grids from showing a fat lines)
        imgEditor->Picture->Bitmap->Width = imgEditor->Width;
        imgEditor->Picture->Bitmap->Height = imgEditor->Height;
        // take the image canvas that we are editing and show it on the image editor view
        m_Frames[m_SelectedFrame]->Canvas().Draw(imgEditor->Picture->Bitmap);
        //draw grids over it
        DrawGrids();
        // show it
        imgEditor->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::RefreshFramesView()
{
    m_Frames.clear();
    fFrameView->Clear();
    const auto& gm = *(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode());
    for (int i = 0; i < m_ImageDocument->Frames; i++)
    {
        // make an image canvas
        auto image = std::make_unique<Agdx::Image>(m_ImageDocument->Width, m_ImageDocument->Height, gm);
        // set the graphic of the canvas from the image documents frame
        image->Canvas().Set(m_ImageDocument->Frame[i]);
        // add the new canvas to the frame view; along with a hint (character set only)
        fFrameView->Add(image->Canvas(), m_ImageDocument->Hint[i]);
        // save the image canvas in the list of editable frames
        m_Frames.push_back(std::move(image));
    }
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::sbxViewMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    if (Shift.Contains(ssCtrl))
    {
        Handled = true;
        float delta = WheelDelta / (Shift.Contains(ssShift) ? 50.f : 200.f);
        m_Magnification = std::max(8.0f, std::min(64.f, m_Magnification + delta));
        sbxViewResize(NULL);
    }
    else
    {
        Handled = true;
        float delta = -WheelDelta / (Shift.Contains(ssShift) ? 5.f : 20.f);
        sbxView->VertScrollBar->Position += delta;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::OnFrameSelected(TObject *Sender)
{
    auto frame = dynamic_cast<TSelectionImageFrame*>(Sender);
    if (frame != nullptr)
    {
        m_SelectedFrame = frame->Tag;
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::popAddFrameClick(TObject *Sender)
{
    m_ImageDocument->AddFrame();
    RefreshFramesView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::popInsertFrameClick(TObject *Sender)
{
    m_ImageDocument->AddFrame(m_SelectedFrame);
    RefreshFramesView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::popRemoveFrameClick(TObject *Sender)
{
    m_ImageDocument->DeleteFrame(m_SelectedFrame);
    m_SelectedFrame = 0;
    RefreshFramesView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actAnimatePlayExecute(TObject *Sender)
{
    btnAnimatePlay->Down = true;
    tmrAnimate->Enabled = true;
    tbrTools->Enabled = false;
    tbrShiftRotates->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actAnimateStopExecute(TObject *Sender)
{
    btnAnimateStop->Down = true;
    tmrAnimate->Enabled = false;
    tbrTools->Enabled = true;
    tbrShiftRotates->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actToggleAnimationExecute(TObject *Sender)
{
    if (btnAnimatePlay->Down)
    {
        actAnimateStopExecute(Sender);
    }
    else
    {
        actAnimatePlayExecute(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::tmrAnimateTimer(TObject *Sender)
{
    m_SelectedFrame = (m_SelectedFrame + 1) % m_ImageDocument->Frames;
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actUndoExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRedoExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
TPoint __fastcall TfrmEditorImage::ToImagePt(int X, int Y)
{
    auto x = (X / (float)imgEditor->Width) * m_ImageDocument->Width;
    auto y = (Y / (float)imgEditor->Height) * m_ImageDocument->Height;
    return TPoint(x, y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::imgEditorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (btnAnimateStop->Down)
    {
        if (m_ToolMap.count(m_PaintTool) == 1)
        {
            auto undo = m_ToolMap[m_PaintTool].get()->Begin(m_Frames[m_SelectedFrame]->Canvas(), ToImagePt(X,Y), Shift);
            RefreshView();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::imgEditorMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    if (btnAnimateStop->Down)
    {
        if (m_ToolMap.count(m_PaintTool) == 1)
        {
            m_ToolMap[m_PaintTool]->Move(m_Frames[m_SelectedFrame]->Canvas(), ToImagePt(X,Y), Shift);
            RefreshView();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::imgEditorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (btnAnimateStop->Down)
    {
        if (m_ToolMap.count(m_PaintTool) == 1)
        {
            auto redo = m_ToolMap[m_PaintTool]->End(m_Frames[m_SelectedFrame]->Canvas(), ToImagePt(X,Y));
            m_ImageDocument->Frame[m_SelectedFrame] = m_Frames[m_SelectedFrame]->Canvas().Get();
            RefreshView();
        }
    }
}
//---------------------------------------------------------------------------

