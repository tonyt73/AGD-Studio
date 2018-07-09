//---------------------------------------------------------------------------
#ifndef fEditorMapH
#define fEditorMapH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDDckSite.hpp"
#include "Project/Document.h"
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Menus.hpp>
#include "TileEditor.h"
#include "AssetSelection.h"
#include "MapDocuments.h"
#include "WndProcHandlers.h"
//---------------------------------------------------------------------------
class TfrmEditorMap : public TFrame
{
__published:    // IDE-managed Components
    TPanel *panToolbar;
    TLabel *Label1;
    TToolBar *tbrTools;
    TToolButton *btnSelect;
    TToolButton *btnPencil;
    TToolButton *btnLine;
    TToolButton *btnShape;
    TPanel *panSplitter1;
    TPanel *panSplitter3;
    TPanel *panSplitter4;
    TToolBar *tbrGrids;
    TToolButton *btnGridRoom;
    TToolButton *btnGridTile;
    TImageList *tbrImagesEnabled;
    TImageList *tbrImagesDisabled;
    TActionList *tbrActions;
    TAction *actSelect;
    TAction *actPencil;
    TAction *actLine;
    TAction *actShape;
    TAction *actGridTile;
    TAction *actGridRoom;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TAction *actUndo;
    TAction *actRedo;
    TPanel *panEditorContainer;
    TPanel *Panel1;
    TPanel *panWorkspaceContainer;
    TSplitter *Splitter1;
    TPanel *Panel4;
    TPopupMenu *popWorkspace;
    TPopupMenu *popScratchPad;
    TPanel *panScratchPadContainer;
    TPanel *Panel5;
    TSplitter *Splitter2;
    TPanel *Panel6;
    TPageControl *PageControl1;
    TTabSheet *tabTiles;
    TTabSheet *tabSprites;
    TTabSheet *tabObjects;
    TPanel *panScratchPadView;
    TImage *imgScratchPad;
    TPanel *panWorkspaceView;
    TImage *imgWorkspace;
    TfrmAssetSelection *assetsTiles;
    TfrmAssetSelection *assetsSprites;
    TfrmAssetSelection *assetsObjects;
    void __fastcall actSelectExecute(TObject *Sender);
    void __fastcall actPencilExecute(TObject *Sender);
    void __fastcall actLineExecute(TObject *Sender);
    void __fastcall actShapeExecute(TObject *Sender);
    void __fastcall actGridTileExecute(TObject *Sender);
    void __fastcall actGridRoomExecute(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);
    void __fastcall actUndoExecute(TObject *Sender);
    void __fastcall actRedoExecute(TObject *Sender);
    void __fastcall imgScratchPadMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imgScratchPadMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall imgScratchPadMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall panWorkspaceViewResize(TObject *Sender);
    void __fastcall imgWorkspaceMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall imgWorkspaceMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
    void __fastcall imgWorkspaceMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
private:    // User declarations
    TiledMapDocument*           m_Document;
    std::unique_ptr<TileEditor> m_Workspace;
    std::unique_ptr<TileEditor> m_ScratchPad;
    std::map<String, TAction*>  m_ActionMap;        // a map of actions; used by generic messaging to handle zoom in/out/reset, undo/redo
    std::list<WinControlEraseHandler> m_EraseHandlers;

            void    __fastcall  Initialise();
            void    __fastcall  RefreshAssets();
            bool    __fastcall  IsActive() const;
            void    __fastcall  OnEvent(const Event& event);
            void    __fastcall  OnMapResize(const OnMapResized& message);


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
