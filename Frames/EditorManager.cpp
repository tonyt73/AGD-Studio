//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "EditorManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
EditorManager& EditorManager::get()
{
    static EditorManager instance;
    return instance;
}
//---------------------------------------------------------------------------
__fastcall EditorManager::EditorManager()
: m_ActiveEditor(nullptr)
{
}
//---------------------------------------------------------------------------
void __fastcall EditorManager::SetActive(TFrame* editor)
{
    m_ActiveEditor = editor;
}
//---------------------------------------------------------------------------
bool __fastcall EditorManager::IsActive(const TFrame* editor) const
{
    return m_ActiveEditor == editor;
}
//---------------------------------------------------------------------------
