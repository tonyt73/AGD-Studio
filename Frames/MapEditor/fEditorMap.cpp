//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fEditorMap.h"
#include "Project/DocumentManager.h"
#include "Project/EditorManager.h"
#include "Messaging/Messaging.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AssetSelection"
#pragma link "LMDButtonPanel"
#pragma link "LMDControl"
#pragma link "LMDCustomBevelPanel"
#pragma link "LMDCustomControl"
#pragma link "LMDCustomPanel"
#pragma link "LMDCustomPanelFill"
#pragma link "LMDCustomParentPanel"
#pragma link "LMDCustomToolBar"
#pragma link "LMDToolBar"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorMap::TfrmEditorMap(TComponent* Owner)
: TFrame(Owner)
, m_ActivePanel(nullptr)
{
    ::Messaging::Bus::Subscribe<Event>(OnEvent);
    ::Messaging::Bus::Subscribe<OnMapResized>(OnMapResize);
}
//---------------------------------------------------------------------------
__fastcall TfrmEditorMap::~TfrmEditorMap()
{
    ::Messaging::Bus::Unsubscribe<OnMapResized>(OnMapResize);
    ::Messaging::Bus::Unsubscribe<Event>(OnEvent);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::Initialise()
{
    m_ActionMap["zoom.in"] = actZoomIn;
    m_ActionMap["zoom.out"] = actZoomOut;
    m_ActionMap["zoom.reset"] = actZoomReset;
    m_ActionMap["edit.undo"] = actUndo;
    m_ActionMap["edit.redo"] = actRedo;

    // create the tile editors
    // TODO: change the size to ???
    m_Workspace = std::make_unique<TileEditor>(imgWorkspace, TSize(512,512), true, true, 128);
    m_ScratchPad = std::make_unique<TileEditor>(imgScratchPad, TSize(128,128), true, false, 0);
    m_Workspace->Mode = TileEditor::temSelect;
    m_ScratchPad->Mode = TileEditor::temSelect;
    // and set their tile sets
    m_Workspace->SetEntities(m_Document->Get(meWorkspace));
    m_ScratchPad->SetEntities(m_Document->Get(meScratchPad));

    // fix up the image flicker
    m_EraseHandlers.push_back(std::make_unique<TWinControlHandler>(panWorkspaceView));
    m_EraseHandlers.push_back(std::make_unique<TWinControlHandler>(panScratchPadView));

    // refresh the views
    RefreshAssets();
    Refresh();
    ShowKeysHelp();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actSelectExecute(TObject *Sender)
{
    m_Workspace->Mode = TileEditor::temSelect;
    m_ScratchPad->Mode = TileEditor::temSelect;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actPencilExecute(TObject *Sender)
{
    m_Workspace->Mode = TileEditor::temPencil;
    m_ScratchPad->Mode = TileEditor::temPencil;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actLineExecute(TObject *Sender)
{
    m_Workspace->Mode = TileEditor::temLine;
    m_ScratchPad->Mode = TileEditor::temLine;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actShapeExecute(TObject *Sender)
{
    m_Workspace->Mode = TileEditor::temShape;
    m_ScratchPad->Mode = TileEditor::temShape;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actGridTileExecute(TObject *Sender)
{
    m_Workspace->GridTile = actGridTile->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actGridRoomExecute(TObject *Sender)
{
    m_Workspace->GridRoom = actGridRoom->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actZoomInExecute(TObject *Sender)
{
    if (m_Workspace->Scale < 4)
    {
        m_Workspace->Scale++;
        m_Workspace->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actZoomOutExecute(TObject *Sender)
{
    if (m_Workspace->Scale > 1)
    {
        m_Workspace->Scale--;
        m_Workspace->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actZoomResetExecute(TObject *Sender)
{
    m_Workspace->Scale = 1;
    m_Workspace->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actUndoExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actRedoExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgWorkspaceMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_Workspace->OnMouseDown(Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgWorkspaceMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    m_Workspace->OnMouseMove(Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgWorkspaceMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_Workspace->OnMouseUp(Button,Shift, X, Y);
    // copy the workspace to the map document
    m_Document->Set(meWorkspace, m_Workspace->GetEntities());
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgScratchPadMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_ScratchPad->OnMouseDown(Button,Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgScratchPadMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    m_ScratchPad->OnMouseMove(Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgScratchPadMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_ScratchPad->OnMouseUp(Button,Shift, X, Y);
    // copy the scratch pad to the map document
    m_Document->Set(meScratchPad, m_ScratchPad->GetEntities());
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::RefreshAssets()
{
    assetsTiles->Clear();
    assetsSprites->Clear();
    assetsObjects->Clear();
    DocumentList images;
    theDocumentManager.GetAllOfType("Image", images);
    bool firstTile = true;
    for (auto image : images)
    {
        if (image->SubType == "Tile")
        {
            auto img = dynamic_cast<ImageDocument*>(image);
            assetsTiles->Add(img);
            if (firstTile)
            {
                m_Workspace->Tile0Id = img->Id;
                firstTile = false;
            }
        }
        else if (image->SubType == "Sprite")
        {
            assetsSprites->Add(dynamic_cast<ImageDocument*>(image));
        }
        else if (image->SubType == "Object")
        {
            assetsObjects->Add(dynamic_cast<ImageDocument*>(image));
        }
    }
    assetsTiles->ScrollBox1Resize(nullptr);
    assetsSprites->ScrollBox1Resize(nullptr);
    assetsObjects->ScrollBox1Resize(nullptr);
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditorMap::IsActive() const
{
    //return static_cast<TLMDDockPanel*>(m_Document->DockPanel)->Active;
    return theEditorManager.IsActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnEvent(const Event& event)
{
    if (IsActive() && m_ActionMap.count(event.Id) == 1)
    {
        m_ActionMap[event.Id]->Execute();
        ShowKeysHelp();
    }
    else if (event.Id == "palette.remapped")
    {
        m_Workspace->Refresh();
        m_ScratchPad->Refresh();
    }
    else if (event.Id == "editor.show")
    {
        dpTileMap->Manager = static_cast<TLMDDockPanel*>(Document->DockPanel)->Site->Manager;
    }
    else if (event.Id == "image.modified" || event.Id == "document.added" || event.Id == "document.removed")
    {
        RefreshAssets();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnMapResize(const OnMapResized& message)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::panWorkspaceViewResize(TObject *Sender)
{
    m_Workspace->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::panScratchPadViewResize(TObject *Sender)
{
    const auto minWidth = 400;
    if (dpScratchPad->Width < minWidth)
    {
        auto dz = dpScratchPad->Zone;
        while (dz->Parent)
        {
            dz->Width = minWidth;
            dz = dz->Parent;
        }
    }
    m_ScratchPad->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::pgcAssetsResize(TObject *Sender)
{
    const auto minWidth = 400;
    if (dpAssets->Width < minWidth)
    {
        auto dz = dpAssets->Zone;
        while (dz->Parent)
        {
            dz->Width = minWidth;
            dz = dz->Parent;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::dpToolsCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::ShowKeysHelp()
{
    const String help =
        "Left Mouse Button         : Place current asset\r\n"
        "                            Tiles - Hold button and drag mouse to place multiple\r\n"
        "Right Mouse Button        : Remove tile\r\n"
        "                            Tiles - Hold button and drag mouse to remove multiple\r\n"
        "Shift + Left Mouse Button : Pan the window";
    ::Messaging::Bus::Publish<HelpKeysMessage>(HelpKeysMessage(help));
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgWorkspaceMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
    theEditorManager.SetActive(this);
    ShowKeysHelp();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgWorkspaceMouseEnter(TObject *Sender)
{
    theEditorManager.SetActive(this);
    auto wc = dynamic_cast<TControl*>(Sender);
    if (wc && wc->Parent && wc->Parent->Parent)
    {
        auto dp = dynamic_cast<TLMDDockPanel*>(wc->Parent->Parent);
        auto cn = wc->Parent->Parent->ClassName();
        if (dp)
        {
            m_ActivePanel = dp;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actCopyToScratchPadExecute(TObject *Sender)
{
    m_ScratchPad->Add(m_Workspace->GetSelection());
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actMoveToScratchPadExecute(TObject *Sender)
{
    m_ScratchPad->Add(m_Workspace->GetSelection());
    m_Workspace->DeleteSelection();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actCopyToWorkspaceExecute(TObject *Sender)
{
    m_Workspace->Add(m_ScratchPad->GetSelection());
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actDuplicateExecute(TObject *Sender)
{
    if (dpWorkspace == m_ActivePanel)
    {
        m_Workspace->Add(m_Workspace->GetSelection());
    }
    else if (dpScratchPad == m_ActivePanel)
    {
        m_ScratchPad->Add(m_ScratchPad->GetSelection());
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actDeleteExecute(TObject *Sender)
{
    if (dpWorkspace == m_ActivePanel)
    {
        m_Workspace->DeleteSelection();
    }
    else if (dpScratchPad == m_ActivePanel)
    {
        m_ScratchPad->DeleteSelection();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::mnuWSToggleToolbarClick(TObject *Sender)
{
    tbrWorkspace->Visible = mnuWSToggleToolbar->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::mnuSPToggleToolbarClick(TObject *Sender)
{
    tbrScratchPad->Visible = mnuSPToggleToolbar->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actSPToggleGridExecute(TObject *Sender)
{
    m_ScratchPad->GridTile = actSPToggleGrid->Checked;
}
//---------------------------------------------------------------------------

