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
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include "LMDInsPropInsp.hpp"
#include "LMDInsPropPage.hpp"
#include "LMDDckSite.hpp"
#include "LMDPNGImageList.hpp"
#include "ElTreeInplaceEditors.hpp"
#include "ElXPThemedControl.hpp"
#include "ElXTree.hpp"
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
class TfrmIDE : public TFrame
{
__published:    // IDE-managed Components
    TLMDDockSite *dsIDE;
    TActionList *actActions;
    TAction *actFileProjectNew;
    TAction *actFileProjectOpen;
    TAction *actFileProjectSave;
    TAction *actFileProjectClose;
    TAction *actFileExit;
    TAction *actEditCopy;
    TAction *actEditCut;
    TAction *actEditPaste;
    TImageList *imgIconsActive;
    TMainMenu *mnuMain;
    TMenuItem *mnuFile;
    TMenuItem *mnuFileNew;
    TMenuItem *mnuFileOpen;
    TMenuItem *mnuFileSave;
    TMenuItem *mnuFileClose;
    TMenuItem *mnuLine1;
    TMenuItem *mnuFileExit;
    TMenuItem *mnuEdit;
    TMenuItem *mnuEditCopy;
    TMenuItem *mnuEditCut;
    TMenuItem *mnuEditPaste;
    TMenuItem *mnuView;
    TMenuItem *mnuBuild;
    TMenuItem *mnuWindow;
    TMenuItem *Help1;
    TAction *actHelp;
    TAction *actHelpGettingStarted;
    TAction *actHelpKeymapReference;
    TAction *actHelpTipOfTheDay;
    TAction *actHelpCheckForUpdates;
    TAction *actHelpAbout;
    TMenuItem *mnuHelp;
    TMenuItem *mnuHelpGettingStarted;
    TMenuItem *mnuHelpKeymapReference;
    TMenuItem *mnuHelpTipOfTheDay;
    TMenuItem *N1;
    TMenuItem *mnuHelpCheckforUpdates;
    TMenuItem *N2;
    TMenuItem *mnuHelpAbout;
    TAction *actEditUndo;
    TAction *actEditRedo;
    TMenuItem *N3;
    TMenuItem *mnuEditUndo;
    TMenuItem *mnuEditRedo;
    TPanel *panNavigationBar;
    TToolBar *tbrMain;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TToolButton *ToolButton1;
    TToolButton *ToolButton4;
    TToolButton *ToolButton5;
    TToolButton *ToolButton6;
    TToolButton *ToolButton7;
    TToolButton *ToolButton8;
    TToolButton *ToolButton9;
    TToolButton *ToolButton10;
    TToolButton *ToolButton11;
    TAction *actEditZoomIn;
    TAction *actEditZoomOut;
    TAction *actEditZoomReset;
    TToolButton *ToolButton12;
    TToolButton *ToolButton13;
    TToolButton *ToolButton14;
    TImageList *imgIconsDisabled;
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
    void __fastcall actFileExitExecute(TObject *Sender);
    void __fastcall actEditCopyExecute(TObject *Sender);
    void __fastcall actEditCutExecute(TObject *Sender);
    void __fastcall actEditPasteExecute(TObject *Sender);
    void __fastcall actFileProjectNewExecute(TObject *Sender);
    void __fastcall actFileProjectOpenExecute(TObject *Sender);
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

private:    // User declarations
    void __fastcall UpdateProperties(Document* document);
    void __fastcall OnDocumentClose(TObject *Sender, TLMDockPanelCloseAction& action);
    void __fastcall RegisterDocumentEditors();

public:        // User declarations
    TNotifyEvent    FOnFormClose;
    __fastcall         TfrmIDE(TComponent* Owner);
    __fastcall        ~TfrmIDE();

    void __fastcall OnActivate();

    __property    TNotifyEvent OnFormClose = { read = FOnFormClose, write = FOnFormClose };
};
//---------------------------------------------------------------------------
#endif
