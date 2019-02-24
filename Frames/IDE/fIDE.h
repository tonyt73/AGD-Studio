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
#include "LMDInsPropInsp.hpp"
#include "LMDInsPropPage.hpp"
#include "LMDDckSite.hpp"
#include "LMDPNGImageList.hpp"
#include "ElMenus.hpp"
#include "ElTreeInplaceEditors.hpp"
#include "ElXPThemedControl.hpp"
#include "ElXTree.hpp"
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Build/BuildManager.h"
#include "Factories/DocumentEditorFactory.h"
#include "Frames/WndProcHandlers.h"
//---------------------------------------------------------------------------
class TfrmIDE : public TFrame
{
__published:    // IDE-managed Components
    TLMDDockSite *dsIDE;
    TActionList *actActions;
    TAction *actFileProjectSave;
    TAction *actFileProjectClose;
    TAction *actEditCopy;
    TAction *actEditCut;
    TAction *actEditPaste;
    TMainMenu *mnuMain;
    TMenuItem *mnuFile;
    TMenuItem *mnuFileSave;
    TMenuItem *mnuFileClose;
    TMenuItem *mnuEdit;
    TMenuItem *mnuEditCopy;
    TMenuItem *mnuEditCut;
    TMenuItem *mnuEditPaste;
    TMenuItem *mnuGame;
    TMenuItem *mnuHelp;
    TAction *actHelp;
    TAction *actHelpGettingStarted;
    TAction *actHelpKeymapReference;
    TAction *actHelpTipOfTheDay;
    TAction *actHelpCheckForUpdates;
    TAction *actHelpAbout;
    TMenuItem *mnuHelpHelp;
    TMenuItem *mnuHelpGettingStarted;
    TMenuItem *mnuHelpKeymapReference;
    TMenuItem *N1;
    TMenuItem *mnuHelpCheckforUpdates;
    TMenuItem *N2;
    TMenuItem *mnuHelpAbout;
    TAction *actEditUndo;
    TAction *actEditRedo;
    TMenuItem *N3;
    TMenuItem *mnuEditUndo;
    TMenuItem *mnuEditRedo;
    TToolBar *tbrMain;
    TToolButton *ToolButton3;
    TToolButton *ToolButton1;
    TToolButton *ToolButton4;
    TToolButton *ToolButton5;
    TToolButton *ToolButton6;
    TToolButton *btnEditCopy;
    TToolButton *btnEditCut;
    TToolButton *btnEditPaste;
    TToolButton *ToolButton10;
    TToolButton *ToolButton11;
    TAction *actEditZoomIn;
    TAction *actEditZoomOut;
    TAction *actEditZoomReset;
    TToolButton *ToolButton12;
    TToolButton *ToolButton13;
    TLMDDockPanel *LMDDockPanel2;
    TLMDDockManager *DockManager;
    TLMDDockPanel *dpMessages;
    TLMDDockPanel *dpProject;
    TLMDDockPanel *dpSearchResults;
    TLMDDockPanel *dpBuild;
    TLMDDockPanel *dpTodo;
    TToolButton *ToolButton15;
    TLMDDockPanel *dpProperties;
    TLMDSimplePropInspector *lmdProperties;
    TPanel *Panel1;
    TToolBar *tbrProject;
    TToolButton *tbnProjectExpandAll;
    TToolButton *tbnProjectCollapseAll;
    TImageList *imgProject;
    TToolButton *tbnProjectZ1;
    TToolButton *tbnProjectShowLines;
    TToolButton *tbnProjectHideLines;
    TImageList *imgProjectNodes;
    TToolButton *tbnProjectShowFolders;
    TPanel *Panel2;
    TLabel *lblPropertyInfo;
    TSplitter *Splitter1;
    TElXTree *tvProject;
    TAction *actFileNewAsset;
    TMenuItem *mnuFileNewAsset;
    TMenuItem *N4;
    TAction *actEditFind;
    TAction *actEditFindNext;
    TAction *actEditReplace;
    TAction *actEditFindPrevious;
    TAction *actFileProjectOpen;
    TMenuItem *mnuFileOpenProject;
    TMenuItem *mnuFileMru;
    TOpenTextFileDialog *dlgOpen;
    TPopupMenu *popProject;
    TMenuItem *mnuNewAsset;
    TAction *actNewAsset;
    TMenuItem *DeleteAsset1;
    TAction *actDeleteAsset;
    TPanel *Panel3;
    TToolBar *tbrSettings;
    TToolButton *btnSettings;
    TAction *actSettings;
    TMemo *memMessages;
    TToolButton *btnEditorHelp;
    TToolButton *ToolButton14;
    TAction *actEditorHelp;
    TLMDDockPanel *dpEditorKeys;
    TMemo *mbKeys;
    TAction *actNewAssetCustom;
    TMenuItem *btnNewImageCustom;
    TAction *actViewBuildResults;
    TAction *actViewMessages;
    TAction *actViewSearchResults;
    TAction *actViewTodo;
    TAction *actViewEditorKeys;
    TMenuItem *mnuView;
    TMenuItem *mnuViewBuildResults;
    TMenuItem *mnuViewSearchResults;
    TMenuItem *mnuViewMessages;
    TMenuItem *mnuViewTodo;
    TMenuItem *mnuViewEditorKeys;
    TToolButton *ToolButton2;
    TToolButton *btnBuildRun;
    TAction *actGameRun;
    TMenuItem *mnuRun;
    TImageList *imgBuildNodes;
    TElXTree *tvBuild;
	TImageList *imgToolbar;
    TMenuItem *mnuTools;
    TMenuItem *mnuToolMachineDefinition;
    TMenuItem *mnuToolKeyboardLayout;
    TMenuItem *mnuToolGraphicsMode;
    TMenuItem *mnuSpecialThanks;
    void __fastcall actEditCopyExecute(TObject *Sender);
    void __fastcall actEditCutExecute(TObject *Sender);
    void __fastcall actEditPasteExecute(TObject *Sender);
    void __fastcall actFileProjectCloseExecute(TObject *Sender);
    void __fastcall actHelpAboutExecute(TObject *Sender);
    void __fastcall actEditUndoExecute(TObject *Sender);
    void __fastcall actEditRedoExecute(TObject *Sender);
    void __fastcall tbnProjectExpandAllClick(TObject *Sender);
    void __fastcall tbnProjectCollapseAllClick(TObject *Sender);
    void __fastcall tbnProjectShowLinesClick(TObject *Sender);
    void __fastcall tbnProjectHideLinesClick(TObject *Sender);
    void __fastcall tbnProjectShowFoldersClick(TObject *Sender);
    void __fastcall lmdPropertiesClick(TObject *Sender);
    void __fastcall tvProjectItemSelectedChange(TObject *Sender, TElXTreeItem *Item);
    void __fastcall tvProjectDblClick(TObject *Sender);
    void __fastcall actFileProjectSaveExecute(TObject *Sender);
    void __fastcall actFileNewAssetExecute(TObject *Sender);
    void __fastcall actEditFindExecute(TObject *Sender);
    void __fastcall actEditFindNextExecute(TObject *Sender);
    void __fastcall actEditReplaceExecute(TObject *Sender);
    void __fastcall actEditFindPreviousExecute(TObject *Sender);
    void __fastcall actFileProjectOpenExecute(TObject *Sender);
    void __fastcall actNewAssetExecute(TObject *Sender);
    void __fastcall popProjectPopup(TObject *Sender);
    void __fastcall actEditZoomInExecute(TObject *Sender);
    void __fastcall actEditZoomOutExecute(TObject *Sender);
    void __fastcall actEditZoomResetExecute(TObject *Sender);
    void __fastcall actDeleteAssetExecute(TObject *Sender);
    void __fastcall actSettingsExecute(TObject *Sender);
    void __fastcall actEditorHelpExecute(TObject *Sender);
    void __fastcall actViewBuildResultsExecute(TObject *Sender);
    void __fastcall actViewSearchResultsExecute(TObject *Sender);
    void __fastcall actViewTodoExecute(TObject *Sender);
    void __fastcall actViewEditorKeysExecute(TObject *Sender);
    void __fastcall actViewMessagesExecute(TObject *Sender);
    void __fastcall actGameRunExecute(TObject *Sender);

private:    // User declarations
    ::Messaging::Registrar  m_Registrar;
    DocumentEditorFactory   m_DocumentEditorFactory;
    BuildManager            m_Builder;
    std::list<EraseHandler> m_EraseHandlers;    // stops flicking

    void    __fastcall  UpdateDocumentProperties(Document* document);
    void    __fastcall  OnDocumentClose(TObject *Sender, TLMDockPanelCloseAction& action);
    void    __fastcall  RegisterDocumentEditors();
    void    __fastcall  RefreshMruList();
    void    __fastcall  mruOnClick(TObject *Sender);
    void    __fastcall  OnMessageEvent(const MessageEvent& message);
    void    __fastcall  OnUpdateProperties(const UpdateProperties& event);

    TNotifyEvent        FOnFormClose;

public:        // User declarations
            __fastcall  TfrmIDE(TComponent* Owner);
            __fastcall ~TfrmIDE();

    void    __fastcall  OnActivate(TWinControl* parent);

            __property  TNotifyEvent OnFormClose = { read = FOnFormClose, write = FOnFormClose };
};
//---------------------------------------------------------------------------
#endif
