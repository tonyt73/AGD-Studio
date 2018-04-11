//---------------------------------------------------------------------------
#ifndef DocumentManagerH
#define DocumentManagerH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
class DocumentManager
{
public: // singleton
    static DocumentManager& get();
    DocumentManager(DocumentManager const&) = delete;
    void operator=(DocumentManager const&)   = delete;

private:
    // list of documents grouped by type
    typedef std::map<String, std::vector<Document*>> DocumentMap;
    typedef DocumentMap::iterator  DocumentMapIt;

    DocumentMap                     m_Documents;

    // the document factory
    typedef std::map<String, CreateDocumentFn>  TFactoryMap;
    typedef TFactoryMap::iterator               TFactoryMapIt;
    TFactoryMap                     m_FactoryMap;

            void        __fastcall  Register(const String& type, const String& subType, CreateDocumentFn pfnCreate);
            Document*   __fastcall  Get(const String& type, const String& subType, const String& name);
            void        __fastcall  OnImportString(const OnImport<String>& event);

public:
                        __fastcall  DocumentManager();

            void        __fastcall  Add(Document* document);
            Document*   __fastcall  Add(const String& type, const String& subType, const String& name, const String& extra = "");
            bool        __fastcall  Remove(const String& type, const String& name);
            void        __fastcall  DocumentFolders(std::vector<String>& folders) const;

            void        __fastcall  Clear();
            void        __fastcall  Save();
            void        __fastcall  Load(const String& name);
};
//---------------------------------------------------------------------------
#define theDocumentManager DocumentManager::get()
//---------------------------------------------------------------------------
#endif
