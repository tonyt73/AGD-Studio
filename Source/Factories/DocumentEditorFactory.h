//---------------------------------------------------------------------------
#ifndef DocumentEditorFactoryH
#define DocumentEditorFactoryH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
namespace Factories
{
//---------------------------------------------------------------------------
typedef TFrame* (*CreateDocumentEditorFn)(Project::Document*, TComponent*);
//---------------------------------------------------------------------------
class DocumentEditorFactory
{
private:
    typedef std::map<String, CreateDocumentEditorFn> EditorMap;
    typedef std::map<String, CreateDocumentEditorFn>::iterator EditorMapIt;
    EditorMap           m_Editors;

public:
    void     Register(const String& documentFolder, CreateDocumentEditorFn pfnCreate);
    TFrame*  Create(Project::Document* document, TComponent* owner);
};
//---------------------------------------------------------------------------
} // Factories namespace
//---------------------------------------------------------------------------
#endif
