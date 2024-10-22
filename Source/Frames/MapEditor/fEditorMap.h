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
#include "LMDButtonPanel.hpp"
#include "LMDControl.hpp"
#include "LMDCustomBevelPanel.hpp"
#include "LMDCustomControl.hpp"
#include "LMDCustomPanel.hpp"
#include "LMDCustomPanelFill.hpp"
#include "LMDCustomParentPanel.hpp"
#include "LMDCustomToolBar.hpp"
#include "LMDToolBar.hpp"
#include "Frames/MapEditor/TileEditor.h"
#include "Project/Document.h"
#include "Project/TiledMapDocument.h"
#include "Messaging/Messaging.h"
#include "Frames/WndProcHandlers.h"
#include "fAssetSelection.h"
//---------------------------------------------------------------------------
class TfrmEditorMap : public TFrame
{
__published:    // IDE-managed Components
    TImageList *tbrImagesEnabled;
    TImageList *tbrImagesDisabled;
    TActionList *tbrActions;
    TAction *actSelect;
    TAction *actPencil;
    TAction *actLine;
    TAction *actRect;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TAction *actUndo;
    TAction *actRedo;
    TPopupMenu *popWorkspace;
    TPopupMenu *popScratchPad;
    TLMDDockSite *dpTileMap;
    TLMDDockPanel *dpScratchPad;
    TLMDDockPanel *dpWorkspace;
    TLMDDockPanel *dpAssets;
    TPanel *panScratchPadView;
    TImage *imgScratchPad;
    TPageControl *pgcAssets;
    TTabSheet *tabTiles;
    TfrmAssetSelection *assetsTiles;
    TTabSheet *tabSprites;
    TfrmAssetSelection *assetsSprites;
    TTabSheet *tabObjects;
    TfrmAssetSelection *assetsObjects;
    TPanel *panWorkspaceView;
    TImage *imgWorkspace;
    TPanel *panToolbars;
    TLabel *lblTools;
    TToolBar *tbrGrids;
    TToolBar *tbrTools;
    TToolButton *btnSelect;
    TToolButton *btnPencil;
    TToolButton *btnLine;
    TToolButton *btnRect;
    TMenuItem *mnuWSCopytoScratchPad;
    TMenuItem *mnuWSMoveToScratchPad;
    TMenuItem *mnuSPCopytoWorkspace;
    TMenuItem *mnuSPDuplicate;
    TMenuItem *mnuWSDuplicate;
    TMenuItem *Delete1;
    TMenuItem *Delete2;
    TMenuItem *N1;
    TMenuItem *N2;
    TActionList *actSmallActions;
    TImageList *imgSmallIcons;
    TAction *actDelete;
    TAction *actDuplicate;
    TAction *actCopyToScratchPad;
    TAction *actMoveToScratchPad;
    TAction *actCopyToWorkspace;
    TToolBar *tbrScratchPad;
    TToolButton *btnScratchCopyFrom;
    TToolButton *btnSep2;
    TToolButton *btnScratchDuplicate;
    TToolButton *btnSep3;
    TToolButton *btnScratchDelete;
    TToolBar *tbrWorkspace;
    TToolButton *btnScratchCopyTo;
    TToolButton *btnScratchMoveTo;
    TToolButton *ToolButton8;
    TToolButton *btnViewDuplicate;
    TToolButton *ToolButton10;
    TToolButton *btnViewDelete;
    TMenuItem *N3;
    TMenuItem *mnuWSToggleToolbar;
    TMenuItem *N4;
    TMenuItem *mnuSPToggleToolbar;
    TToolButton *btnSep1;
    TToolButton *btnSPGridTile;
    TMenuItem *mnuSPToggleGrid;
    TPanel *panSplitter4;
    TAction *actGridTile;
    TAction *actGridRoom;
    TToolButton *btnWSGridTile;
    TToolButton *btnWSGridRoom;
    TToolBar *tbrModes;
    TAction *actToggleStartRoom;
    TToolButton *btnEditModeMultiple;
    TAction *actEditModeFullMap;
    TPanel *panGrids;
    TPanel *panModes;
    TAction *actEntityNext;
    TAction *actEntityPrev;
    TLMDDockPanel *dpRoomSelector;
    TImage *imgRoomSelector;
    TScrollBox *sbxWorkspace;
    TAction *actCopy;
    TAction *actCut;
    TAction *actPaste;
    TStatusBar *sbrWorkspace;
    TStatusBar *sbrRoomSelection;
    TStatusBar *StatusBar1;
    TImage *imgLock;
    TToolButton *ToolButton1;
    TToolButton *btnEntityPrev;
    TToolButton *btnEntityNext;
    TPanel *panVisuals;
    TToolBar *ToolBar1;
    TToolButton *btnToggleDisplayStart;
    TToolButton *btnToggleDisplayRoomNumbers;
    TAction *actToggleRoomNumbers;
    TToolButton *btnToggleDisplayLocks;
    TAction *actToggleShowLocks;
    TToolButton *btnEditModeSingle;
    TAction *actEditModeSingleScreen;
    TAction *actToggleTileTypes;
    TToolButton *btnToggleTileTypes;
    TPanel *Panel1;
    TToolBar *ToolBar2;
    TToolButton *btnToggleSpriteLocks;
    TToolButton *btnSpriteType0;
    TToolBar *ToolBar3;
    TToolButton *btnSpriteType1;
    TToolButton *btnSpriteType2;
    TToolButton *btnSpriteType3;
    TToolButton *btnSpriteType4;
    TToolButton *btnSpriteType5;
    TToolButton *btnSpriteType6;
    TToolButton *btnSpriteType7;
    TToolButton *btnSpriteType8;
    TAction *actSpriteType0;
    TAction *actShowSpriteTypes;
    TAction *actSpriteType1;
    TAction *actSpriteType2;
    TAction *actSpriteType3;
    TAction *actSpriteType4;
    TAction *actSpriteType5;
    TAction *actSpriteType6;
    TAction *actSpriteType7;
    TAction *actSpriteType8;
    TToolButton *btnToggleSpriteTypes;
    TAction *actToggleSpriteLocks;
    void actSelectExecute(TObject *Sender);
    void actPencilExecute(TObject *Sender);
    void actLineExecute(TObject *Sender);
    void actRectExecute(TObject *Sender);
    void actZoomInExecute(TObject *Sender);
    void actZoomOutExecute(TObject *Sender);
    void actZoomResetExecute(TObject *Sender);
    void actUndoExecute(TObject *Sender);
    void actRedoExecute(TObject *Sender);
    void imgScratchPadMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void imgScratchPadMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void imgScratchPadMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void panWorkspaceViewResize(TObject *Sender);
    void imgWorkspaceMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void imgWorkspaceMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void imgWorkspaceMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void dpToolsCloseQuery(TObject *Sender, bool &CanClose);
    void panScratchPadViewResize(TObject *Sender);
    void pgcAssetsResize(TObject *Sender);
    void imgWorkspaceMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);
    void imgWorkspaceMouseEnter(TObject *Sender);
    void actCopyToScratchPadExecute(TObject *Sender);
    void actMoveToScratchPadExecute(TObject *Sender);
    void actCopyToWorkspaceExecute(TObject *Sender);
    void actDuplicateExecute(TObject *Sender);
    void actDeleteExecute(TObject *Sender);
    void mnuWSToggleToolbarClick(TObject *Sender);
    void mnuSPToggleToolbarClick(TObject *Sender);
    void pgcAssetsChange(TObject *Sender);
    void imgRoomSelectorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void imgRoomSelectorMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void imgRoomSelectorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void btnWSGridRoomClick(TObject *Sender);
    void btnWSGridTileClick(TObject *Sender);
    void btnSPGridTileClick(TObject *Sender);
    void actGridTileExecute(TObject *Sender);
    void actGridRoomExecute(TObject *Sender);
    void actEditModeFullMapExecute(TObject *Sender);
    void actToggleStartRoomExecute(TObject *Sender);
    void actEntityNextExecute(TObject *Sender);
    void actEntityPrevExecute(TObject *Sender);
    void sbxWorkspaceMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
    void actCopyExecute(TObject *Sender);
    void actCutExecute(TObject *Sender);
    void actPasteExecute(TObject *Sender);
    void actEntityToggleLocksExecute(TObject *Sender);
    void actToggleRoomNumbersExecute(TObject *Sender);
    void actToggleShowLocksExecute(TObject *Sender);
    void actToggleTileTypesExecute(TObject *Sender);
    void actSpriteType0Execute(TObject *Sender);
    void actShowSpriteTypesExecute(TObject *Sender);

