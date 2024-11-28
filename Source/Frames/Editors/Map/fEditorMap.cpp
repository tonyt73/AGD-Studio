//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fEditorMap.h"
#include "../EditorManager.h"
#include "Messaging/Messaging.h"
#include "Messaging/Event.h"
#include "Project/Documents/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "fAssetSelection"
#pragma link "LMDButtonPanel"
#pragma link "LMDControl"
#pragma link "LMDCustomBevelPanel"
#pragma link "LMDCustomControl"
#pragma link "LMDCustomPanel"
#pragma link "LMDCustomPanelFill"
#pragma link "LMDCustomParentPanel"
#pragma link "LMDCustomToolBar"
#pragma link "LMDToolBar"
#pragma link "fAssetSelection"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
const float g_Scales[] = { 0.33f, 0.5f, 1.0f, 2.0f, 3.0f, 4.0f, 6.0f, 8.0f, 16.f };
//---------------------------------------------------------------------------
__fastcall TfrmEditorMap::TfrmEditorMap(TComponent* Owner)
: TfrmEditor(Owner)
, m_ActivePanel(nullptr)
, m_LastSelectedId(-1)
, m_Scale(2)
{
    m_KeysHelp =
        "Select Tool (1)\r\n"
        "Mouse over            : Highlight an item\r\n"
        "                        Can be moved, duplicated or deleted\r\n"
        "Ctrl + Left MB + Move : Select group of items\r\n"
        "                        Can select multiple group while Ctrl is held down\r\n"
        "Left MB click         : Clear selection\r\n\r\n"
        "Ctrl+D                : Duplicate the selected images\r\n\r\n"
        "Paint Tools (Pencil: 2, Line: 3, Rectangle: 4)\r\n"
        "Left MB click         : Add an image\r\n"
        "Left MB and drag      : Add multiple images defined by tool\r\n"
        "Middle MB click       : Removes any tile under the cursor\r\n"
        ", (<)                 : Change to previous image of active type\r\n"
        ". (>)                 : Change to next image of active type\r\n"
        "Line Tool\r\n"
        "Ctrl + Left MB        : Snap Line vertically or horizontally\r\n"
        "Rect Tool\r\n"
        "Ctrl + Left MB        : Snap Rectangle to Square\r\n\r\n"
        "General\r\n"
        "Shift + Left MB       : Pan the window by moving the mouse\r\n"
        "Ctrl + Del            : Delete selection\r\n"
        "Ctrl + G              : Toggle room grid\r\n"
        "Ctrl + Shift + G      : Toggle tile grid\r\n"
        "Ctrl + T              : Toggle sprite types\r\n"
        "Alt + E               : Toggle screen edit mode (multiple/single)\r\n"
        "Alt + R               : Toggle start room edit mode\r\n\r\n"
        "Sprite Types\r\n"
        "0                     : Set selected sprite(s) as Player sprite\r\n"
        "Shift + (1 - 8)       : Set selected sprite(s) as Sprite Type {no.}\r\n\r\n"
        "Change Start Room     : o Use Single Room Edit Mode\r\n"
        "                        o Select the room, using left click\r\n"
        "                        o Right click the select room to make it the Start room\r\n";

    m_Registrar.Subscribe<Event>(OnEvent);
    m_Registrar.Subscribe<RoomSelected>(OnRoomSelected);
    m_Registrar.Subscribe<StartRoomChanged>(OnStartRoomChanged);
    m_Registrar.Subscribe<DocumentChange<String>>(OnDocumentChanged);
}
//---------------------------------------------------------------------------
__fastcall TfrmEditorMap::~TfrmEditorMap()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::Initialise()
{
    m_ActionMap["zoom.in"] = actZoomIn;
    m_ActionMap["zoom.out"] = actZoomOut;
    m_ActionMap["zoom.reset"] = actZoomReset;
    m_ActionMap["edit.undo"] = actUndo;
    m_ActionMap["edit.redo"] = actRedo;
    m_ActionMap["edit.copy"] = actCopy;
    m_ActionMap["edit.cut"] = actCut;
    m_ActionMap["edit.paste"] = actPaste;

    // create the tile editors
    // TODO: change the size to ???
    m_Workspace = std::make_unique<TileEditor>(imgWorkspace, m_ImageMap, TSize(Project::g_MaxMapRoomsAcross, Project::g_MaxMapRoomsDown), true, true, 144, false);
    m_Workspace->Mode = TileEditor::temSelect;
    m_Workspace->StartRoom = TPoint(m_Document->StartRoomX, m_Document->StartRoomY);
    m_Workspace->LockIcon = imgLock;
    m_Workspace->RetrieveRoomIndex = OnRetrieveRoomIndex;

    m_ScratchPad = std::make_unique<TileEditor>(imgScratchPad, m_ImageMap, TSize(8,8), true, false, 8, false);
    m_ScratchPad->Mode = TileEditor::temSelect;
    m_ScratchPad->GridTile = true;
    m_ScratchPad->GridRoom = false;
    m_ScratchPad->Mode = TileEditor::temSelect;

    m_RoomSelector = std::make_unique<TileEditor>(imgRoomSelector, m_ImageMap, TSize(Project::g_MaxMapRoomsAcross, Project::g_MaxMapRoomsDown), false, true, 8, true);
    m_RoomSelector->Mode = TileEditor::temSelect;
    m_RoomSelector->GridRoom = true;
    m_RoomSelector->ShowStartRoom = true;
    m_RoomSelector->ShowSelectedRoom = true;
    m_RoomSelector->StartRoom = TPoint(m_Document->StartRoomX, m_Document->StartRoomY);
    m_RoomSelector->Scale = 0.5f;
    m_RoomSelector->RetrieveRoomIndex = OnRetrieveRoomIndex;
    // and set their tile sets
    m_Workspace->SetEntities(m_Document->Get(Project::meMap));
    m_ScratchPad->SetEntities(m_Document->Get(Project::meScratchPad));
    m_RoomSelector->SetEntities(m_Document->Get(Project::meMap));
    // On MapEntity Select handler
    m_Workspace->OnEntitySelected = OnWorkspaceEntitySelected;

    // fix up the image flicker
    m_EraseHandlers.push_back(std::make_unique<TWinControlHandler>(panWorkspaceView));
    m_EraseHandlers.push_back(std::make_unique<TWinControlHandler>(panScratchPadView));

    // refresh the views
    RefreshAssets();
    Refresh();

    // handle asset onclick
    assetsTiles->OnImageSelection = OnEntityClick;
    assetsSprites->OnImageSelection = OnEntityClick;
    assetsObjects->OnImageSelection = OnEntityClick;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actSelectExecute(TObject *Sender)
{
    if (IsActive())
    {
        btnSelect->Down = true;
        m_Workspace->Mode = TileEditor::temSelect;
        m_Workspace->ToolEntity = m_LastSelectedId;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actPencilExecute(TObject *Sender)
{
    if (IsActive())
    {
        btnPencil->Down = true;
        m_Workspace->UnselectAll();
        m_Workspace->Mode = TileEditor::temPencil;
        m_Workspace->ToolEntity = m_LastSelectedId;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actLineExecute(TObject *Sender)
{
    if (IsActive())
    {
        btnLine->Down = true;
        m_Workspace->UnselectAll();
        m_Workspace->Mode = TileEditor::temLine;
        m_Workspace->ToolEntity = m_LastSelectedId;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actRectExecute(TObject *Sender)
{
    if (IsActive())
    {
        btnRect->Down = true;
        m_Workspace->UnselectAll();
        m_Workspace->Mode = TileEditor::temRect;
        m_Workspace->ToolEntity = m_LastSelectedId;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actZoomInExecute(TObject *Sender)
{
    if (IsActive() && m_Scale < 8)
    {
        m_Workspace->Scale = g_Scales[++m_Scale];
        m_Workspace->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actZoomOutExecute(TObject *Sender)
{
    if (IsActive() && m_Scale > 0)
    {
        m_Workspace->Scale = g_Scales[--m_Scale];
        m_Workspace->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actZoomResetExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_Scale = 2;
        m_Workspace->Scale = g_Scales[m_Scale];
        m_Workspace->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actUndoExecute(TObject *Sender)
{
    if (IsActive())
    {

    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actRedoExecute(TObject *Sender)
{
    if (IsActive())
    {

    }
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
    m_Document->Set(actEditModeSingleScreen->Checked ? Project::meRoom : Project::meMap, m_Workspace->GetEntities());
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgRoomSelectorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbRight && actEditModeSingleScreen->Checked) {
        // select screen as start screen
        Bus::Publish<SetStartRoom>(SetStartRoom(TPoint(m_RoomSelector->SelectedRoom.cx, m_RoomSelector->SelectedRoom.cy)));
    }
    m_RoomSelector->OnMouseDown(Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgRoomSelectorMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    m_RoomSelector->OnMouseMove(Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgRoomSelectorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_RoomSelector->OnMouseUp(Button, Shift, X, Y);
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
    m_Document->Set(Project::meScratchPad, m_ScratchPad->GetEntities());
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::RefreshAssets()
{
    assetsTiles->Visible = false;
    assetsSprites->Visible = false;
    assetsObjects->Visible = false;
    assetsTiles->Clear();
    assetsSprites->Clear();
    assetsObjects->Clear();
    m_ImageMap.clear();
    Project::DocumentList images;
    theDocumentManager.GetAllOfType("Image", images);
    const auto& gm = *(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode());
    bool firstTile = true;
    for (auto image : images)
    {
        auto img = dynamic_cast<Project::ImageDocument*>(image);
        m_ImageMap[image->Id] = std::make_unique<Visuals::Image>(img, gm);
        if (image->SubType == "Tile")
        {
            assetsTiles->Add(img, true);
            if (firstTile)
            {
                m_Workspace->Tile0Id = img->Id;
                m_RoomSelector->Tile0Id = img->Id;
                firstTile = false;
            }
        }
        else if (image->SubType == "Sprite")
        {
            assetsSprites->Add(img);
        }
        else if (image->SubType == "Object")
        {
            assetsObjects->Add(img);
        }
    }
    assetsTiles->Visible = true;
    assetsSprites->Visible = true;
    assetsObjects->Visible = true;
    assetsTiles->sbxListResize(nullptr);
    assetsSprites->sbxListResize(nullptr);
    assetsObjects->sbxListResize(nullptr);
    m_Workspace->UpdateMap();
    m_RoomSelector->UpdateMap();
    Bus::Publish<Event>(Event("update.properties"));
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnEvent(const Event& event)
{
    TfrmEditor::OnEvent(event);
    if (IsActive() && m_ActionMap.count(event.Id) == 1)
    {
        m_ActionMap[event.Id]->Execute();
    }
    else if (event.Id == "palette.remapped")
    {
        m_Workspace->Refresh();
        m_ScratchPad->Refresh();
        if (imgRoomSelector->Visible)
        {
            m_RoomSelector->Refresh();
        }
    }
    else if (event.Id == "editor.show")
    {
        dpTileMap->Manager = static_cast<TLMDDockPanel*>(Document->DockPanel)->Site->Manager;
    }
    else if (event.Id == "map.updated")
    {
        m_RoomSelector->SetEntities(m_Document->Get(Project::meMap));
        m_RoomSelector->UpdateMap();
    }
    else if (event.Id == "document.added")
    {
        RefreshAssets();
    }
    assetsTiles->sbxListResize(nullptr);
    assetsSprites->sbxListResize(nullptr);
    assetsObjects->sbxListResize(nullptr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnRoomSelected(const RoomSelected& event)
{
    if (event.Id == "room.selected")
    {
        m_Workspace->SetEntities(m_Document->Get(Project::meRoom, event.Room));
        m_Workspace->UpdateMap();
        Bus::Publish<Event>(Event("update.properties"));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnStartRoomChanged(const StartRoomChanged& event)
{
    if (event.Id == "start.room.changed")
    {
        m_Workspace->StartRoom = event.Room;
        m_RoomSelector->StartRoom = event.Room;
        ::Messaging::Bus::Publish<Event>(Event("update.properties"));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnDocumentChanged(const DocumentChange<String>& message)
{
    if (message.Id == "document.removing")
    {
        m_Workspace->SetEntities(m_Document->Get(actEditModeSingleScreen->Checked ? Project::meRoom : Project::meMap, m_RoomSelector->SelectedRoom));
        m_ScratchPad->SetEntities(m_Document->Get(Project::meScratchPad));
        m_RoomSelector->SetEntities(m_Document->Get(Project::meMap));
        m_Workspace->UpdateMap();
        m_ScratchPad->UpdateMap();
        m_RoomSelector->UpdateMap();
    }
    else if (message.Id == "document.removed")
    {
        RefreshAssets();
    }
    else if ("document.changed")
    {
        const auto& gm = *(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode());
        auto image = dynamic_cast<const Project::ImageDocument*>(message.Document);
        m_ImageMap[message.Document->Id] = std::make_unique<Visuals::Image>(image, gm);
        if (message.Document->Id == m_Workspace->Tile0Id)
        {
            m_Workspace->Tile0Id = image->Id;
            m_RoomSelector->Tile0Id = image->Id;
        }
        m_Workspace->UpdateMap();
        m_ScratchPad->UpdateMap();
        m_RoomSelector->UpdateMap();
        assetsTiles->UpdateDocument(image);
        assetsSprites->UpdateDocument(image);
        assetsObjects->UpdateDocument(image);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::panWorkspaceViewResize(TObject *Sender)
{
    m_Workspace->Refresh();
    m_RoomSelector->Refresh();
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
    if (dpAssets != nullptr && dpAssets->Width < minWidth)
    {
        auto dz = dpAssets->Zone;
        while (dz != nullptr && dz->Parent)
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
void __fastcall TfrmEditorMap::imgWorkspaceMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
    theEditorManager.SetActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgWorkspaceMouseEnter(TObject *Sender)
{
    theEditorManager.SetActive(this);
    auto wc = dynamic_cast<TControl*>(Sender);
    if (wc && wc->Parent && wc->Parent->Parent)
    {
        m_ActivePanel = nullptr;
        while (!m_ActivePanel && wc->Parent)
        {
            auto dp = dynamic_cast<TLMDDockPanel*>(wc->Parent);
            auto cn = wc->Parent->ClassName();
            if (dp)
            {
                m_ActivePanel = dp;
            }
            wc = wc->Parent;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actCopyToScratchPadExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_ScratchPad->Add(m_Workspace->GetSelection(true));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actMoveToScratchPadExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_ScratchPad->Add(m_Workspace->GetSelection(true));
        m_Workspace->DeleteSelection();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actCopyToWorkspaceExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_Workspace->Add(m_ScratchPad->GetSelection());
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actDuplicateExecute(TObject *Sender)
{
    if (IsActive())
    {
        if (dpWorkspace == m_ActivePanel)
        {
            auto list = m_Workspace->GetSelection();
            m_Workspace->UnselectAll();
            m_Workspace->Add(list);
        }
        else if (dpScratchPad == m_ActivePanel)
        {
            auto list = m_ScratchPad->GetSelection();
            m_ScratchPad->UnselectAll();
            m_ScratchPad->Add(list);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actDeleteExecute(TObject *Sender)
{
    if (IsActive())
    {
        if (dpWorkspace == m_ActivePanel)
        {
            m_Workspace->DeleteSelection();
            m_Document->Set(actEditModeSingleScreen->Checked ? Project::meRoom : Project::meMap, m_Workspace->GetEntities());
        }
        else if (dpScratchPad == m_ActivePanel)
        {
            m_ScratchPad->DeleteSelection();
            m_Document->Set(Project::meScratchPad, m_ScratchPad->GetEntities());
        }
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
void __fastcall TfrmEditorMap::pgcAssetsChange(TObject *Sender)
{
    auto state = pgcAssets->ActivePage == tabTiles;
    if (!state && (btnLine->Down || btnRect->Down))
    {
        btnPencil->Down = true;
        actPencilExecute(Sender);
    }
    actLine->Enabled = state;
    actRect->Enabled = state;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnEntityClick(Project::ImageDocument* document)
{
    m_LastSelectedId = document->Id;
    m_Workspace->ToolEntity = document->Id;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnWorkspaceEntitySelected(const Project::MapEntity& entity)
{
    switch (entity.Image->ImageType)
    {
        case Visuals::itObject:
            pgcAssets->ActivePage = tabObjects;
            assetsObjects->Select(entity.Image);
            break;
        case Visuals::itSprite:
            pgcAssets->ActivePage = tabSprites;
            assetsSprites->Select(entity.Image);
            break;
        case Visuals::itTile:
            pgcAssets->ActivePage = tabTiles;
            assetsTiles->Select(entity.Image);
            break;
        default:
            // ignore the other enum values
            break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::btnWSGridRoomClick(TObject *Sender)
{
    m_Workspace->GridRoom = btnWSGridRoom->Down;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::btnWSGridTileClick(TObject *Sender)
{
    m_Workspace->GridTile = btnWSGridTile->Down;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::btnSPGridTileClick(TObject *Sender)
{
    //btnSPGridTile->Down = !btnSPGridTile->Down;
    m_ScratchPad->GridTile = btnSPGridTile->Down;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actGridTileExecute(TObject *Sender)
{
    if (IsActive())
    {
        if (dpWorkspace == m_ActivePanel)
        {
            btnWSGridTile->Down = !btnWSGridTile->Down;
            btnWSGridTileClick(Sender);
        }
        else
        {
            btnSPGridTileClick(Sender);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actGridRoomExecute(TObject *Sender)
{
    if (IsActive())
    {
        if (dpWorkspace == m_ActivePanel)
        {
            btnWSGridRoom->Down = !btnWSGridRoom->Down;
            btnWSGridRoomClick(Sender);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actEditModeFullMapExecute(TObject *Sender)
{
    if (IsActive())
    {
        if (actEditModeFullMap->Checked)
        {
            actEditModeFullMap->Checked = false;
            actEditModeSingleScreen->Checked = true;
        }
        else
        {
            actEditModeSingleScreen->Checked = false;
            actEditModeFullMap->Checked = true;
        }
        //actStartRoomTool->Enabled = !actEditModeSingleScreen->Checked;
        dpRoomSelector->PanelVisible = actEditModeSingleScreen->Checked;
        dpRoomSelector->Zone->Height = std::max(dpRoomSelector->Zone->Height, 256);
        m_Workspace->Rooms = actEditModeSingleScreen->Checked ? TSize(1, 1) : TSize(Project::g_MaxMapRoomsAcross, Project::g_MaxMapRoomsDown);
        m_Workspace->SetEntities(m_Document->Get(actEditModeSingleScreen->Checked ? Project::meRoom : Project::meMap, m_RoomSelector->SelectedRoom));
        m_Workspace->ShowStartRoom = !actEditModeSingleScreen->Checked && actToggleStartRoom->Checked;
        m_Workspace->UpdateMap();
        m_RoomSelector->UpdateMap();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actToggleStartRoomExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_Workspace->ShowStartRoom = actToggleStartRoom->Checked;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actEntityNextExecute(TObject *Sender)
{
    if (IsActive())
    {
        if (pgcAssets->ActivePage == tabTiles)
        {
            assetsTiles->Next();
        }
        else if (pgcAssets->ActivePage == tabSprites)
        {
            assetsSprites->Next();
        }
        else
        {
            assetsObjects->Next();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actEntityPrevExecute(TObject *Sender)
{
    if (IsActive())
    {
        if (pgcAssets->ActivePage == tabTiles)
        {
            assetsTiles->Prev();
        }
        else if (pgcAssets->ActivePage == tabSprites)
        {
            assetsSprites->Prev();
        }
        else
        {
            assetsObjects->Prev();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actEntityToggleLocksExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_Workspace->ToggleEntityLocks();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::sbxWorkspaceMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    if (WheelDelta < 0)
    {
        actZoomInExecute(nullptr);
    }
    else
    {
        actZoomOutExecute(nullptr);
    }
    Handled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actCopyExecute(TObject *Sender)
{
    if (IsActive())
    {
        if (dpWorkspace == m_ActivePanel)
        {
            m_Workspace->Copy();
        }
        else if (dpScratchPad == m_ActivePanel)
        {
            m_ScratchPad->Copy();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actCutExecute(TObject *Sender)
{
    if (IsActive())
    {
        if (dpWorkspace == m_ActivePanel)
        {
            m_Workspace->Cut();
        }
        else if (dpScratchPad == m_ActivePanel)
        {
            m_ScratchPad->Cut();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actPasteExecute(TObject *Sender)
{
    if (IsActive())
    {
        if (dpWorkspace == m_ActivePanel)
        {
            m_Workspace->Paste();
        }
        else if (dpScratchPad == m_ActivePanel)
        {
            m_ScratchPad->Paste();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actToggleRoomNumbersExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_Workspace->ShowRoomNumbers = actToggleRoomNumbers->Checked;
        m_RoomSelector->ShowRoomNumbers = actToggleRoomNumbers->Checked;
    }
}
//---------------------------------------------------------------------------
int __fastcall TfrmEditorMap::OnRetrieveRoomIndex(const TPoint& pt, bool newIndex)
{
    return m_Document->GetRoomIndex(pt, newIndex);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actToggleShowLocksExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_Workspace->LockIcon = actToggleShowLocks->Checked ? imgLock : nullptr;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actToggleTileTypesExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_Workspace->ShowTileTypes = actToggleTileTypes->Checked;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actSpriteType0Execute(TObject *Sender)
{
    if (IsActive())
    {
        auto action = dynamic_cast<TAction*>(Sender);
        m_Workspace->SetSpriteType(action->Tag);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actShowSpriteTypesExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_Workspace->ShowSpriteTypes = actShowSpriteTypes->Checked;
    }
}
//---------------------------------------------------------------------------

