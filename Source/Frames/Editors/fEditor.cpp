//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fEditor.h"
#include "EditorManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditor::TfrmEditor(TComponent* Owner)
: TFrame(Owner)
, m_KeysHelp("")
{
    OnMouseActivate = FrameMouseActivate;
    m_Registrar.Subscribe<Event>(OnEvent);
}
//---------------------------------------------------------------------------
__fastcall TfrmEditor::~TfrmEditor()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditor::FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
    ShowKeysHelp();
    theEditorManager.SetActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditor::SetDocument(Project::Document* document)
{
    m_Document = document;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditor::ShowKeysHelp()
{
    HelpKeysMessage(m_KeysHelp);
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditor::IsActive() const
{
    return theEditorManager.IsActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditor::OnEvent(const Event& event)
{
    if (IsActive())
    {
        ShowKeysHelp();
    }
}
//---------------------------------------------------------------------------
