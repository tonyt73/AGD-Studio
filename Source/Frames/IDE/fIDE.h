//---------------------------------------------------------------------------
#ifndef fIDEH
#define fIDEH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ThemedActnCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.WinXPanels.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.VirtualImageList.hpp>
#include <Xml.XMLIntf.hpp>
#include "ElTreeInplaceEditors.hpp"
#include "ElXPThemedControl.hpp"
#include "ElXTree.hpp"
#include "LMDDckSite.hpp"
#include "LMDInsPropInsp.hpp"
#include "LMDInsPropPage.hpp"
//---------------------------------------------------------------------------
#include "Build/BuildManager.h"
#include "Factories/DocumentEditorFactory.h"
#include "Frames/WndProcHandlers.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Project/Documents/Document.h"
//---------------------------------------------------------------------------
class TfrmIDE : public TFrame
{
__published:    // IDE-managed Components
    TAction *actDeleteAsset;
    TAction *actEditCopy;
    TAction *actEditCut;
    TAction *actEditFind;
    TAction *actEditFindNext;
    TAction *actEditFindPrevious;
    TAction *actEditorHelp;
    TAction *actEditPaste;
    TAction *actEditRedo;
    TAction *actEditReplace;
    TAction *actEditUndo;
    TAction *actEditZoomIn;
    TAction *actEditZoomOut;
    TAction *actEditZoomReset;
    TAction *actFileProjectClose;
    TAction *actFileProjectOpen;
    TAction *actFileProjectSave;
    TAction *actGameRun;
    TAction *actHelp;
    TAction *actHelpAbout;
    TAction *actHelpCheckForUpdates;
    TAction *actHelpGettingStarted;
    TAction *actHelpKeymapReference;
    TAction *actHelpTipOfTheDay;
    TAction *actFileNewImageDefault;
    TAction *actFileNewTileCustom;
    TAction *actSettings;
    TAction *actViewBuildResults;
    TAction *actViewEditorKeys;
    TAction *actViewMessages;
    TAction *actViewSearchResults;
    TAction *actViewTodo;
    TActionList *actActions;
    TElXTree *tvBuild;
    TElXTree *tvProject;
    TImageCollection *icProject;
    TImageCollection *icToolbar;
    TImageList *imgBuildNodes;
    TImageList *imgProjectNodes;
    TLabel *lblPropertyInfo;
    TLMDDockManager *DockManager;
    TLMDDockPanel *dpBuild;
    TLMDDockPanel *dpEditorKeys;
    TLMDDockPanel *dpMessages;
    TLMDDockPanel *dpProject;
    TLMDDockPanel *dpProperties;
    TLMDDockPanel *dpSearchResults;
    TLMDDockPanel *dpTodo;
    TLMDDockPanel *LMDDockPanel2;
    TLMDDockSite *dsIDE;
    TLMDSimplePropInspector *lmdProperties;
    TMainMenu *mnuMain;
    TMemo *mbKeys;
    TMemo *memMessages;
    TMenuItem *DeleteAsset1;
    TMenuItem *mnuEdit;
    TMenuItem *mnuEditCopy;
    TMenuItem *mnuEditCut;
    TMenuItem *mnuEditPaste;
    TMenuItem *mnuEditRedo;
    TMenuItem *mnuEditUndo;
    TMenuItem *mnuFile;
    TMenuItem *mnuFileClose;
    TMenuItem *mnuFileMru;
    TMenuItem *mnuFileOpenProject;
    TMenuItem *mnuFileSave;
    TMenuItem *mnuGame;
    TMenuItem *mnuHelp;
    TMenuItem *mnuHelpAbout;
    TMenuItem *mnuHelpCheckforUpdates;
    TMenuItem *mnuHelpGettingStarted;
    TMenuItem *mnuHelpHelp;
    TMenuItem *mnuHelpKeymapReference;
    TMenuItem *mnuNewAsset;
    TMenuItem *mnuRun;
    TMenuItem *mnuSpecialThanks;
    TMenuItem *mnuToolGraphicsMode;
    TMenuItem *mnuToolKeyboardLayout;
    TMenuItem *mnuToolMachineDefinition;
    TMenuItem *mnuTools;
    TMenuItem *mnuView;
    TMenuItem *mnuViewBuildResults;
    TMenuItem *mnuViewEditorKeys;
    TMenuItem *mnuViewMessages;
    TMenuItem *mnuViewSearchResults;
    TMenuItem *mnuViewTodo;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TMenuItem *N5;
    TMenuItem *Settings1;
    TOpenTextFileDialog *dlgOpen;
    TPanel *Panel1;
    TPanel *Panel2;
	TPanel *panToolbar;
    TPopupMenu *popProject;
    TSplitter *Splitter1;
    TToolBar *tbrMain;
    TToolBar *tbrProject;
    TToolBar *tbrSettings;
    TToolButton *btnBuildRun;
    TToolButton *btnEditCopy;
    TToolButton *btnEditCut;
    TToolButton *btnEditorHelp;
    TToolButton *btnEditPaste;
    TToolButton *btnSettings;
    TToolButton *tbnProjectCollapseAll;
    TToolButton *tbnProjectExpandAll;
    TToolButton *tbnProjectHideLines;
    TToolButton *tbnProjectShowFolders;
    TToolButton *tbnProjectShowLines;
    TToolButton *tbnProjectZ1;
    TToolButton *ToolButton1;
    TToolButton *ToolButton10;
    TToolButton *ToolButton11;
    TToolButton *ToolButton12;
    TToolButton *ToolButton13;
    TToolButton *ToolButton14;
    TToolButton *btnFileNewTileCustom;
    TToolButton *ToolButton2;
    TToolButton *ToolButton4;
    TToolButton *ToolButton5;
    TToolButton *ToolButton6;
    TVirtualImageList *vilProject;
    TVirtualImageList *vilToolbar;
    TMenuItem *NewTileImageCustomSize1;
    TToolButton *btnFileNewImage;
    TAction *actFileNewTile;
    TMenuItem *New1;
    TAction *actFileNewObject;
    TAction *actFileNewSprite;
    TToolButton *ToolButton3;
    TToolButton *ToolButton7;
    TMenuItem *N6;
    TMenuItem *NewObjectDefaultSize1;
    TMenuItem *NewSpriteDefaultSize1;
    TMenuItem *NewTileDefaultSize1;
    TAction *actEditDuplicateImage;
    TMenuItem *DuplicateImage1;
    TAction *actEditSplitIntoTiles;
    TMenuItem *Replace1;
    void __fastcall actDeleteAssetExecute(TObject *Sender);
    void __fastcall actEditCopyExecute(TObject *Sender);
    void __fastcall actEditCutExecute(TObject *Sender);
    void __fastcall actEditFindExecute(TObject *Sender);
    void __fastcall actEditFindNextExecute(TObject *Sender);
    void __fastcall actEditFindPreviousExecute(TObject *Sender);
    void __fastcall actEditorHelpExecute(TObject *Sender);
    void __fastcall actEditPasteExecute(TObject *Sender);
    void __fastcall actEditRedoExecute(TObject *Sender);
    void __fastcall actEditReplaceExecute(TObject *Sender);
    void __fastcall actEditUndoExecute(TObject *Sender);
    void __fastcall actEditZoomInExecute(TObject *Sender);
    void __fastcall actEditZoomOutExecute(TObject *Sender);
    void __fastcall actEditZoomResetExecute(TObject *Sender);
    void __fastcall actFileProjectCloseExecute(TObject *Sender);
    void __fastcall actFileProjectOpenExecute(TObject *Sender);
    void __fastcall actFileProjectSaveExecute(TObject *Sender);
    void __fastcall actGameRunExecute(TObject *Sender);
    void __fastcall actHelpAboutExecute(TObject *Sender);
    void __fastcall actFileNewImageDefaultExecute(TObject *Sender);
    void __fastcall actSettingsExecute(TObject *Sender);
    void __fastcall actViewBuildResultsExecute(TObject *Sender);
    void __fastcall actViewEditorKeysExecute(TObject *Sender);
    void __fastcall actViewMessagesExecute(TObject *Sender);
    void __fastcall actViewSearchResultsExecute(TObject *Sender);
    void __fastcall actViewTodoExecute(TObject *Sender);
    void __fastcall lmdPropertiesClick(TObject *Sender);
    void __fastcall popProjectPopup(TObject *Sender);
    void __fastcall tbnProjectCollapseAllClick(TObject *Sender);
    void __fastcall tbnProjectExpandAllClick(TObject *Sender);
    void __fastcall tbnProjectHideLinesClick(TObject *Sender);
    void __fastcall tbnProjectShowFoldersClick(TObject *Sender);
    void __fastcall tbnProjectShowLinesClick(TObject *Sender);
    void __fastcall tvProjectDblClick(TObject *Sender);
    void __fastcall tvProjectItemSelectedChange(TObject *Sender, TElXTreeItem *Item);
    void __fastcall dsIDEChange(TObject *Sender);
    void __fastcall actFileNewTileCustomExecute(TObject *Sender);
    void __fastcall popProjectClose(TObject *Sender);
    void __fastcall actFileNewTileExecute(TObject *Sender);
    void __fastcall actFileNewObjectExecute(TObject *Sender);
    void __fastcall actFileNewSpriteExecute(TObject *Sender);
    void __fastcall actEditDuplicateImageExecute(TObject *Sender);
    void __fastcall actEditSplitIntoTilesExecute(TObject *Sender);

private:                // User declarations
    Registrar                           m_Registrar;
    Factories::DocumentEditorFactory    m_DocumentEditorFactory;
    Build::BuildManager                 m_Builder;
    std::list<EraseHandler>             m_EraseHandlers;    // stops flicking
    std::map<String,bool>               m_RegisteredCategories;

    void    __fastcall  UpdateDocumentProperties(Project::Document* document);
    void    __fastcall  DoOpenDocument(Project::Document* document);
    void    __fastcall  OnDocumentClose(TObject *Sender, TLMDockPanelCloseAction& action);
    void    __fastcall  RegisterDocumentEditors();
    void    __fastcall  RefreshMruList();
    void    __fastcall  mruOnClick(TObject *Sender);
                        // message event handlers
    void    __fastcall  OnMessageEvent(const MessageEvent& message);
    void    __fastcall  OnUpdateProperties(const UpdateProperties& event);
    void    __fastcall  OnOpenDocument(const OpenDocument& event);

    TNotifyEvent        FOnFormClose;

public:                 // User declarations
            __fastcall  TfrmIDE(TComponent* Owner) override;
            __fastcall ~TfrmIDE() override;

    void    __fastcall  OnActivate(TWinControl* parent);
    void    __fastcall  OnClose();

            __property  TNotifyEvent OnFormClose = { read = FOnFormClose, write = FOnFormClose };
};
//---------------------------------------------------------------------------
#endif
