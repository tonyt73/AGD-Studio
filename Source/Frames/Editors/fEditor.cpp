//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fEditor.h"
#include "EditorManager.h"
#include "LMDDckSite.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditor::TfrmEditor(TComponent* Owner, const String& Name)
: TFrame(Owner)
, m_KeysHelp("")
, m_Name(Name)
{
    m_Registrar.Subscribe<Event>(OnEvent);
}
//---------------------------------------------------------------------------
__fastcall TfrmEditor::~TfrmEditor()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditor::SetDocument(Project::Document* document)
{
    m_Document = document;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditor::ShowKeysHelp()
{
    HelpKeysNameMessage(m_KeysHelp, m_Name);
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditor::IsActive() const
{
    return theEditorManager.IsActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditor::OnEvent(const Event& event)
{
    if (IsActive() && event.Id == "editor.help")
    {
        ShowKeysHelp();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditor::FrameEnter(TObject *Sender)
{
    theEditorManager.SetActive(this);
}
//---------------------------------------------------------------------------

