//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "../EditorManager.h"
#include "fEditorImage.h"
#include "fSelectionImage.h"
#include "CanvasPencilTool.h"
#include "CanvasLineTool.h"
#include "CanvasShapeTool.h"
#include "Settings/ThemeManager.h"
#include "Project/Documents/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDDckSite"
#pragma link "fMultiImageView"
#pragma link "fToolbarShape"
#pragma link "fToolbar"
#pragma link "fPaletteAttribute"
#pragma link "fPaletteMonoAttribute"
#pragma link "fPaletteBitmap"
#pragma link "fULAplusBitmap"
#pragma link "fBlockTypes"
#pragma link "fBlockTypes"
#pragma link "fMultiImageView"
#pragma link "fPaletteAttribute"
#pragma link "fPaletteBitmap"
#pragma link "fPaletteMonoAttribute"
#pragma link "fToolbar"
#pragma link "fToolbarShape"
#pragma link "fULAplusBitmap"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorImage::TfrmEditorImage(TComponent* Owner)
: TfrmEditor(Owner, "Image Editor")
, m_ImageDocument(nullptr)
, m_Magnification(8.f)
, m_SelectedFrame(0)
, m_Toolbar(nullptr)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
, m_LastModeString("Pixel Paint Mode - Pencil")
{
    m_KeysHelp =
        "Left Mouse Button         : Use current tool\r\n"
        "                            Hold button and drag mouse to expand, release button to finalise\r\n"
        "Right Mouse Button        : Unset\r\n"
        "Ctrl + Mouse Wheel        : Zoom the window in/out\r\n"
        "                            Hold Shift for faster zoom";
        //"Shift + Left Mouse Button : Pan the window\r\n"
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::OnEvent(const Event& event)
{
    TfrmEditor::OnEvent(event);
    if (IsActive() && m_ActionMap.count(event.Id) == 1) {
        m_ActionMap[event.Id]->Execute();
    } else if (event.Id == "palette.remapped") {
        RefreshView(true);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::OnDocumentSet()
{
    m_EraseHandlerView = std::make_unique<TWinControlHandler>(panViewFrame);
    m_ActionMap["zoom.in"   ] = actZoomIn;
    m_ActionMap["zoom.out"  ] = actZoomOut;
    m_ActionMap["zoom.reset"] = actZoomReset;
    m_ActionMap["edit.undo" ] = actUndo;
    m_ActionMap["edit.redo" ] = actRedo;

    // TODO -cDrawing: Finish the image editor tool set

//    m_CanvasToolMap[static_cast<int>(btnSelect->Tag)] = std::make_unique<ImageSelectTool>();
//    m_CanvasToolMap[static_cast<int>(btnText->Tag)] = std::make_unique<CanvasTextTool>();
    m_CanvasToolMap[static_cast<int>(btnPencil->Tag)] = std::make_unique<CanvasPencilTool>();
//    m_CanvasToolMap[static_cast<int>(btnBrush->Tag)] = std::make_unique<CanvasBrushTool>();
    m_CanvasToolMap[static_cast<int>(btnLine->Tag)] = std::make_unique<CanvasLineTool>();
    m_CanvasToolMap[static_cast<int>(btnShape->Tag)] = std::make_unique<CanvasShapeTool>();
//    m_CanvasToolMap[static_cast<int>(btnDropper->Tag)] = std::make_unique<CanvasDropperTool>();
//    m_CanvasToolMap[static_cast<int>(btnSprayBrush->Tag)] = std::make_unique<CanvasSprayBrushTool>();
//    m_CanvasToolMap[static_cast<int>(btnFill->Tag)] = std::make_unique<CanvasFillTool>();
//    m_CanvasToolMap[static_cast<int>(btnEraser->Tag)] = std::make_unique<CanvasEraserTool>();

//    m_CanvasToolMap[static_cast<int>(btnRotateLeft->Tag)] = std::make_unique<CanvasRotateLeftTool>();
//    m_CanvasToolMap[static_cast<int>(btnRotateRight->Tag)] = std::make_unique<CanvasRotateRightTool>();
//    m_CanvasToolMap[static_cast<int>(btnRotateDown->Tag)] = std::make_unique<CanvasRotateDownTool>();
//    m_CanvasToolMap[static_cast<int>(btnRotateUp->Tag)] = std::make_unique<CanvasRotateUpTool>();
//    m_CanvasToolMap[static_cast<int>(btnFlipHorizontal->Tag)] = std::make_unique<CanvasFlipHorizontalTool>();
//    m_CanvasToolMap[static_cast<int>(btnFlipvertical->Tag)] = std::make_unique<CanvasFlipverticalTool>();
//    m_CanvasToolMap[static_cast<int>(btnRotateLeft90->Tag)] = std::make_unique<CanvasRotateLeft90Tool>();
//    m_CanvasToolMap[static_cast<int>(btnRotateRight90->Tag)] = std::make_unique<CanvasRotateRight90Tool>();

    m_ImageDocument = dynamic_cast<Project::ImageDocument*>(Document);
    panEditorContainer->Color = ThemeManager::Background;
    m_BlockTypeTool.Document = m_ImageDocument;

    // convert the documents images into frames
    fFrameView->OnSelectedClick = OnFrameSelected;
    RefreshFramesView();
    imgEditor->Picture->Bitmap->PixelFormat = pf32bit;
    if (m_ImageDocument->CanModifyFrames) {
        fFrameView->PopupMenu = popFrames;
    }

    // default tool: pencil
    actPencil->Checked = true;
    btnTool->ImageIndex = actPencil->ImageIndex;
    m_CanvasTool = static_cast<int>(btnPencil->Tag);

    palAttribute->Visible = m_GraphicsMode.TypeOfBuffer == Visuals::btAttribute && m_GraphicsMode.LogicalColors == 16;
    palMonoAttribute->Visible = m_GraphicsMode.TypeOfBuffer == Visuals::btAttribute && m_GraphicsMode.LogicalColors == 2;
    palBitmap->Visible = m_GraphicsMode.TypeOfBuffer == Visuals::btBitmap;
    palULAPlus->Visible = m_GraphicsMode.TypeOfBuffer == Visuals::btULAplus;
    palBlocks->Visible = false;
    if (palBitmap->Visible) {
        palBitmap->Init();
    }
    if (palULAPlus->Visible) {
        palULAPlus->Init();
    }
    btnModePaint->Down = true;
    btnModeBlock->Enabled = m_ImageDocument->ImageType == Visuals::itTile;
    barStatus->Panels->Items[0]->Text = "Pixel Paint Mode - Pencil";
    barStatus->Panels->Items[1]->Text = "P=" + UIntToStr(m_ImageDocument->Width) + "x" + UIntToStr(m_ImageDocument->Height) +
                                      ", C=" + UIntToStr(m_ImageDocument->Width  / static_cast<unsigned int>(8 / m_GraphicsMode.ScalarX)) + "x" +
                                               UIntToStr(m_ImageDocument->Height / static_cast<unsigned int>(8 / m_GraphicsMode.ScalarY));
    barStatus->Panels->Items[2]->Text = "0, 0";
    barStatus->Panels->Items[3]->Text = "Graphics Mode: " + m_GraphicsMode.Name + ", Palette: " + m_GraphicsMode.Palette().Name;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::FrameEndDock(TObject* Sender, TObject* /*Target*/, int /*X*/, int /*Y*/)
{
    TLMDDockPanel* dp = dynamic_cast<TLMDDockPanel*>(Sender);
    assert(dp != nullptr);
    //barStatus->Visible = dp->Site->IsFloatingDoc;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::ChangeToolbar(TfrmToolbar* toolbar)
{
    if (m_Toolbar != nullptr) {
        m_Toolbar->Visible = false;
    }
    m_Toolbar = toolbar;
    if (m_Toolbar != nullptr) {
        m_Toolbar->Visible = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actSelectExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        ChangeToolbar(nullptr);
        actSelect->Checked = true;
        btnTool->ImageIndex = actSelect->ImageIndex;
        m_CanvasTool = static_cast<int>(btnSelect->Tag);
        barStatus->Panels->Items[0]->Text = "Pixel Paint Mode - Select";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actPencilExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        ChangeToolbar(nullptr);
        actPencil->Checked = true;
        btnTool->ImageIndex = actPencil->ImageIndex;
        m_CanvasTool = static_cast<int>(btnPencil->Tag);
        barStatus->Panels->Items[0]->Text = "Pixel Paint Mode - Pencil";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actBrushExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        ChangeToolbar(nullptr);
        actBrush->Checked = true;
        btnTool->ImageIndex = actBrush->ImageIndex;
        m_CanvasTool = static_cast<int>(btnBrush->Tag);
        barStatus->Panels->Items[0]->Text = "Pixel Paint Mode - Brush";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actFillExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        ChangeToolbar(nullptr);
        actFill->Checked = true;
        btnTool->ImageIndex = actFill->ImageIndex;
        m_CanvasTool = static_cast<int>(btnFill->Tag);
        barStatus->Panels->Items[0]->Text = "Pixel Paint Mode - Fill";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actSprayBrushExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        ChangeToolbar(nullptr);
        actSprayBrush->Checked = true;
        btnTool->ImageIndex = actSprayBrush->ImageIndex;
        m_CanvasTool = static_cast<int>(btnSprayBrush->Tag);
        barStatus->Panels->Items[0]->Text = "Pixel Paint Mode - Spray Brush";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actLineExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        ChangeToolbar(nullptr);
        actLine->Checked = true;
        btnTool->ImageIndex = actLine->ImageIndex;
        m_CanvasTool = static_cast<int>(btnLine->Tag);
        barStatus->Panels->Items[0]->Text = "Pixel Paint Mode - Line";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actShapeExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        ChangeToolbar(toolbarShape);
        actShape->Checked = true;
        btnTool->ImageIndex = actShape->ImageIndex;
        m_CanvasTool = static_cast<int>(btnShape->Tag);
        barStatus->Panels->Items[0]->Text = "Pixel Paint Mode - Shape";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actTextExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        ChangeToolbar(nullptr);
        actText->Checked = true;
        btnTool->ImageIndex = actText->ImageIndex;
        m_CanvasTool = static_cast<int>(btnText->Tag);
        barStatus->Panels->Items[0]->Text = "Pixel Paint Mode - Text";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actGridPixelExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateLeftExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateRightExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateUpExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateDownExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actFlipVerticalExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actFlipHorizontalExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateLeft90Execute(TObject* /*Sender*/)
{
    if (IsActive()) {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRotateRight90Execute(TObject* /*Sender*/)
{
    if (IsActive()) {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actMonoOnExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        for (int i = 0; i < m_ImageDocument->Frames; i++) {
            m_Frames[i]->Canvas().RenderInGreyscale = true;
        }
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actMonoOffExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        for (int i = 0; i < m_ImageDocument->Frames; i++) {
            m_Frames[i]->Canvas().RenderInGreyscale = false;
        }
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::panEditorContainerClick(TObject* /*Sender*/)
{
    SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actZoomInExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        sbxView->HorzScrollBar->Position = 0;
        sbxView->VertScrollBar->Position = 0;
        m_Magnification = std::min(64.f, m_Magnification * 2.f);
        sbxViewResize(nullptr);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actZoomOutExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        sbxView->HorzScrollBar->Position = 0;
        sbxView->VertScrollBar->Position = 0;
        m_Magnification = std::max(8.f, m_Magnification / 2.f);
        sbxViewResize(nullptr);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actZoomResetExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        m_Magnification = 8.f;
        sbxViewResize(nullptr);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::sbxViewResize(TObject* /*Sender*/)
{
    if (theDocumentManager.ProjectConfig()) {
        const auto& gm = m_GraphicsMode;
        auto vw = m_ImageDocument->Width  * static_cast<unsigned int>(gm.ScalarX * m_Magnification) + 2;
        auto vh = m_ImageDocument->Height * static_cast<unsigned int>(gm.ScalarY * m_Magnification) + 2;
        if (vw + 16 > sbxView->Width || vh + 16 > sbxView->Height) {
            // no auto alignment
            panEditorContainer->Align = alNone;
            panEditorContainer->Width = std::max(vw + 16, static_cast<unsigned int>(sbxView->Width));
            panEditorContainer->Height = std::max(vh + 16, static_cast<unsigned int>(sbxView->Height));
            panEditorContainer->Left = 0;
            panEditorContainer->Top = 0;
        } else {
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
    const auto& gm = m_GraphicsMode;
    auto fScalarX = gm.ScalarX;
    auto fScalarY = gm.ScalarY;
    auto Canvas = imgEditor->Picture->Bitmap->Canvas;

    auto xs = 0;
    auto xe = m_ImageDocument->Width * static_cast<unsigned int>(fScalarX * m_Magnification);
    auto ys = 0;
    auto ye = m_ImageDocument->Height * static_cast<unsigned int>(fScalarY * m_Magnification);
    if (true == btnGridPixel->Down && 4 <= m_Magnification) {
        Canvas->Pen->Color = static_cast<TColor>(0x00004080);
        for (auto x = xs; x <= xe; x++) {
            Canvas->MoveTo(x * static_cast<unsigned int>(fScalarX * m_Magnification), ys);
            Canvas->LineTo(x * static_cast<unsigned int>(fScalarX * m_Magnification), ye);
        }
        for (auto y = ys; y <= ye; y++) {
            Canvas->MoveTo(xs, y * static_cast<unsigned int>(fScalarY * m_Magnification));
            Canvas->LineTo(xe, y * static_cast<unsigned int>(fScalarY * m_Magnification));
        }
    }
    if (true == btnGridCharacter->Down) {
        Canvas->Pen->Color = static_cast<TColor>(0x0048BAF7);
        for (auto x = xs; x <= xe; x += static_cast<int>(8 / gm.ScalarX)) {
            Canvas->MoveTo(x * static_cast<unsigned int>(fScalarX * m_Magnification), ys);
            Canvas->LineTo(x * static_cast<unsigned int>(fScalarX * m_Magnification), ye);
        }
        for (auto y = ys; y <= ye; y += static_cast<int>(8 / gm.ScalarY)) {
            Canvas->MoveTo(xs    , y * static_cast<unsigned int>(fScalarY * m_Magnification));
            Canvas->LineTo(xe + 1, y * static_cast<unsigned int>(fScalarY * m_Magnification));
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::RefreshView(bool redraw)
{
    fFrameView->Select(m_SelectedFrame);
    if (m_ImageDocument != nullptr) {
        // match the internal bitmap to the image components size (this stops the grids from showing a fat lines)
        imgEditor->Picture->Bitmap->Width = imgEditor->Width;
        imgEditor->Picture->Bitmap->Height = imgEditor->Height;
        if (redraw) {
            // force a redraw
            m_Frames[m_SelectedFrame]->Canvas().End();
        }
        if (btnModePaint->Down) {
            // take the image canvas that we are editing and show it on the image editor view
            m_Frames[m_SelectedFrame]->Canvas().Draw(imgEditor->Picture->Bitmap);
        } else {
            // get the block tool to draw its results
            m_BlockTypeTool.Draw(imgEditor->Picture->Bitmap);
        }
        // draw grids over it
        DrawGrids();
        // show it
        imgEditor->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::RefreshFramesView()
{
    m_Frames.clear();
    fFrameView->Clear();
    const auto& gm = m_GraphicsMode;
    for (int i = 0; i < m_ImageDocument->Frames; i++) {
        // make an image canvas
        auto image = std::make_unique<Visuals::Image>(m_ImageDocument->Width, m_ImageDocument->Height, gm);
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
void __fastcall TfrmEditorImage::sbxViewMouseWheel(TObject* /*Sender*/, TShiftState Shift, int WheelDelta, TPoint&, bool &Handled)
{
    if (Shift.Contains(ssCtrl)) {
        Handled = true;
        auto delta = static_cast<float>(WheelDelta) / (Shift.Contains(ssShift) ? 50.f : 200.f);
        m_Magnification = std::max(2.0f, std::min(64.f, m_Magnification + delta));
        sbxViewResize(nullptr);
    } else {
        Handled = true;
        auto delta = static_cast<float>(-WheelDelta) / (Shift.Contains(ssShift) ? 5.f : 20.f);
        sbxView->VertScrollBar->Position += static_cast<int>(delta);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::OnFrameSelected(TObject* Sender)
{
    auto frame = dynamic_cast<TSelectionImageFrame*>(Sender);
    if (frame != nullptr) {
        m_SelectedFrame = static_cast<int>(frame->Tag);
        RefreshView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::popAddFrameClick(TObject* /*Sender*/)
{
    m_ImageDocument->AddFrame();
    RefreshFramesView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::popInsertFrameClick(TObject* /*Sender*/)
{
    m_ImageDocument->AddFrame(m_SelectedFrame);
    RefreshFramesView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::popRemoveFrameClick(TObject* /*Sender*/)
{
    m_ImageDocument->DeleteFrame(m_SelectedFrame);
    m_SelectedFrame = 0;
    RefreshFramesView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actAnimatePlayExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        btnAnimatePlay->Down = true;
        tmrAnimate->Enabled = true;
        tbrTools->Enabled = false;
        tbrBlockType->Enabled = false;
        tbrShiftRotates->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actAnimateStopExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        btnAnimateStop->Down = true;
        tmrAnimate->Enabled = false;
        tbrTools->Enabled = true;
        tbrBlockType->Enabled = true;
        tbrShiftRotates->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actToggleAnimationExecute(TObject* Sender)
{
    if (IsActive()) {
        if (btnAnimatePlay->Down) {
            actAnimateStopExecute(Sender);
        } else {
            actAnimatePlayExecute(Sender);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::tmrAnimateTimer(TObject* /*Sender*/)
{
    m_SelectedFrame = (m_SelectedFrame + 1) % m_ImageDocument->Frames;
    RefreshView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actUndoExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actRedoExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
    }
}
//---------------------------------------------------------------------------
TPoint __fastcall TfrmEditorImage::ToImagePt(int X, int Y)
{
    auto x = (X  * m_ImageDocument->Width ) / imgEditor->Width;
    auto y = (Y  * m_ImageDocument->Height) / imgEditor->Height;
    return TPoint(x, y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::SetCanvasColors()
{
    if (palAttribute->Visible) {
        palAttribute->Set(m_Frames[m_SelectedFrame]->Canvas());
    }
    else if (palMonoAttribute->Visible) {
        palMonoAttribute->Set(m_Frames[m_SelectedFrame]->Canvas());
    }
    else if (palBitmap->Visible) {
        palBitmap->Set(m_Frames[m_SelectedFrame]->Canvas());
    } else if (palULAPlus->Visible) {
        palULAPlus->Set(m_Frames[m_SelectedFrame]->Canvas());
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::imgEditorMouseDown(TObject* /*Sender*/, TMouseButton, TShiftState Shift, int X, int Y)
{
    theEditorManager.SetActive(this);
    if (btnAnimateStop->Down) {
        SetCaptureControl(imgEditor);
        if (btnModePaint->Down) {
            // pixel paint mode
            if (m_CanvasToolMap.count(m_CanvasTool) == 1) {
                m_CanvasToolMap[m_CanvasTool].get()->Parameters = toolbarShape->Parameters();
                SetCanvasColors();
                auto undo = m_CanvasToolMap[m_CanvasTool].get()->Begin(m_Frames[m_SelectedFrame]->Canvas(), ToImagePt(X,Y), Shift);
                RefreshView();
            }
        } else {
            // block type paint
            m_BlockTypeTool.BlockType = palBlocks->BlockType;
            m_BlockTypeTool.Begin(m_Frames[m_SelectedFrame]->Canvas());
            m_BlockTypeTool.Move(ToImagePt(X,Y), Shift);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::imgEditorMouseMove(TObject* /*Sender*/, TShiftState Shift, int X, int Y)
{
    auto w = static_cast<int>(8 / m_GraphicsMode.ScalarX);
    auto h = static_cast<int>(8 / m_GraphicsMode.ScalarY);
    auto pt = ToImagePt(X,Y);
    barStatus->Panels->Items[2]->Text = "P=" + IntToStr(static_cast<int>(pt.X  )) + ", " + IntToStr(static_cast<int>(pt.Y  )) +
                                       ",C=" + IntToStr(static_cast<int>(pt.X/w)) + ", " + IntToStr(static_cast<int>(pt.Y / h));
    if (btnAnimateStop->Down) {
        if (btnModePaint->Down) {
            // pixel paint mode
            if (m_CanvasToolMap.count(m_CanvasTool) == 1) {
                m_CanvasToolMap[m_CanvasTool]->Move(m_Frames[m_SelectedFrame]->Canvas(), pt, Shift);
                RefreshView();
            }
        } else {
            // block type paint
            palBlocks->BlockType = m_BlockTypeTool.Move(pt, Shift);
            RefreshView();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::imgEditorMouseUp(TObject* /*Sender*/, TMouseButton, TShiftState, int X, int Y)
{
    if (btnAnimateStop->Down) {
        SetCaptureControl(nullptr);
        if (btnModePaint->Down) {
            // pixel paint mode
            if (m_CanvasToolMap.count(m_CanvasTool) == 1) {
                auto redo = m_CanvasToolMap[m_CanvasTool]->End(m_Frames[m_SelectedFrame]->Canvas(), ToImagePt(X,Y));
                m_ImageDocument->Frame[m_SelectedFrame] = m_Frames[m_SelectedFrame]->Canvas().Get();
                RefreshView();
                Bus::Publish<DocumentChange<String>>(DocumentChange<String>("document.changed", m_ImageDocument));
            }
        } else {
            // block type paint
            m_BlockTypeTool.End();
            RefreshView();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actModePaintExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        actPencil->Enabled = true;
        actLine->Enabled = true;
        actShape->Enabled = true;
        palAttribute->Visible = m_GraphicsMode.TypeOfBuffer == Visuals::btAttribute && m_GraphicsMode.LogicalColors == 16;
        palMonoAttribute->Visible = m_GraphicsMode.TypeOfBuffer == Visuals::btAttribute && m_GraphicsMode.LogicalColors == 2;
        palBitmap->Visible = m_GraphicsMode.TypeOfBuffer == Visuals::btBitmap;
        palULAPlus->Visible = m_GraphicsMode.TypeOfBuffer == Visuals::btULAplus;
        palBlocks->Visible = false;
        actGridPixel->Enabled = true;
        actGridCharacter->Enabled = true;
        actGridPixel->Checked = m_GridPixel;
        actGridCharacter->Checked = m_GridBlock;
        actMonoOff->Enabled = true;
        actMonoOff->Checked = true;
        actMonoOffExecute(nullptr);
        btnModePaint->Down = true;
        RefreshView(true);
        barStatus->Panels->Items[0]->Text = m_LastModeString;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorImage::actModeBlockExecute(TObject* /*Sender*/)
{
    if (IsActive()) {
        m_LastModeString = barStatus->Panels->Items[3]->Text;
        barStatus->Panels->Items[0]->Text = "Block Type Mode - Set";
        actPencil->Enabled = false;
        actLine->Enabled = false;
        actShape->Enabled = false;
        palAttribute->Visible = false;
        palMonoAttribute->Visible = false;
        palBitmap->Visible = false;
        palULAPlus->Visible = false;
        palBlocks->Visible = true;
        m_GridPixel = actGridPixel->Checked;
        m_GridBlock = actGridCharacter->Checked;
        actGridPixel->Checked = false;
        actGridCharacter->Checked = true;
        actGridPixel->Enabled = false;
        actGridCharacter->Enabled = false;
        actMonoOn->Checked = true;
        actMonoOff->Enabled = false;
        actMonoOnExecute(nullptr);
        btnModeBlock->Down = true;
        m_BlockTypeTool.Begin(m_Frames[m_SelectedFrame]->Canvas());
        RefreshView(true);
    }
}
//---------------------------------------------------------------------------



