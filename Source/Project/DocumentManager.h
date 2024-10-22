//---------------------------------------------------------------------------
#ifndef DocumentManagerH
#define DocumentManagerH
//---------------------------------------------------------------------------
#include "Document.h"
#include "ProjectDocument.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class DocumentManager
{
public: // singleton
    static DocumentManager& get();
    DocumentManager(DocumentManager const&) = delete;
    void operator=(DocumentManager const&)   = delete;

private:
    // list of documents grouped by type
    typedef std::map<String, DocumentList>      DocumentMap;
    DocumentMap                                 m_Documents;

    // the document factory
    typedef std::map<String, CreateDocumentFn>  TFactoryMap;
    typedef TFactoryMap::iterator               TFactoryMapIt;
    TFactoryMap                                 m_FactoryMap;

    void         Register(const String& type, const String& subType, CreateDocumentFn pfnCreate);

public:
                 DocumentManager();

    void         Add(Document* document);
    Document*    Add(const String& type, const String& subType, const String& name, const String& extra = "");
    bool         DoesNameExist(const String& name) const;
    String       NextName(const String& type, const String& subType) const;
    String       NextName(const String& name) const;
    bool         Remove(const String& type, const String& name);
    void         DocumentFolders(std::vector<String>& folders) const;
    Document*    Get(const String& type, const String& subType, const String& name) const;
    Document*    Get(unsigned int id) const;
    int          GetAsIndex(unsigned int id) const;
ProjectDocument* ProjectConfig() const;

    void         GetAllOfType(const String& type, DocumentList& list) const;
    bool         IsFirstOfType(const Document* document) const;

    void         Clear();
    void         Save();
    void         Load(const String& name);
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#define theDocumentManager Project::DocumentManager::get()
//---------------------------------------------------------------------------
#endif
