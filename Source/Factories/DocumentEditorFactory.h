//---------------------------------------------------------------------------
#ifndef DocumentEditorFactoryH
#define DocumentEditorFactoryH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
namespace Factories
{
//---------------------------------------------------------------------------
typedef TFrame* (__fastcall *CreateDocumentEditorFn)(Project::Document*, TComponent*);
//---------------------------------------------------------------------------
class DocumentEditorFactory
{
private:
    typedef std::map<String, CreateDocumentEditorFn> EditorMap;
    typedef std::map<String, CreateDocumentEditorFn>::iterator EditorMapIt;
    EditorMap           m_Editors;

public:
    void    __fastcall  Register(const String& documentFolder, CreateDocumentEditorFn pfnCreate);
    TFrame* __fastcall  Create(Project::Document* document, TComponent* owner);
};
//---------------------------------------------------------------------------
} // Factories namespace
//---------------------------------------------------------------------------
#endif
