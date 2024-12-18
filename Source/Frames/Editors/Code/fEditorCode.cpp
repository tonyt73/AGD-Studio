//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include <LMDSedGotoLineDialog.hpp>
#include <LMDSedColorSchemeDialog.hpp>
#include <LMDSedKeyBindingsDialog.hpp>
//---------------------------------------------------------------------------
#include "fEditorCode.h"
#include "../EditorManager.h"
#include "Forms/fMain.h"
#include "Project/Documents/Settings.h"
#include "Settings/ThemeManager.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "fEditor"
#pragma link "LMDSedDocument"
#pragma link "LMDSedView"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
const int SCHEMES_EXTS_COUNT = 5;
const String SCHEMES_EXTS[SCHEMES_EXTS_COUNT] =
{
    "txt", "log", "event", "agd", "sfx"
};
const String SCHEMES_SYN[SCHEMES_EXTS_COUNT] =
{
    "AGD", "AGD", "AGD", "AGD", "AGD"
};
//---------------------------------------------------------------------------
__fastcall TfrmEditorCode::TfrmEditorCode(TComponent* Owner)
: TfrmEditor(Owner, "Code Editor")
{
    m_KeysHelp =
    "Edit\r\n"
    " Ctrl+C       : Copy selected text\r\n"
    " Ctrl+X       : Cut selected text\r\n"
    " Ctrl+V       : Paste selected text\r\n"
    " Ctrl+Z       : Undo changes\r\n"
    " Ctrl+Shift+Z : Redo changes\r\n"
    "Search\r\n"
    " Ctrl+F       : Search dialog\r\n"
    " F3           : Find next\r\n"
    " Shift+F3     : Find previous\r\n"
    " Ctrl+H       : Find/Replace dialog\r\n\r\n"
    "Navigation\r\n"
    " Ctrl+G       : Goto line number\r\n\r\n"
    "Settings\r\n"
    " Alt+F        : Change Font dialog\r\n"
    " Ctrl+=       : Increase font size\r\n"
    " Ctrl+-       : Decrease font size\r\n"
    " Ctrl+0       : Reset font size\r\n\r\n"
    "File\r\n"
    " Ctrl+S       : Save changes\r\n";

    m_SearchOptions.Searches.set_length(0);
    m_SearchOptions.Options.Clear();
    m_SearchOptions.Options << soConfirmReplace;
    m_SearchOptions.Direction = sdForward;
    m_SearchOptions.ReplaceAllBounds = rbAllText;
    m_SearchOptions.Start = ssCursor;

    m_Registrar.Subscribe<OnChange<String>>(OnChangeString);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::OnChangeString(const OnChange<String>& event)
{
    if (event.Id == "code.editor.font") {
        auto font = SplitString(event.Value, ":");
        evEditor->Font->Name = font[0];
        evEditor->Font->Height = StrToIntDef(font[1], -13);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::OnDocumentSet()
{
    m_ActionMap["zoom.in"       ] = actZoomIn;
    m_ActionMap["zoom.out"      ] = actZoomOut;
    m_ActionMap["zoom.reset"    ] = actZoomReset;
    m_ActionMap["edit.copy"     ] = actCopy;
    m_ActionMap["edit.cut"      ] = actCut;
    m_ActionMap["edit.paste"    ] = actPaste;
    m_ActionMap["edit.undo"     ] = actUndo;
    m_ActionMap["edit.redo"     ] = actRedo;
    m_ActionMap["edit.find"     ] = actSearch;
    m_ActionMap["edit.find.next"] = actSearchNext;
    m_ActionMap["edit.find.prev"] = actSearchPrevious;
    m_ActionMap["edit.replace"  ] = actReplace;
    m_ActionMap["project.save"  ] = actSaveFile;

    theEditorManager.SetActive(this);
    lmdDocument->ClearNoUndo();
    if (Services::File::Exists(Document->Path)) {
        lmdDocument->LoadFromFile(Document->Path, CP_ACP, true);
        auto extension = Services::File::Extension(Document->Path).SubString(2, 32);
        auto sc = GetSyntaxScByExt(extension);
        lmdDocument->ActiveSyntaxScheme = sc;
        lmdDocument->ReadOnly = Document->IsReadOnly;
    }
    Color = ThemeManager::Background;
    evEditor->ViewSettings = evEditor->ViewSettings << vsAutoIndent;
    if (theAppSettings.CodeEditorFontName.Trim() != "") {
        evEditor->Font->Name = theAppSettings.CodeEditorFontName;
        evEditor->Font->Height = StrToIntDef(theAppSettings.CodeEditorFontHeight, -13);
    }
}
//---------------------------------------------------------------------------
String __fastcall TfrmEditorCode::GetSyntaxScByExt(const String& extension)
{
    for (auto i = 0; i < SCHEMES_EXTS_COUNT; i++) {
        if (LMDLowerCase(extension) == LMDLowerCase(SCHEMES_EXTS[i])) {
            return SCHEMES_SYN[i];
        }
    }
    return "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actUndoExecute(TObject *Sender)
{
    if (IsActive()) {
        evEditor->Undo();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actRedoExecute(TObject *Sender)
{
    if (IsActive()) {
        evEditor->Redo();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actZoomInExecute(TObject *Sender)
{
    if (IsActive() && evEditor->Font->Size <= 24) {
        evEditor->Font->Size++;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actZoomOutExecute(TObject *Sender)
{
    if (IsActive() && evEditor->Font->Size >= 8) {
        evEditor->Font->Size--;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actZoomResetExecute(TObject *Sender)
{
    if (IsActive()) {
        evEditor->Font->Size = 10;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actGoToLineExecute(TObject *Sender)
{
    if (IsActive()) {
        int Line = -1;
        if (mrOk == LMDEditAskGoToLine(evEditor->Document->LinesCount, Line)) {
            evEditor->GotoPhysLine(Line);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actSearchExecute(TObject *Sender)
{
    if (IsActive() && LMDEditExecFindDialog("Search text", evEditor, m_SearchOptions) == srNotFound) {
        WarningMessage("[Code Editor] Search text (" + evEditor->SearchLastArgs.Search +  ") not found.");
        Beep();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actReplaceExecute(TObject *Sender)
{
    if (IsActive()) {
        m_SearchOptions.ReplaceAllBounds = evEditor->SelAvail ? rbSelection : rbAllText;

        auto Res = LMDEditExecReplaceDialog("Replace text", evEditor, m_SearchOptions);

        if ((Res == srFound) && (m_SearchOptions.WasReplaceAllChosen) && (m_SearchOptions.LastNumberOfReplacements > 0)) {
            TMsgDlgButtons btns;
            btns << mbOK;
            MessageDlg(Format("Ok. Number of replacements: %d", ARRAYOFCONST(( m_SearchOptions.LastNumberOfReplacements ))), mtInformation, btns, -1);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actCopyExecute(TObject *Sender)
{
    if (IsActive()) {
        evEditor->CopySelection();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actPasteExecute(TObject *Sender)
{
    if (IsActive()) {
        evEditor->Paste();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actCutExecute(TObject *Sender)
{
    if (IsActive()) {
        evEditor->CutSelection();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actSearchNextExecute(TObject *Sender)
{
    if (IsActive()) {
        if (evEditor->SearchLastArgs.Search == "" || m_SearchOptions.Direction != sdForward) {
            m_SearchOptions.Direction = sdForward;
            actSearchExecute(Sender);
        } else {
            if (m_SearchOptions.Direction != sdForward) {
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
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actSearchPreviousExecute(TObject *Sender)
{
    if (IsActive()) {
        if (evEditor->SearchLastArgs.Search == "") {
            m_SearchOptions.Direction = sdBackward;
            actSearchExecute(Sender);
        } else {
            if (m_SearchOptions.Direction != sdBackward) {
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
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actFontExecute(TObject *Sender)
{
    FontDialog->Font->Assign(evEditor->Font);
    if (FontDialog->Execute()) {
        evEditor->Font->Assign(FontDialog->Font);
        theAppSettings.CodeEditorFontName = FontDialog->Font->Name;
        theAppSettings.CodeEditorFontHeight = FontDialog->Font->Height;
        Bus::Publish<OnChange<String>>(OnChange<String>("code.editor.font", theAppSettings.CodeEditorFontName + ":" + theAppSettings.CodeEditorFontHeight));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::FontDialogApply(TObject *Sender, HWND Wnd)
{
    evEditor->Font->Assign(FontDialog->Font);
    theAppSettings.CodeEditorFontName = FontDialog->Font->Name;
    theAppSettings.CodeEditorFontHeight = FontDialog->Font->Height;
    Bus::Publish<OnChange<String>>(OnChange<String>("code.editor.font", theAppSettings.CodeEditorFontName + ":" + theAppSettings.CodeEditorFontHeight));
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::actUndoUpdate(TObject *Sender)
{
    UpdateStatus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::UpdateStatus()
{
    // code taken from the LMD demo projects :-(
    int i, NewW, Ph, LinesCount, CharsCount, PhScr;
    TLMDMarkArray Books;
    _di_ILMDMarkers AllBooks;
    Integer AllBooksCount;
    TLMDSpecialCharKinds SpecKinds;

    Books.set_length(0);

    actReplace->Enabled = (evEditor->Document != nullptr) && (! evEditor->Document->ReadOnly);
    actSearch->Enabled = evEditor->Document != nullptr;
    actSearchNext->Enabled = (evEditor->Document==nullptr) ? false : (! evEditor->Document->ReadOnly) || (evEditor->SearchState!=stInReplace);

    actCopy->Enabled = evEditor->CanCopy;
    actCut->Enabled = evEditor->CanCut && (! lmdDocument->ReadOnly);
    actPaste->Enabled = evEditor->CanPaste && (! lmdDocument->ReadOnly);

    actGoToLine->Enabled = evEditor->Document != nullptr;
 
    actFoldAll->Enabled = evEditor->Document != nullptr;
    actFoldAllInCurrent->Enabled = evEditor->Document != nullptr;
    actFoldCurrentTop->Enabled = evEditor->Document != nullptr;
    actFoldTops->Enabled = evEditor->Document != nullptr;
    actFoldTopsInCurrent->Enabled = evEditor->Document != nullptr;

    actUnfoldAll->Enabled = evEditor->Document != nullptr;
    actUnfoldAllInCurrent->Enabled = evEditor->Document != nullptr;
    actUnfoldTops->Enabled = evEditor->Document != nullptr;
    actUnfoldTopsInCurrent->Enabled = evEditor->Document != nullptr;

    actUndo->Enabled = evEditor->CanUndo && (! lmdDocument->ReadOnly);
    actRedo->Enabled = evEditor->CanRedo && (! lmdDocument->ReadOnly);

    auto Line = 0;
    auto Col = 0;

    evEditor->ScrollPosToPhysical(evEditor->CursorPos, Line, Col);

    sbStatus->Panels->Items[0]->Text = Format("Cur: (%d: %d)", ARRAYOFCONST(( Line + 1, Col + 1 )) );

    if (evEditor->Document != nullptr) {
        AllBooks = evEditor->Document->Bookmarks;
        AllBooksCount = AllBooks->Count;
    } else {
        AllBooks = nullptr;
        AllBooksCount = 0;
    }

    if ((evEditor->Document != nullptr) && (evEditor->Document->InsideCompoundEdit))
        return;

    Ph = evEditor->ScrollToPhysical(evEditor->CursorPos.y);
    PhScr = evEditor->PhysicalToScroll(Ph);

    if (evEditor->Document != nullptr) {
        LinesCount = evEditor->Document->LinesCount;
        CharsCount = evEditor->Document->CharsCount;
        Books =  evEditor->Document->Bookmarks->GetMarksByLines(Ph, 1);
    } else {
        LinesCount = 1;
        CharsCount = 0;
        Books.set_length(0);
    }

    auto Line1 = 0;
    auto Col1 = 0;

    evEditor->ScrollPosToPhysical(evEditor->SelectionStart, Line, Col);
    evEditor->ScrollPosToPhysical(evEditor->SelectionEnd, Line1, Col1);

    sbStatus->Panels->Items[1]->Text = Format("Sel: (%d: %d)(%d: %d)", ARRAYOFCONST(( Line + 1, Col + 1, Line1 + 1, Col1 + 1  )) );
    sbStatus->Panels->Items[2]->Text = evEditor->ViewSettings.Contains(vsOverwrite) ? "Overwrite" : "Insert";
    sbStatus->Panels->Items[3]->Text = Format("View: lines=[%d]", ARRAYOFCONST((LinesCount)) );
    sbStatus->Panels->Items[4]->Text = Format("Doc: chars=%d, lines=%d", ARRAYOFCONST(( CharsCount, LinesCount )) );
    sbStatus->Panels->Items[6]->Text = Format("Books: here=%d, all=%d", ARRAYOFCONST(( Books.Length, AllBooksCount )) );

    AnsiString Str;
    Str = lmdDocument->CodePageUsePreamble ? "+" : "";

    sbStatus->Panels->Items[7]->Text = Format("Encoding: %s", ARRAYOFCONST(( lmdDocument->CodePageName+Str )) );
    sbStatus->Canvas->Font = sbStatus->Font;

    for (int i = 0; i<sbStatus->Panels->Count; i++) {
        NewW = sbStatus->Canvas->TextWidth(sbStatus->Panels->Items[i]->Text) + 10;
        sbStatus->Panels->Items[i]->Width = Max(sbStatus->Panels->Items[i]->Width, NewW);
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
    TfrmEditor::OnEvent(event);
    if (evEditor != nullptr && IsActive() && m_ActionMap.count(event.Id) == 1) {
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
void __fastcall TfrmEditorCode::actFormatExecute(TObject *Sender)
{
    if (IsActive()) {
        lmdDocument->BeginCompoundEdit();
        auto indent = 0;
        auto commentColumn = evEditor->WrapRulerWidth;

        String lines;
        for (auto line : lmdDocument->Lines) {
            line = line.Trim();
            auto comment = line.Pos(";");
            auto lc = line.UpperCase();

            if (lc.Pos("ELSE") == 1 || lc.Pos("ENDIF") == 1) {
                indent--;
                if (indent < 0) {
                    line = ";" + line + "; Unbalanced IF/ELSE";
                }
            }
            auto inStr = StringOfChar(' ', std::max(0, indent) * 4);
            auto code = (inStr + line).UpperCase();
            if (comment > 2) {
                code = inStr + line.SubString(1, comment - 1).Trim();
                auto comments = line.SubString(comment, line.Length());
                auto padding = std::max(commentColumn, code.Length()) - code.Length();
                code = code.UpperCase() + StringOfChar(' ', padding) + comments;
            }
            auto cq1 = code.Pos("\"");
            if (cq1 > 1) {
                // copy string from line into code (which is now all upper case)
                auto cq2 = code.SubString(cq1 + 1, code.Length()).Pos("\"");
                if (cq2 > 0) {
                    auto lq1 = line.Pos("\"");
                    auto lq2 = line.SubString(lq1+1, line.Length()).Pos("\"");
                    code = code.SubString(1, cq1-1) + line.SubString(lq1, lq2) + code.SubString(cq1 + cq2, code.Length());
                }
            }
            lines += code + "\r\n";
            if (lc.Pos("IF") == 1 || lc.Pos("ELSE")) {
                indent++;
            }
        }
        lmdDocument->Lines->Text = lines;
        lmdDocument->EndCompoundEdit();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::evEditorKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == vkReturn) {
        auto cp = evEditor->CursorPos;
        auto tl = evEditor->TopLinePhysical;
        actFormatExecute(nullptr);
        evEditor->CursorPos = cp;
        evEditor->TopLinePhysical = tl;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorCode::evEditorNotFound(TObject *Sender, TLMDEditNotFoundAction &Action)
{
    Action = saGoStartEnd;
}
//---------------------------------------------------------------------------


