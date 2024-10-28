//---------------------------------------------------------------------------
#ifndef fEditorCodeH
#define fEditorCodeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.Dialogs.hpp>
#include <System.Actions.hpp>
#include <LMDDckSite.hpp>
#include <LMDSedDocument.hpp>
#include <LMDSedView.hpp>
#include <LMDSedFindDialog.hpp>
#include "LMDButtonPanel.hpp"
#include "LMDControl.hpp"
#include "LMDCustomBevelPanel.hpp"
#include "LMDCustomControl.hpp"
#include "LMDCustomPanel.hpp"
#include "LMDCustomPanelFill.hpp"
#include "LMDCustomParentPanel.hpp"
#include "LMDCustomToolBar.hpp"
#include "LMDToolBar.hpp"
//---------------------------------------------------------------------------
#include "../fEditor.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Project/Document.h"
#include "fEditor.h"
//---------------------------------------------------------------------------
class TfrmEditorCode : public TfrmEditor
{
__published:    // IDE-managed Components
    TAction *actBmkDeleteAll;
    TAction *actBmkDeleteLast;
    TAction *actBmkGoto_0;
    TAction *actBmkGoto_1;
    TAction *actBmkGoto_2;
    TAction *actBmkGoto_3;
    TAction *actBmkGoto_4;
    TAction *actBmkGoto_5;
    TAction *actBmkGoto_6;
    TAction *actBmkGoto_7;
    TAction *actBmkGoto_8;
    TAction *actBmkGoto_9;
    TAction *actBmkSet_0;
    TAction *actBmkSet_1;
    TAction *actBmkSet_2;
    TAction *actBmkSet_3;
    TAction *actBmkSet_4;
    TAction *actBmkSet_5;
    TAction *actBmkSet_6;
    TAction *actBmkSet_7;
    TAction *actBmkSet_8;
    TAction *actBmkSet_9;
    TAction *actBmkSet;
    TAction *actCopy;
    TAction *actCut;
    TAction *actFoldAll;
    TAction *actFoldAllInCurrent;
    TAction *actFoldCurrentTop;
    TAction *actFoldTops;
    TAction *actFoldTopsInCurrent;
    TAction *actFont;
    TAction *actGoToLine;
    TAction *Action1;
    TAction *actKeybindings;
    TAction *actNoWrap;
    TAction *actPaste;
    TAction *actRefreshSchemes;
    TAction *actReplace;
    TAction *actSaveFile;
    TAction *actSearch;
    TAction *actSearchNext;
    TAction *actSearchPrevious;
    TAction *actToggleAutoIndent;
    TAction *actToggleCursorBound;
    TAction *actToggleShowLineEnds;
    TAction *actToggleShowRuler;
    TAction *actToggleShowSpaces;
    TAction *actToggleShowTabs;
    TAction *actToggleUseTabs;
    TAction *actUnfoldAll;
    TAction *actUnfoldAllInCurrent;
    TAction *actUnfoldTops;
    TAction *actUnfoldTopsInCurrent;
    TAction *actWrapToRuler;
    TAction *actWrapToWindow;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TActionList *Actions;
    TEditUndo *actRedo;
    TEditUndo *actUndo;
    TFontDialog *FontDialog;
    TLMDEditDocument *lmdDocument;
    TLMDEditView *evEditor;
    TLMDToolBar *LMDToolBar1;
    TStatusBar *sbStatus;
    void __fastcall actCopyExecute(TObject *Sender);
    void __fastcall actCutExecute(TObject *Sender);
    void __fastcall actFontExecute(TObject *Sender);
    void __fastcall actGoToLineExecute(TObject *Sender);
    void __fastcall actKeybindingsExecute(TObject *Sender);
    void __fastcall actNoWrapExecute(TObject *Sender);
    void __fastcall actPasteExecute(TObject *Sender);
    void __fastcall actRedoExecute(TObject *Sender);
    void __fastcall actReplaceExecute(TObject *Sender);
    void __fastcall actSaveFileExecute(TObject *Sender);
    void __fastcall actSearchExecute(TObject *Sender);
    void __fastcall actSearchNextExecute(TObject *Sender);
    void __fastcall actSearchPreviousExecute(TObject *Sender);
    void __fastcall actToggleAutoIndentExecute(TObject *Sender);
    void __fastcall actToggleCursorBoundExecute(TObject *Sender);
    void __fastcall actToggleShowRulerExecute(TObject *Sender);
    void __fastcall actToggleShowSpacesExecute(TObject *Sender);
    void __fastcall actUndoExecute(TObject *Sender);
    void __fastcall actUndoUpdate(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);
    void __fastcall evEditorEnter(TObject *Sender);
    void __fastcall evEditorStatusChanged(TLMDCustomEditView *AView, TLMDViewStatusChanges AChanges);

private:    // User declarations
    TLMDEditView*               m_ActiveEdit;
    TLMDEditSearchDlgOptions    m_SearchOptions;
    std::map<String, TAction*>  m_ActionMap;

    String          __fastcall  GetSyntaxScByExt(const String& extension);
    void            __fastcall  OnEvent(const Event& event);

    __property TLMDEditView*    ActiveEdit = { read = m_ActiveEdit };

public:        // User declarations
                    __fastcall  TfrmEditorCode(TComponent* Owner);

    void            __fastcall  SetDocument(Project::Document* document);
    void            __fastcall  UpdateStatus();
    static  TFrame* __fastcall  Create(Project::Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorCode(owner);
                                    editor->SetDocument(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }
};
//---------------------------------------------------------------------------
#endif
