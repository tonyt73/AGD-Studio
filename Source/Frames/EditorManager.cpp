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
EditorManager::EditorManager()
: m_ActiveEditor(nullptr)
{
}
//---------------------------------------------------------------------------
void EditorManager::SetActive(TFrame* editor)
{
    m_ActiveEditor = editor;
}
//---------------------------------------------------------------------------
bool EditorManager::IsActive(const TFrame* editor) const
{
    return m_ActiveEditor == editor;
}
//---------------------------------------------------------------------------
