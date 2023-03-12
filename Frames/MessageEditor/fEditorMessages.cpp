//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#include "fEditorMessages.h"
#include "Frames/CodeEditor/fEditorCode.h"
#include "Frames/EditorManager.h"
#include "Project/DocumentManager.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmEditorMessages *frmEditorMessages;
//---------------------------------------------------------------------------
__fastcall TfrmEditorMessages::TfrmEditorMessages(TComponent* Owner)
: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::SetDocument(Document* document)
{
    m_Document = dynamic_cast<MessageDocument*>(document);
    ShowKeysHelp();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditorMessages::IsActive() const
{
    return theEditorManager.IsActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::ShowKeysHelp()
{
    const String help = "It's a text editor ;-)";
    HelpKeysMessage(help);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
    ShowKeysHelp();
    theEditorManager.SetActive(this);
}
//---------------------------------------------------------------------------