private:    // User declarations
    Registrar      m_Registrar;        // the messaging registrar
    Project::TiledMapDocument*  m_Document;         // the map document we are editiing
    std::unique_ptr<TileEditor> m_Workspace;        // the main workspace editor
    std::unique_ptr<TileEditor> m_ScratchPad;       // the scratch pad editor
    std::unique_ptr<TileEditor> m_RoomSelector;     // the room selection editor
    std::map<String, TAction*>  m_ActionMap;        // a map of actions; used by generic messaging to handle zoom in/out/reset, undo/redo
    std::list<EraseHandler>     m_EraseHandlers;    // stops flicking
    TLMDDockPanel*              m_ActivePanel;      // the active dock panel
    Visuals::ImageMap           m_ImageMap;         // a rendering of each tile, object, sprite that is shared with all the editors
    int                         m_LastSelectedId;   // last selected document id
    int                         m_Scale;

            void                Initialise();
            void                RefreshAssets();
            bool                IsActive() const;
            void                OnEvent(const Event& event);
            void                OnRoomSelected(const RoomSelected& event);
            void                OnStartRoomChanged(const StartRoomChanged& event);
            void                OnDocumentChanged(const DocumentChange<String>& message);
            void                OnEntityClick(Project::ImageDocument* document);
            void                OnWorkspaceEntitySelected(const Project::MapEntity& entity);
            int                 OnRetrieveRoomIndex(const TPoint& pt, bool newIndex = false);
            void                ShowKeysHelp();

public:        // User declarations
                     TfrmEditorMap(TComponent* Owner);
                    ~TfrmEditorMap();

    static  TFrame*  Create(Project::Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorMap(owner);
                                    editor->Document = dynamic_cast<Project::TiledMapDocument*>(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    editor->Initialise();
                                    return editor;
                                }

  __property Project::Document* Document = { read = m_Document, write = m_Document };
};
//---------------------------------------------------------------------------
#endif
