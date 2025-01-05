//---------------------------------------------------------------------------
#ifndef fEditorMapH
#define fEditorMapH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Menus.hpp>
#include "LMDDckSite.hpp"
#include "fAssetSelection.h"
#include "fEditor.h"
#include "../../WndProcHandlers.h"
#include "TileEditor.h"
#include "fAssetSelection.h"
#include "Project/Documents/Document.h"
#include "Project/Documents/TiledMap.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
class TfrmEditorMap : public TfrmEditor
{
__published:    // IDE-managed Components
    TAction *actCopy;
    TAction *actCopyToScratchPad;
    TAction *actCopyToWorkspace;
    TAction *actCut;
    TAction *actDelete;
    TAction *actDuplicate;
    TAction *actEditModeFullMap;
    TAction *actEditModeSingleScreen;
    TAction *actEntityNext;
    TAction *actEntityPrev;
    TAction *actGridRoom;
    TAction *actGridTile;
    TAction *actLine;
    TAction *actMoveToScratchPad;
    TAction *actPaste;
    TAction *actPencil;
    TAction *actRect;
    TAction *actRedo;
    TAction *actSelect;
    TAction *actShowSpriteTypes;
    TAction *actSpriteType0;
    TAction *actSpriteType1;
    TAction *actSpriteType2;
    TAction *actSpriteType3;
    TAction *actSpriteType4;
    TAction *actSpriteType5;
    TAction *actSpriteType6;
    TAction *actSpriteType7;
    TAction *actSpriteType8;
    TAction *actToggleRoomNumbers;
    TAction *actToggleShowLocks;
    TAction *actToggleSpriteLocks;
    TAction *actToggleSpecialRooms;
    TAction *actToggleTileTypes;
    TAction *actUndo;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TActionList *actSmallActions;
    TActionList *tbrActions;
    TfrmAssetSelection *assetsObjects;
    TfrmAssetSelection *assetsSprites;
    TfrmAssetSelection *assetsTiles;
    TImage *imgLock;
    TImage *imgRoomSelector;
    TImage *imgScratchPad;
    TImage *imgWorkspace;
    TImageList *imgSmallIcons;
    TImageList *tbrImagesDisabled;
    TImageList *tbrImagesEnabled;
    TLabel *lblTools;
    TLMDDockPanel *dpAssets;
    TLMDDockPanel *dpRoomSelector;
    TLMDDockPanel *dpScratchPad;
    TLMDDockPanel *dpWorkspace;
    TLMDDockSite *dpTileMap;
    TMenuItem *Delete1;
    TMenuItem *Delete2;
    TMenuItem *mnuSPCopytoWorkspace;
    TMenuItem *mnuSPDuplicate;
    TMenuItem *mnuSPToggleGrid;
    TMenuItem *mnuSPToggleToolbar;
    TMenuItem *mnuWSCopytoScratchPad;
    TMenuItem *mnuWSDuplicate;
    TMenuItem *mnuWSMoveToScratchPad;
    TMenuItem *mnuWSToggleToolbar;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TPageControl *pgcAssets;
    TPanel *Panel1;
    TPanel *panGrids;
    TPanel *panModes;
    TPanel *panScratchPadView;
    TPanel *panSplitter4;
    TPanel *panToolbars;
    TPanel *panVisuals;
    TPanel *panWorkspaceView;
    TPopupMenu *popScratchPad;
    TPopupMenu *popWorkspace;
    TScrollBox *sbxWorkspace;
    TStatusBar *sbrRoomSelection;
    TStatusBar *sbrWorkspace;
    TStatusBar *StatusBar1;
    TTabSheet *tabObjects;
    TTabSheet *tabSprites;
    TTabSheet *tabTiles;
    TToolBar *tbrGrids;
    TToolBar *tbrModes;
    TToolBar *tbrScratchPad;
    TToolBar *tbrTools;
    TToolBar *tbrWorkspace;
    TToolBar *ToolBar1;
    TToolBar *ToolBar2;
    TToolBar *ToolBar3;
    TToolButton *btnEditModeMultiple;
    TToolButton *btnEditModeSingle;
    TToolButton *btnEntityNext;
    TToolButton *btnEntityPrev;
    TToolButton *btnLine;
    TToolButton *btnPencil;
    TToolButton *btnRect;
    TToolButton *btnScratchCopyFrom;
    TToolButton *btnScratchCopyTo;
    TToolButton *btnScratchDelete;
    TToolButton *btnScratchDuplicate;
    TToolButton *btnScratchMoveTo;
    TToolButton *btnSelect;
    TToolButton *btnSep1;
    TToolButton *btnSep2;
    TToolButton *btnSep3;
    TToolButton *btnSPGridTile;
    TToolButton *btnSpriteType0;
    TToolButton *btnSpriteType1;
    TToolButton *btnSpriteType2;
    TToolButton *btnSpriteType3;
    TToolButton *btnSpriteType4;
    TToolButton *btnSpriteType5;
    TToolButton *btnSpriteType6;
    TToolButton *btnSpriteType7;
    TToolButton *btnSpriteType8;
    TToolButton *btnToggleDisplayLocks;
    TToolButton *btnToggleDisplayRoomNumbers;
    TToolButton *btnToggleDisplayStart;
    TToolButton *btnToggleSpriteLocks;
    TToolButton *btnToggleSpriteTypes;
    TToolButton *btnToggleTileTypes;
    TToolButton *btnViewDelete;
    TToolButton *btnViewDuplicate;
    TToolButton *btnWSGridRoom;
    TToolButton *btnWSGridTile;
    TToolButton *ToolButton1;
    TToolButton *ToolButton10;
    TToolButton *ToolButton8;
    void __fastcall actCopyExecute(TObject *Sender);
    void __fastcall actCopyToScratchPadExecute(TObject *Sender);
    void __fastcall actCopyToWorkspaceExecute(TObject *Sender);
    void __fastcall actCutExecute(TObject *Sender);
    void __fastcall actDeleteExecute(TObject *Sender);
    void __fastcall actDuplicateExecute(TObject *Sender);
    void __fastcall actEditModeFullMapExecute(TObject *Sender);
    void __fastcall actEntityNextExecute(TObject *Sender);
    void __fastcall actEntityPrevExecute(TObject *Sender);
    void __fastcall actEntityToggleLocksExecute(TObject *Sender);
    void __fastcall actGridRoomExecute(TObject *Sender);
    void __fastcall actGridTileExecute(TObject *Sender);
    void __fastcall actLineExecute(TObject *Sender);
    void __fastcall actMoveToScratchPadExecute(TObject *Sender);
    void __fastcall actPasteExecute(TObject *Sender);
    void __fastcall actPencilExecute(TObject *Sender);
    void __fastcall actRectExecute(TObject *Sender);
    void __fastcall actRedoExecute(TObject *Sender);
    void __fastcall actSelectExecute(TObject *Sender);
    void __fastcall actShowSpriteTypesExecute(TObject *Sender);
    void __fastcall actSpriteType0Execute(TObject *Sender);
    void __fastcall actToggleRoomNumbersExecute(TObject *Sender);
    void __fastcall actToggleShowLocksExecute(TObject *Sender);
    void __fastcall actToggleSpecialRoomsExecute(TObject *Sender);
    void __fastcall actToggleTileTypesExecute(TObject *Sender);
    void __fastcall actUndoExecute(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);
    void __fastcall btnSPGridTileClick(TObject *Sender);
    void __fastcall btnWSGridRoomClick(TObject *Sender);
    void __fastcall btnWSGridTileClick(TObject *Sender);
    void __fastcall dpToolsCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall imgRoomSelectorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgRoomSelectorMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgRoomSelectorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgScratchPadMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgScratchPadMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgScratchPadMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgWorkspaceMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);
    void __fastcall imgWorkspaceMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgWorkspaceMouseEnter(TObject *Sender);
    void __fastcall imgWorkspaceMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgWorkspaceMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall mnuSPToggleToolbarClick(TObject *Sender);
    void __fastcall mnuWSToggleToolbarClick(TObject *Sender);
    void __fastcall panScratchPadViewResize(TObject *Sender);
    void __fastcall panWorkspaceViewResize(TObject *Sender);
    void __fastcall pgcAssetsChange(TObject *Sender);
    void __fastcall pgcAssetsResize(TObject *Sender);
    void __fastcall sbxWorkspaceMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);

