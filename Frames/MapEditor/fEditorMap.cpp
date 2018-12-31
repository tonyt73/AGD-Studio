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
    ::Messaging::Bus::Subscribe<RoomSelected>(OnRoomSelected);
    ::Messaging::Bus::Subscribe<StartRoomSet>(OnStartRoomSet);
}
//---------------------------------------------------------------------------
__fastcall TfrmEditorMap::~TfrmEditorMap()
{
    ::Messaging::Bus::Unsubscribe<StartRoomSet>(OnStartRoomSet);
    ::Messaging::Bus::Unsubscribe<RoomSelected>(OnRoomSelected);
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
    m_Workspace = std::make_unique<TileEditor>(imgWorkspace, TSize(16,16), true, true, 144, false);
    m_ScratchPad = std::make_unique<TileEditor>(imgScratchPad, TSize(8,8), true, false, 8, false);
    m_RoomSelector = std::make_unique<TileEditor>(imgRoomSelector, TSize(16,16), false, true, 8, true);
    m_Workspace->Mode = TileEditor::temSelect;
	m_ScratchPad->Mode = TileEditor::temSelect;
	m_RoomSelector->Mode = TileEditor::temSelect;
    m_ScratchPad->GridTile = true;
	m_ScratchPad->GridRoom = false;
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
    m_ScratchPad->Mode = TileEditor::temSelect;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actPencilExecute(TObject *Sender)
{
    btnPencil->Down = true;
    m_Workspace->Mode = TileEditor::temPencil;
    m_ScratchPad->Mode = TileEditor::temPencil;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actLineExecute(TObject *Sender)
{
    btnLine->Down = true;
    m_Workspace->Mode = TileEditor::temLine;
    m_ScratchPad->Mode = TileEditor::temLine;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actShapeExecute(TObject *Sender)
{
    btnShape->Down = true;
    m_Workspace->Mode = TileEditor::temShape;
    m_ScratchPad->Mode = TileEditor::temShape;
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
    m_Document->Set(actToggleEditMode->Checked ? meRoom : meMap, m_Workspace->GetEntities());
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
    assetsTiles->sbxListResize(nullptr);
    assetsSprites->sbxListResize(nullptr);
    assetsObjects->sbxListResize(nullptr);
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
    else if (event.Id == "image.modified" || event.Id == "document.added" || event.Id == "document.removed")
    {
        RefreshAssets();
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
		"Select Tool (Alt+1)\r\n"
		"Mouse over            : Highlight an item\r\n"
		"                        Can be moved, duplicated or deleted\r\n"
        "Ctrl + Left MB + Move : Select group of items\r\n"
        "Ctrl + Left MB Click  : Clear selection\r\n\r\n"
		"Pencil (Alt+2), Line (Alt+3), Rectangle (Alt+4) Tools\r\n"
		"Left MB               : Place current asset\r\n"
        "                        Tiles - Hold button and drag mouse to place multiple\r\n"
        "Middle MB             : Remove tile\r\n"
		"                        Tiles - Hold button and drag mouse to remove multiple\r\n\r\n"
        "General\r\n"
        "Shift + Left MB       : Pan the window by moving the mouse\r\n"
        "Ctrl + Del            : Delete selection\r\n"
        "Ctrl + R              : Toggle room grid\r\n"
        "Ctrl + T              : Toggle tile grid\r\n";
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
void __fastcall TfrmEditorMap::pgcAssetsChange(TObject *Sender)
{
	auto state = pgcAssets->ActivePage == tabTiles;
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
	m_ScratchPad->SelectedEntity = document->Id;
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
void __fastcall TfrmEditorMap::actToggleEditModeExecute(TObject *Sender)
{
    actToggleShowStart->Enabled = !actToggleEditMode->Checked;
    imgRoomSelector->Visible = actToggleEditMode->Checked;
    splRoomSelector->Visible = actToggleEditMode->Checked;
    splRoomSelector->Top = imgRoomSelector->Top - 8;
    m_Workspace->Rooms = actToggleEditMode->Checked ? TSize(1, 1) : TSize(16, 16);
    m_Workspace->SetEntities(m_Document->Get(actToggleEditMode->Checked ? meRoom : meMap, m_RoomSelector->SelectedRoom));
    m_Workspace->ShowStartRoom = !actToggleEditMode->Checked && actToggleShowStart->Checked;
    m_Workspace->UpdateMap();
    m_RoomSelector->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::btnWSGridRoomClick(TObject *Sender)
{
    btnWSGridRoom->Down = !btnWSGridRoom->Down;
    m_Workspace->GridRoom = btnWSGridRoom->Down;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::btnWSGridTileClick(TObject *Sender)
{
    btnWSGridTile->Down = !btnWSGridTile->Down;
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
        btnWSGridRoomClick(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMap::actToggleShowStartExecute(TObject *Sender)
{
    m_Workspace->ShowStartRoom = actToggleShowStart->Checked;
}
//---------------------------------------------------------------------------

