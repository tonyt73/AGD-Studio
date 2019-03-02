//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include <LMDSedGotoLineDialog.hpp>
#include <LMDSedColorSchemeDialog.hpp>
#include <LMDSedKeyBindingsDialog.hpp>
#include "fEditorCode.h"
#include "fMain.h"
#include "Project/EditorManager.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LMDSedDocument"
#pragma link "LMDSedView"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
const int SCHEMES_EXTS_COUNT = 28;
const String SCHEMES_EXTS[SCHEMES_EXTS_COUNT] =
{
    "cpp", "hpp", "cxx", "h",
    "c", "js", "vb", "pl", "pm", "py", "tcl",
    "html", "htm",
    "xml", "php", "asp", "lua", "rex",
    "dfm", "pas", "css",
    "txt", "log",
    "sql",
    "event", "agd", "sfx"
};
const String SCHEMES_SYN[SCHEMES_EXTS_COUNT] =
{
    "CPP", "CPP", "CPP", "CPP",
    "C",
    "JavaScript", "VB", "Perl", "Perl", "Python", "TCL",
    "HTML", "HTML",
    "XML", "PHP", "ASP_VB", "Lua", "Rexx",
    "DFM", "Pascal", "CSS",
    "AGD", "AGD",
    "SQL",
    "AGD", "AGD", "AGD"
};
//---------------------------------------------------------------------------
__fastcall TfrmEditorCode::TfrmEditorCode(TComponent* Owner)
: TFrame(Owner)
{
    m_Registrar.Subscribe<Event>(OnEvent);

    m_SearchOptions.Searches.set_length(0);
    m_SearchOptions.Options.Clear();
    m_SearchOptions.Options << soConfirmReplace;
    m_SearchOptions.Direction = sdForward;
    m_SearchOptions.ReplaceAllBounds = rbAllText;
    m_SearchOptions.Start = ssCursor;
}
//---------------------------------------------------------------------------
__fastcall TfrmEditorCode::~TfrmEditorCode()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::SetDocument(Document* document)
{
    m_ActionMap["zoom.in"] = actZoomIn;
    m_ActionMap["zoom.out"] = actZoomOut;
    m_ActionMap["zoom.reset"] = actZoomReset;
    m_ActionMap["edit.copy"] = actCopy;
    m_ActionMap["edit.cut"] = actCut;
    m_ActionMap["edit.paste"] = actPaste;
    m_ActionMap["edit.undo"] = actUndo;
    m_ActionMap["edit.redo"] = actRedo;
    m_ActionMap["edit.find"] = actSearch;
    m_ActionMap["edit.find.next"] = actSearchNext;
    m_ActionMap["edit.find.prev"] = actSearchPrevious;
    m_ActionMap["edit.replace"] = actReplace;
    m_ActionMap["project.save"] = actSaveFile;

    m_Document = document;
    lmdDocument->ClearNoUndo();
    if (System::File::Exists(document->Path))
    {
        lmdDocument->LoadFromFile(document->Path, CP_ACP, true);
        auto extension = System::File::Extension(document->Path).SubString(2, 32);
        auto sc = GetSyntaxScByExt(extension);
        lmdDocument->ActiveSyntaxScheme = sc;
        lmdDocument->ReadOnly = document->IsReadOnly;
    }
    Color = StyleServices()->GetStyleColor(scGenericGradientBase);
}
//---------------------------------------------------------------------------
String __fastcall TfrmEditorCode::GetSyntaxScByExt(const String& extension)
{
    for (auto i = 0; i < SCHEMES_EXTS_COUNT; i++)
    {
        if (LMDLowerCase(extension) == LMDLowerCase(SCHEMES_EXTS[i]))
        {
            return SCHEMES_SYN[i];
        }
    }
    return "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actUndoExecute(TObject *Sender)
{
    if (evEditor->Focused()) evEditor->Undo();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actRedoExecute(TObject *Sender)
{
    if (evEditor->Focused()) evEditor->Redo();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actZoomInExecute(TObject *Sender)
{
    if (evEditor->Focused()&& evEditor->Font->Size <= 24)
    {
        evEditor->Font->Size++;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actZoomOutExecute(TObject *Sender)
{
    if (evEditor->Focused() && evEditor->Font->Size >= 8)
    {
        evEditor->Font->Size--;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actZoomResetExecute(TObject *Sender)
{
    if (evEditor->Focused())
    {
        evEditor->Font->Size = 10;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actGoToLineExecute(TObject *Sender)
{
    if (evEditor->Focused())
    {
        int Line = -1;
        if (mrOk == LMDEditAskGoToLine(evEditor->Document->LinesCount, Line))
        {
            evEditor->GotoPhysLine(Line);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actSearchExecute(TObject *Sender)
{
    if (evEditor->Focused() && LMDEditExecFindDialog("Search text", evEditor, m_SearchOptions) == srNotFound)
    {
        //ShowSearchNotFound();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actReplaceExecute(TObject *Sender)
{
    m_SearchOptions.ReplaceAllBounds = evEditor->SelAvail ? rbSelection : rbAllText;
    auto Res = LMDEditExecReplaceDialog("Replace text", evEditor, m_SearchOptions);

    if ((Res == srFound) && (m_SearchOptions.WasReplaceAllChosen) && (m_SearchOptions.LastNumberOfReplacements > 0))
    {
        TMsgDlgButtons btns;
        btns << mbOK;
        MessageDlg(Format("Ok. Number of replacements: %d", ARRAYOFCONST(( m_SearchOptions.LastNumberOfReplacements ))), mtInformation, btns, -1);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actCopyExecute(TObject *Sender)
{
    if (evEditor->Focused()) evEditor->CopySelection();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actPasteExecute(TObject *Sender)
{
    if (evEditor->Focused()) evEditor->Paste();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actCutExecute(TObject *Sender)
{
    if (evEditor->Focused()) evEditor->CutSelection();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actSearchNextExecute(TObject *Sender)
{
    if (evEditor->SearchLastArgs.Search == "" || m_SearchOptions.Direction != sdForward)
    {
        m_SearchOptions.Direction = sdForward;
        actSearchExecute(Sender);
    }
    else
    {
        if (m_SearchOptions.Direction != sdForward)
        {
            m_SearchOptions.Direction = sdForward;
            evEditor->SearchLastArgs.Direction = sdForward;
            evEditor->SearchFirst(evEditor->SearchLastArgs);
        }
        switch (evEditor->SearchState)
        {
            case stInSearch: evEditor->SearchNext(); break;
            case stInReplace: evEditor->ReplaceNext(); break;
            default: Beep();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actSearchPreviousExecute(TObject *Sender)
{
    if (evEditor->SearchLastArgs.Search == "")
    {
        m_SearchOptions.Direction = sdBackward;
        actSearchExecute(Sender);
    }
    else
    {
        if (m_SearchOptions.Direction != sdBackward)
        {
            m_SearchOptions.Direction = sdBackward;
            evEditor->SearchLastArgs.Direction = sdBackward;
            evEditor->SearchFirst(evEditor->SearchLastArgs);
        }
        switch (evEditor->SearchState)
        {
            case stInSearch: evEditor->SearchNext(); break;
            case stInReplace: evEditor->ReplaceNext(); break;
            default: Beep();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actToggleShowSpacesExecute(TObject *Sender)
{
//  TAction* Act = dynamic_cast<TAction*>( Sender );
//
//  Act->Checked = ! Act->Checked;
//
//  TLMDSpecialCharKinds Kinds = GetShowSpecKinds(Act);
//  TLMDSpecialCharKinds Sets = evEditor->SpecialChars->ShowCharKinds;
//
//  if ( (Sets*Kinds)==TLMDSpecialCharKinds() )
//    Sets = Sets+Kinds;
//  else
//    Sets = Sets-Kinds;
//
//  evEditor->SpecialChars->ShowCharKinds = Sets;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actNoWrapExecute(TObject *Sender)
{
  if (Sender==actNoWrap)
    evEditor->WrapMode = wmNoWrap;
  else if (Sender==actWrapToRuler)
    evEditor->WrapMode = wmWrapToRuler;
  else if (Sender==actWrapToWindow)
    evEditor->WrapMode = wmWrapToWindow;
  else
    throw new Exception("Unknown Wrap action");

  UpdateStatus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actToggleAutoIndentExecute(TObject *Sender)
{
  if (evEditor->ViewSettings.Contains(vsAutoIndent))
    evEditor->ViewSettings = evEditor->ViewSettings >> vsAutoIndent;
  else
    evEditor->ViewSettings = evEditor->ViewSettings << vsAutoIndent;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actKeybindingsExecute(TObject *Sender)
{
    LMDEditExecKeyBindingsDialog(evEditor);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actToggleCursorBoundExecute(TObject *Sender)
{
  if (evEditor->ViewSettings.Contains(vsCursorBoundToChars))
    evEditor->ViewSettings = evEditor->ViewSettings >> vsCursorBoundToChars;
  else
    evEditor->ViewSettings = evEditor->ViewSettings << vsCursorBoundToChars;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actToggleShowRulerExecute(TObject *Sender)
{
  if (evEditor->ViewSettings.Contains(vsShowWrapRuler))
    evEditor->ViewSettings = evEditor->ViewSettings >> vsShowWrapRuler;
  else
    evEditor->ViewSettings = evEditor->ViewSettings << vsShowWrapRuler;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actFontExecute(TObject *Sender)
{
    FontDialog->Font->Assign(evEditor->Font);
    if (FontDialog->Execute())
        evEditor->Font->Assign(FontDialog->Font);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actUndoUpdate(TObject *Sender)
{
    UpdateStatus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::UpdateStatus()
{
  int i, NewW, Ph, LinesCount, CharsCount, PhScr;
  TLMDMarkArray Breaks, Books;
  _di_ILMDMarkers AllBreaks, AllBooks;
  Integer AllBreaksCount, AllBooksCount;
  TLMDSpecialCharKinds SpecKinds;

  Breaks.set_length(0);
  Books.set_length(0);

  actReplace->Enabled = (evEditor->Document!=NULL) && (! evEditor->Document->ReadOnly);
  actSearch->Enabled = evEditor->Document!=NULL;

  if (evEditor->Document==NULL)
    actSearchNext->Enabled = false;
  else
    actSearchNext->Enabled = (! evEditor->Document->ReadOnly) || (evEditor->SearchState!=stInReplace);

  actCopy->Enabled = evEditor->CanCopy;
  actCut->Enabled = evEditor->CanCut && (! lmdDocument->ReadOnly);
  actPaste->Enabled = evEditor->CanPaste && (! lmdDocument->ReadOnly);

  actNoWrap->Enabled = true;
  actWrapToWindow->Enabled = true;
  actWrapToRuler->Enabled = true;
  actToggleAutoIndent->Enabled = true;
  actToggleUseTabs->Enabled = true;
  actToggleShowSpaces->Enabled = true;
  actToggleShowTabs->Enabled = true;
  actToggleShowLineEnds->Enabled = true;
  actToggleShowRuler->Enabled = true;
  actToggleCursorBound->Enabled = true;

  actGoToLine->Enabled = evEditor->Document!=NULL;
 
  actFoldAll->Enabled = evEditor->Document!=NULL;
  actFoldAllInCurrent->Enabled = evEditor->Document!=NULL;
  actFoldCurrentTop->Enabled = evEditor->Document!=NULL;
  actFoldTops->Enabled = evEditor->Document!=NULL;
  actFoldTopsInCurrent->Enabled = evEditor->Document!=NULL;

  actUnfoldAll->Enabled = evEditor->Document!=NULL;
  actUnfoldAllInCurrent->Enabled = evEditor->Document!=NULL;
  actUnfoldTops->Enabled = evEditor->Document!=NULL;
  actUnfoldTopsInCurrent->Enabled = evEditor->Document!=NULL;

  actUndo->Enabled = evEditor->CanUndo && (! lmdDocument->ReadOnly);
  actRedo->Enabled = evEditor->CanRedo && (! lmdDocument->ReadOnly);

  actToggleAutoIndent->Checked = evEditor->ViewSettings.Contains(vsAutoIndent);

  actNoWrap->Checked = evEditor->WrapMode==wmNoWrap;
  actWrapToWindow->Checked = evEditor->WrapMode==wmWrapToWindow;
  actNoWrap->Checked = evEditor->WrapMode==wmWrapToRuler;

  actToggleUseTabs->Checked = evEditor->ViewSettings.Contains(vsUseTabs);

  TLMDSpecialChars* Sc = evEditor->SpecialChars;
  SpecKinds = Sc->ShowCharKinds;
//  actToggleShowSpaces->Checked =
//    (SpecKinds*GetShowSpecKinds(actToggleShowSpaces))!=TLMDSpecialCharKinds();
//  actToggleShowTabs->Checked =
//    (SpecKinds*GetShowSpecKinds(actToggleShowTabs))!=TLMDSpecialCharKinds();
//  actToggleShowLineEnds->Checked =
//    (SpecKinds*GetShowSpecKinds(actToggleShowLineEnds))!=TLMDSpecialCharKinds();

  actToggleShowRuler->Checked = evEditor->ViewSettings.Contains(vsShowWrapRuler);
  actToggleCursorBound->Checked = evEditor->ViewSettings.Contains(vsCursorBoundToChars);

  int Line=0, Col=0;

  evEditor->ScrollPosToPhysical(evEditor->CursorPos, Line, Col);

  sbStatus->Panels->Items[0]->Text = Format("Cur: (%d: %d)", ARRAYOFCONST(( Line + 1, Col + 1 )) );

  if (evEditor->Document != NULL)
  {
    AllBreaks = evEditor->Document->Breakpoints;
    AllBooks = evEditor->Document->Bookmarks;
    AllBreaksCount = AllBreaks->Count;
    AllBooksCount = AllBooks->Count;
  }
  else
  {
    AllBreaks = NULL;
    AllBooks = NULL;
    AllBreaksCount = 0;
    AllBooksCount = 0;
  };

  if ( (evEditor->Document != NULL) && (evEditor->Document->InsideCompoundEdit) )
    return;

  Ph = evEditor->ScrollToPhysical(evEditor->CursorPos.y);
  PhScr = evEditor->PhysicalToScroll(Ph);

  if (evEditor->Document!=NULL)
  {
    LinesCount = evEditor->Document->LinesCount;
    CharsCount = evEditor->Document->CharsCount;
    Breaks = evEditor->Document->Breakpoints->GetMarksByLines(Ph, 1);
    Books =  evEditor->Document->Bookmarks->GetMarksByLines(Ph, 1);
  }
  else
  {
    LinesCount = 1;
    CharsCount = 0;

    Breaks.set_length(0);
    Books.set_length(0);
  };

  int Line1 = 0, Col1 = 0;

  evEditor->ScrollPosToPhysical(evEditor->SelectionStart, Line, Col);
  evEditor->ScrollPosToPhysical(evEditor->SelectionEnd, Line1, Col1);

  sbStatus->Panels->Items[1]->Text = Format("Sel: (%d: %d)(%d: %d)", ARRAYOFCONST(( Line + 1, Col + 1, Line1 + 1, Col1 + 1  )) );

  if ( evEditor->ViewSettings.Contains(vsOverwrite) )
    sbStatus->Panels->Items[2]->Text = "Overwrite";
  else
    sbStatus->Panels->Items[2]->Text = "Insert";


  sbStatus->Panels->Items[3]->Text = Format("View: lines=[%d]", ARRAYOFCONST((LinesCount)) );

  sbStatus->Panels->Items[4]->Text = Format("Doc: chars=%d, lines=%d", ARRAYOFCONST(( CharsCount, LinesCount )) );

  int Cnt = AllBreaksCount;
  sbStatus->Panels->Items[6]->Text = Format("Books: here=%d, all=%d", ARRAYOFCONST(( Books.Length, AllBooksCount )) );

  AnsiString Str;
  if (lmdDocument->CodePageUsePreamble)
    Str = "+";
  else
    Str = "";

  sbStatus->Panels->Items[7]->Text = Format("Encoding: %s", ARRAYOFCONST(( lmdDocument->CodePageName+Str )) );

  sbStatus->Canvas->Font = sbStatus->Font;

  for (int i = 0; i<sbStatus->Panels->Count; i++)
  {
    NewW = sbStatus->Canvas->TextWidth(sbStatus->Panels->Items[i]->Text) + 10;

    sbStatus->Panels->Items[i]->Width =
      Max(sbStatus->Panels->Items[i]->Width, NewW);
  };
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::evEditorStatusChanged(TLMDCustomEditView *AView, TLMDViewStatusChanges AChanges)
{
    UpdateStatus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::OnEvent(const Event& event)
{
    if (evEditor != nullptr && evEditor->Focused() && m_ActionMap.count(event.Id) == 1)
    {
        m_ActionMap[event.Id]->Execute();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actSaveFileExecute(TObject *Sender)
{
    lmdDocument->SaveToFile(m_Document->Path, lmdDocument->CodePage, lmdDocument->CodePageUsePreamble);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::evEditorEnter(TObject *Sender)
{
    theEditorManager.SetActive(this);
}
//---------------------------------------------------------------------------

