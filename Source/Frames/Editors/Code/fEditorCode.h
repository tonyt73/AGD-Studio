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
#include "Project/Documents/Document.h"
#include "fEditor.h"
#include <Vcl.VirtualImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
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
    TAction *actVariableEditor;
    TAction *actPaste;
    TAction *actRefreshSchemes;
    TAction *actReplace;
    TAction *actSaveFile;
    TAction *actSearch;
    TAction *actSearchNext;
    TAction *actSearchPrevious;
    TAction *actUnfoldAll;
    TAction *actUnfoldAllInCurrent;
    TAction *actUnfoldTops;
    TAction *actUnfoldTopsInCurrent;
    TActionList *Actions;
    TEditUndo *actRedo;
    TEditUndo *actUndo;
    TFontDialog *FontDialog;
    TLMDEditDocument *lmdDocument;
    TLMDEditView *evEditor;
    TStatusBar *sbStatus;
    TVirtualImageList *vilToolbar;
    TImageCollection *icToolbar;
    TAction *actFormat;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TToolBar *ToolBar1;
    TToolButton *tbrFormatCode;
    TToolButton *ToolButton1;
    TToolButton *btnChangeFont;
    TToolButton *ToolButton5;
    void __fastcall actCopyExecute(TObject *Sender);
    void __fastcall actCutExecute(TObject *Sender);
    void __fastcall actFontExecute(TObject *Sender);
    void __fastcall actGoToLineExecute(TObject *Sender);
    void __fastcall actPasteExecute(TObject *Sender);
    void __fastcall actRedoExecute(TObject *Sender);
    void __fastcall actReplaceExecute(TObject *Sender);
    void __fastcall actSaveFileExecute(TObject *Sender);
    void __fastcall actSearchExecute(TObject *Sender);
    void __fastcall actSearchNextExecute(TObject *Sender);
    void __fastcall actSearchPreviousExecute(TObject *Sender);
    void __fastcall actUndoExecute(TObject *Sender);
    void __fastcall actUndoUpdate(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);
    void __fastcall evEditorEnter(TObject *Sender);
    void __fastcall evEditorStatusChanged(TLMDCustomEditView *AView, TLMDViewStatusChanges AChanges);
    void __fastcall actFormatExecute(TObject *Sender);
    void __fastcall evEditorKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FontDialogApply(TObject *Sender, HWND Wnd);
    void __fastcall evEditorNotFound(TObject *Sender, TLMDEditNotFoundAction &Action);

private:    // User declarations
    TLMDEditView*               m_ActiveEdit;
    TLMDEditSearchDlgOptions    m_SearchOptions;
    std::map<String, TAction*>  m_ActionMap;

    void            __fastcall  OnChangeString(const OnChange<String>& event);
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
