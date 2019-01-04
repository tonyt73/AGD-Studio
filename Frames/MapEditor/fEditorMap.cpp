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
    m_Registrar.Subscribe<Event>(OnEvent);
    m_Registrar.Subscribe<OnMapResized>(OnMapResize);
    m_Registrar.Subscribe<RoomSelected>(OnRoomSelected);
    m_Registrar.Subscribe<StartRoomSet>(OnStartRoomSet);
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

    // create the tile editors
    // TODO: change the size to ???
    m_Workspace = std::make_unique<TileEditor>(imgWorkspace, m_ImageMap, TSize(16,16), true, true, 144, false);
    m_Workspace->Mode = TileEditor::temSelect;
    m_Workspace->StartRoom = TPoint(m_Document->StartLocationX, m_Document->StartLocationY);

    m_ScratchPad = std::make_unique<TileEditor>(imgScratchPad, m_ImageMap, TSize(8,8), true, false, 8, false);
    m_ScratchPad->Mode = TileEditor::temSelect;
    m_ScratchPad->GridTile = true;
    m_ScratchPad->GridRoom = false;
    m_ScratchPad->Mode = TileEditor::temSelect;

    m_RoomSelector = std::make_unique<TileEditor>(imgRoomSelector, m_ImageMap, TSize(16,16), false, true, 8, true);
    m_RoomSelector->Mode = TileEditor::temSelect;
    m_RoomSelector->GridRoom = true;
    m_RoomSelector->ShowStartRoom = true;
    m_RoomSelector->ShowSelectedRoom = true;
    m_RoomSelector->StartRoom = TPoint(m_Document->StartLocationX, m_Document->StartLocationY);
    m_RoomSelector->Scale = 0.5f;
    // and set their tile sets
    m_Workspace->SetEntities(m_Document->Get(meMap));
    m_ScratchPad->SetEntities(m_Document->Get(meScratchPad));
    m_RoomSelector->SetEntities(m_Document->Get(meMap));
    // On Entity Select handler
    m_Workspace->OnEntitySelected = OnWorkspaceEntitySelected;

    // fix up the image flicker
    m_EraseHandlers.push_back(std::make_unique<TWinControlHandler>(panWorkspaceView));
    m_EraseHandlers.push_back(std::make_unique<TWinControlHandler>(panScratchPadView));

    // refresh the views
    RefreshAssets();
    Refresh();
    ShowKeysHelp();

    // handle asset onclick
    assetsTiles->OnImageSelection = OnEntityClick;
    assetsSprites->OnImageSelection = OnEntityClick;
    assetsObjects->OnImageSelection = OnEntityClick;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actSelectExecute(TObject *Sender)
{
    btnSelect->Down = true;
    m_Workspace->Mode = TileEditor::temSelect;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actPencilExecute(TObject *Sender)
{
    btnPencil->Down = true;
    m_Workspace->UnselectAll();
    m_Workspace->Mode = TileEditor::temPencil;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actLineExecute(TObject *Sender)
{
    btnLine->Down = true;
    m_Workspace->UnselectAll();
    m_Workspace->Mode = TileEditor::temLine;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actShapeExecute(TObject *Sender)
{
    btnShape->Down = true;
    m_Workspace->UnselectAll();
    m_Workspace->Mode = TileEditor::temShape;
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
    m_Document->Set(actToggleSingleRoomMode->Checked ? meRoom : meMap, m_Workspace->GetEntities());
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::imgRoomSelectorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
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
    m_Document->Set(meScratchPad, m_ScratchPad->GetEntities());
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::RefreshAssets()
{
    assetsTiles->Clear();
    assetsSprites->Clear();
    assetsObjects->Clear();
    m_ImageMap.clear();
    DocumentList images;
    theDocumentManager.GetAllOfType("Image", images);
    const auto& gm = *(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode());
    bool firstTile = true;
    for (auto image : images)
    {
        auto img = dynamic_cast<ImageDocument*>(image);
        m_ImageMap[image->Id] = std::make_unique<Agdx::Image>(img, gm);
        if (image->SubType == "Tile")
        {
            assetsTiles->Add(img, !firstTile);
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
    assetsTiles->sbxListResize(nullptr);
    assetsSprites->sbxListResize(nullptr);
    assetsObjects->sbxListResize(nullptr);
    m_Workspace->UpdateMap();
    m_RoomSelector->UpdateMap();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditorMap::IsActive() const
{
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
        m_RoomSelector->SetEntities(m_Document->Get(meMap));
        m_RoomSelector->UpdateMap();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnRoomSelected(const RoomSelected& event)
{
    if (event.Id == "room.selected")
    {
        m_Workspace->SetEntities(m_Document->Get(meRoom, event.Room));
        m_Workspace->UpdateMap();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnStartRoomSet(const StartRoomSet& event)
{
    if (event.Id == "start.room.set")
    {
        m_Workspace->StartRoom = event.Room;
        m_RoomSelector->StartRoom = event.Room;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnDocumentChanged(const DocumentChange<String>& message)
{
    if (message.Id == "document.removing")
    {
        m_Workspace->SetEntities(m_Document->Get(actToggleSingleRoomMode->Checked ? meRoom : meMap, m_RoomSelector->SelectedRoom));
        m_ScratchPad->SetEntities(m_Document->Get(meScratchPad));
        m_RoomSelector->SetEntities(m_Document->Get(meMap));
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
        auto image = dynamic_cast<const ImageDocument*>(message.document);
        m_ImageMap[message.document->Id] = std::make_unique<Agdx::Image>(image, gm);
        if (message.document->Id == m_Workspace->Tile0Id)
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
void __fastcall TfrmEditorMap::OnMapResize(const OnMapResized& message)
{
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
        "Select Tool (1)\r\n"
        "Mouse over            : Highlight an item\r\n"
        "                        Can be moved, duplicated or deleted\r\n"
        "Ctrl + Left MB + Move : Select group of items\r\n"
        "Ctrl + Left MB Click  : Clear selection\r\n\r\n"
        "Paint Tools (Pencil: 2, Line: 3, Rectangle: 4)\r\n"
        "Left MB click         : Add an image\r\n"
        "Left MB and drag      : Add multiple images defined by tool\r\n\r\n"
        "Middle MB click       : Removes any tile under the cursor\r\n"
        "Middle MB and drag    : Remove multiple tiles of the selected type\r\n\r\n"
        "General\r\n"
        "Shift + Left MB       : Pan the window by moving the mouse\r\n"
        "Ctrl + Del            : Delete selection\r\n"
        "Ctrl + G              : Toggle room grid\r\n"
        "Ctrl + Shift + G      : Toggle tile grid\r\n"
        "Alt + E               : Toggle screen edit mode (multiple/single)\r\n"
        "Alt + R               : Toggle start room edit mode\r\n";
    ::Messaging::Bus::Publish<MessageEvent>(HelpKeysMessageEvent(help));
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
    m_ScratchPad->Add(m_Workspace->GetSelection(true));
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actMoveToScratchPadExecute(TObject *Sender)
{
    m_ScratchPad->Add(m_Workspace->GetSelection(true));
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
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actDeleteExecute(TObject *Sender)
{
    if (dpWorkspace == m_ActivePanel)
    {
        m_Workspace->DeleteSelection();
        m_Document->Set(actToggleSingleRoomMode->Checked ? meRoom : meMap, m_Workspace->GetEntities());
        //TODO:m_Workspace->SetEntities(m_Document->Get(actToggleSingleRoomMode->Checked ? meRoom : meMap, m_RoomSelector->SelectedRoom));
    }
    else if (dpScratchPad == m_ActivePanel)
    {
        m_ScratchPad->DeleteSelection();
        m_Document->Set(meScratchPad, m_ScratchPad->GetEntities());
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
    auto state = true;//pgcAssets->ActivePage == tabTiles;
    if (!state && (btnLine->Down || btnShape->Down))
    {
        btnPencil->Down = true;
        actPencilExecute(Sender);
    }
    actLine->Enabled = state;
    actShape->Enabled = state;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnEntityClick(ImageDocument* document)
{
    m_Workspace->SelectedEntity = document->Id;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::OnWorkspaceEntitySelected(const Entity& entity)
{
    switch (entity.Image->ImageType)
    {
        case itObject:
            pgcAssets->ActivePage = tabObjects;
            assetsObjects->Select(entity.Image);
            break;
        case itSprite:
            pgcAssets->ActivePage = tabSprites;
            assetsSprites->Select(entity.Image);
            break;
        case itTile:
            pgcAssets->ActivePage = tabTiles;
            assetsTiles->Select(entity.Image);
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
    btnSPGridTile->Down = !btnSPGridTile->Down;
    m_ScratchPad->GridTile = btnSPGridTile->Down;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actGridTileExecute(TObject *Sender)
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
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actGridRoomExecute(TObject *Sender)
{
    if (dpWorkspace == m_ActivePanel)
    {
        btnWSGridRoom->Down = !btnWSGridRoom->Down;
        btnWSGridRoomClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actToggleSingleRoomModeExecute(TObject *Sender)
{
    actStartRoomTool->Enabled = !actToggleSingleRoomMode->Checked;
    dpRoomSelector->PanelVisible = actToggleSingleRoomMode->Checked;
    dpRoomSelector->Zone->Height = std::max(dpRoomSelector->Zone->Height, 256);
    m_Workspace->Rooms = actToggleSingleRoomMode->Checked ? TSize(1, 1) : TSize(16, 16);
    m_Workspace->SetEntities(m_Document->Get(actToggleSingleRoomMode->Checked ? meRoom : meMap, m_RoomSelector->SelectedRoom));
    m_Workspace->ShowStartRoom = !actToggleSingleRoomMode->Checked && actStartRoomTool->Checked;
    m_Workspace->UpdateMap();
    m_RoomSelector->UpdateMap();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actStartRoomToolExecute(TObject *Sender)
{
    m_Workspace->ShowStartRoom = actStartRoomTool->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actEntityNextExecute(TObject *Sender)
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
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actEntityPrevExecute(TObject *Sender)
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
//---------------------------------------------------------------------------

