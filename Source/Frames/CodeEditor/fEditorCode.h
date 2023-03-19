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
#include "Project/Document.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
class TfrmEditorCode : public TFrame
{
__published:    // IDE-managed Components
    TLMDEditView *evEditor;
    TStatusBar *sbStatus;
    TLMDEditDocument *lmdDocument;
    TEditUndo *actUndo;
    TEditUndo *actRedo;
    TActionList *Actions;
    TAction *actBmkSet_0;
    TAction *actBmkSet_9;
    TAction *actBmkSet_8;
    TAction *actBmkSet_7;
    TAction *actBmkSet_6;
    TAction *actBmkSet_5;
    TAction *actBmkSet_4;
    TAction *actToggleShowLineEnds;
    TAction *actToggleShowTabs;
    TAction *actNoWrap;
    TAction *actWrapToWindow;
    TAction *actWrapToRuler;
    TAction *actBmkSet;
    TAction *actBmkDeleteLast;
    TAction *actBmkDeleteAll;
    TAction *actToggleUseTabs;
    TAction *actToggleShowSpaces;
    TAction *actToggleAutoIndent;
    TAction *actGoToLine;
    TAction *actFoldTops;
    TAction *actUnfoldTops;
    TAction *actFoldAll;
    TAction *actUnfoldAll;
    TAction *actFoldCurrentTop;
    TAction *actFoldAllInCurrent;
    TAction *actFoldTopsInCurrent;
    TAction *actUnfoldTopsInCurrent;
    TAction *actUnfoldAllInCurrent;
    TAction *actSearch;
    TAction *actReplace;
    TAction *actSaveFile;
    TAction *actBmkSet_1;
    TAction *actBmkSet_2;
    TAction *actBmkSet_3;
    TAction *actBmkGoto_1;
    TAction *actBmkGoto_2;
    TAction *actBmkGoto_3;
    TAction *actBmkGoto_4;
    TAction *actBmkGoto_5;
    TAction *actBmkGoto_6;
    TAction *actBmkGoto_7;
    TAction *actBmkGoto_8;
    TAction *actBmkGoto_9;
    TAction *actBmkGoto_0;
    TAction *actCopy;
    TAction *actPaste;
    TAction *actCut;
    TAction *actRefreshSchemes;
    TAction *actSearchNext;
    TAction *actKeybindings;
    TAction *actToggleCursorBound;
    TAction *actToggleShowRuler;
    TAction *actFont;
    TAction *actSearchPrevious;
    TAction *actZoomIn;
    TAction *actZoomOut;
    TAction *actZoomReset;
    TFontDialog *FontDialog;
    void __fastcall actUndoExecute(TObject *Sender);
    void __fastcall actRedoExecute(TObject *Sender);
    void __fastcall actGoToLineExecute(TObject *Sender);
    void __fastcall actSearchExecute(TObject *Sender);
    void __fastcall actReplaceExecute(TObject *Sender);
    void __fastcall actCopyExecute(TObject *Sender);
    void __fastcall actPasteExecute(TObject *Sender);
    void __fastcall actCutExecute(TObject *Sender);
    void __fastcall actSearchNextExecute(TObject *Sender);
    void __fastcall actToggleShowSpacesExecute(TObject *Sender);
    void __fastcall actNoWrapExecute(TObject *Sender);
    void __fastcall actToggleAutoIndentExecute(TObject *Sender);
    void __fastcall actKeybindingsExecute(TObject *Sender);
    void __fastcall actToggleCursorBoundExecute(TObject *Sender);
    void __fastcall actToggleShowRulerExecute(TObject *Sender);
    void __fastcall actFontExecute(TObject *Sender);
    void __fastcall actUndoUpdate(TObject *Sender);
    void __fastcall evEditorStatusChanged(TLMDCustomEditView *AView, TLMDViewStatusChanges AChanges);
    void __fastcall actSaveFileExecute(TObject *Sender);
    void __fastcall actSearchPreviousExecute(TObject *Sender);
    void __fastcall evEditorEnter(TObject *Sender);
    void __fastcall actZoomInExecute(TObject *Sender);
    void __fastcall actZoomOutExecute(TObject *Sender);
    void __fastcall actZoomResetExecute(TObject *Sender);

private:    // User declarations
    ::Messaging::Registrar      m_Registrar;
    Document*                   m_Document;
    TLMDEditView*               m_ActiveEdit;
    TLMDEditSearchDlgOptions    m_SearchOptions;

    std::map<String, TAction*>  m_ActionMap;

    bool            __fastcall  IsActive() const;
    String          __fastcall  GetSyntaxScByExt(const String& extension);
    void            __fastcall  OnEvent(const Event& event);

    __property TLMDEditView*    ActiveEdit = { read = m_ActiveEdit };

public:        // User declarations
                    __fastcall  TfrmEditorCode(TComponent* Owner);
                    __fastcall  ~TfrmEditorCode();
    void            __fastcall  SetDocument(Document* document);
    void            __fastcall  UpdateStatus();
    static  TFrame* __fastcall  Create(Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorCode(owner);
                                    editor->SetDocument(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }
};
//---------------------------------------------------------------------------
#endif
