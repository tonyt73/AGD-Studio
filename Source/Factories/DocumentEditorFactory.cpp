//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "LMDDckSite.hpp"
//---------------------------------------------------------------------------
#include "DocumentEditorFactory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Factories;
//---------------------------------------------------------------------------
void __fastcall DocumentEditorFactory::Register(const String& documentFolder, CreateDocumentEditorFn pfnCreate)
{
    if (m_Editors.count(documentFolder) == 0)
    {
        m_Editors[documentFolder] = pfnCreate;
    }
    else
    {
        assert(0);
    }
}
//---------------------------------------------------------------------------
TFrame* __fastcall DocumentEditorFactory::Create(Project::Document* document, TComponent* owner)
{
    auto dp = dynamic_cast<TLMDDockPanel*>(owner);
    auto it = m_Editors.find(document->Type + "." + document->SubType);
    if (it == m_Editors.end())
    {
        it = m_Editors.find(document->Type);
    }
    if (it != m_Editors.end() && dp)
    {
        // create an instance of the document editor for the given document type
        auto editor = it->second(document, owner);
        // and attach it to the dock panel
        editor->Parent = dp;
        editor->Align = alClient;
        dp->OnEndDock = editor->OnEndDock;
        return editor;
    }
    return nullptr;
}
//---------------------------------------------------------------------------
