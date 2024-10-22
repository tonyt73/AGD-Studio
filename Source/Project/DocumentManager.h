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

    void        __fastcall  Register(const String& type, const String& subType, CreateDocumentFn pfnCreate);

public:
                __fastcall  DocumentManager();

    void        __fastcall  Add(Document* document);
    Document*   __fastcall  Add(const String& type, const String& subType, const String& name, const String& extra = "");
    bool        __fastcall  DoesNameExist(const String& name) const;
    String      __fastcall  NextName(const String& type, const String& subType) const;
    String      __fastcall  NextName(const String& name) const;
    bool        __fastcall  Remove(const String& type, const String& name);
    void        __fastcall  DocumentFolders(std::vector<String>& folders) const;
    Document*   __fastcall  Get(const String& type, const String& subType, const String& name) const;
    Document*   __fastcall  Get(unsigned int id) const;
    int         __fastcall  GetAsIndex(unsigned int id) const;
ProjectDocument* __fastcall ProjectConfig() const;

    void        __fastcall  GetAllOfType(const String& type, DocumentList& list) const;
    bool        __fastcall  IsFirstOfType(const Document* document) const;

    void        __fastcall  Clear();
    void        __fastcall  Save();
    void        __fastcall  Load(const String& name);
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#define theDocumentManager Project::DocumentManager::get()
//---------------------------------------------------------------------------
#endif