private:    // User declarations
    Project::TiledMapDocument*  m_TiledDocument;    // the map document we are editiing
    std::unique_ptr<TileEditor> m_Workspace;        // the main workspace editor
    std::unique_ptr<TileEditor> m_ScratchPad;       // the scratch pad editor
    std::unique_ptr<TileEditor> m_RoomSelector;     // the room selection editor
    std::map<String, TAction*>  m_ActionMap;        // a map of actions; used by generic messaging to handle zoom in/out/reset, undo/redo
    std::list<EraseHandler>     m_EraseHandlers;    // stops flicking
    TLMDDockPanel*              m_ActivePanel;      // the active dock panel
    Visuals::ImageMap           m_ImageMap;         // a rendering of each tile, object, sprite that is shared with all the editors
    int                         m_LastSelectedId;   // last selected document id
    int                         m_Scale;

            void    __fastcall  RefreshAssets();
            void    __fastcall  OnInitialise() override;
            void    __fastcall  OnEvent(const Event& event) override;
            void    __fastcall  OnRoomSelected(const RoomSelected& event);
            void    __fastcall  OnSpecialRoomChanged(const SpecialRoomChanged& event);
            void    __fastcall  OnDocumentChanged(const DocumentChange<String>& message);
            void    __fastcall  OnEntityClick(Project::ImageDocument* document);
            void    __fastcall  OnWorkspaceEntitySelected(const Project::MapEntity& entity);
            int     __fastcall  OnRetrieveRoomIndex(const TPoint& pt, bool newIndex = false);

public:     // User declarations
                    __fastcall  TfrmEditorMap(TComponent* Owner) override;
};
//---------------------------------------------------------------------------
#endif
