//---------------------------------------------------------------------------
#ifndef fEditorMapH
#define fEditorMapH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
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
#include "TileEditor.h"
#include "AssetSelection.h"
#include "Project/Document.h"
#include "Project/MapDocuments.h"
#include "Frames/WndProcHandlers.h"
#include "Messaging/Messaging.h"
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
    TAction *actShape;
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
    TLMDDockPanel *LMDDockPanel4;
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
    TPanel *Panel1;
    TLabel *Label1;
    TToolBar *tbrGrids;
    TToolBar *tbrTools;
    TToolButton *btnSelect;
    TToolButton *btnPencil;
    TToolButton *btnLine;
    TToolButton *btnShape;
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
    TToolButton *ToolButton2;
    TToolButton *btnScratchDuplicate;
    TToolButton *ToolButton4;
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
    TToolButton *ToolButton12;
    TToolButton *btnSPGridTile;
    TMenuItem *mnuSPToggleGrid;
    TToolButton *ToolButton1;
    TToolButton *btnEditMode;
    TAction *actToggleEditMode;
    TSplitter *splRoomSelector;
    TImage *imgRoomSelector;
    TToolButton *ToolButton3;
    TToolButton *btnWSGridRoom;
    TToolButton *btnWSGridTile;
    TAction *actGridTile;
    TAction *actGridRoom;
    TToolButton *ToolButton5;
    TToolButton *btnShowStart;
    TAction *actToggleShowStart;
    void __fastcall actSelectExecute(TObject *Sender);
    void __fastcall actPencilExecute(TObject *Sender);
    void __fastcall actLineExecute(TObject *Sender);
    void __fastcall actShapeExecute(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);
    void __fastcall actUndoExecute(TObject *Sender);
    void __fastcall actRedoExecute(TObject *Sender);
    void __fastcall imgScratchPadMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgScratchPadMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgScratchPadMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall panWorkspaceViewResize(TObject *Sender);
    void __fastcall imgWorkspaceMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgWorkspaceMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgWorkspaceMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall dpToolsCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall panScratchPadViewResize(TObject *Sender);
    void __fastcall pgcAssetsResize(TObject *Sender);
    void __fastcall imgWorkspaceMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);
    void __fastcall imgWorkspaceMouseEnter(TObject *Sender);
    void __fastcall actCopyToScratchPadExecute(TObject *Sender);
    void __fastcall actMoveToScratchPadExecute(TObject *Sender);
    void __fastcall actCopyToWorkspaceExecute(TObject *Sender);
    void __fastcall actDuplicateExecute(TObject *Sender);
    void __fastcall actDeleteExecute(TObject *Sender);
    void __fastcall mnuWSToggleToolbarClick(TObject *Sender);
    void __fastcall mnuSPToggleToolbarClick(TObject *Sender);
    void __fastcall pgcAssetsChange(TObject *Sender);
    void __fastcall actToggleEditModeExecute(TObject *Sender);
    void __fastcall imgRoomSelectorMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgRoomSelectorMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgRoomSelectorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall btnWSGridRoomClick(TObject *Sender);
    void __fastcall btnWSGridTileClick(TObject *Sender);
    void __fastcall btnSPGridTileClick(TObject *Sender);
    void __fastcall actGridTileExecute(TObject *Sender);
    void __fastcall actGridRoomExecute(TObject *Sender);
    void __fastcall actToggleShowStartExecute(TObject *Sender);

private:    // User declarations
    TiledMapDocument*           m_Document;
    std::unique_ptr<TileEditor> m_Workspace;
    std::unique_ptr<TileEditor> m_ScratchPad;
    std::unique_ptr<TileEditor> m_RoomSelector;
    std::map<String, TAction*>  m_ActionMap;        // a map of actions; used by generic messaging to handle zoom in/out/reset, undo/redo
    std::list<EraseHandler>     m_EraseHandlers;
    TLMDDockPanel*              m_ActivePanel;
    Agdx::ImageMap              m_ImageMap;         // a rendering of each tile, object, sprite

            void    __fastcall  Initialise();
            void    __fastcall  RefreshAssets();
            bool    __fastcall  IsActive() const;
            void    __fastcall  OnEvent(const Event& event);
            void    __fastcall  OnRoomSelected(const RoomSelected& event);
            void    __fastcall  OnStartRoomSet(const StartRoomSet& event);
            void    __fastcall  OnDocumentChanged(const DocumentChange<String>& message);
            void    __fastcall  OnMapResize(const OnMapResized& message);
            void     __fastcall OnEntityClick(ImageDocument* document);
            void    __fastcall  OnWorkspaceEntitySelected(const Entity& entity);
            void    __fastcall  ShowKeysHelp();

public:        // User declarations
                    __fastcall  TfrmEditorMap(TComponent* Owner);
                    __fastcall ~TfrmEditorMap();

    static  TFrame* __fastcall  Create(Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorMap(owner);
                                    editor->Document = dynamic_cast<TiledMapDocument*>(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    editor->Initialise();
                                    return editor;
                                }

    __property  Document*       Document = { read = m_Document, write = m_Document };
};
//---------------------------------------------------------------------------
#endif
