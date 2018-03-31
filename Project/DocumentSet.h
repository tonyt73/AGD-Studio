//---------------------------------------------------------------------------
#ifndef DocumentSetH
#define DocumentSetH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
class DocumentSet : public Document
{
private:
            int         __fastcall  GetCount();

protected:
    typedef std::vector<Document*> TDocumentList;
    typedef TDocumentList::iterator  TDocumentListIt;

    TDocumentList                   m_Documents;

    virtual void        __fastcall  Update() {};
    virtual void        __fastcall  OnLoad() {};

public:
                        __fastcall  DocumentSet();
                        __fastcall  DocumentSet(const String& subType);

    static  Document*   __fastcall  Create() { throw "Don't create this class"; }

            void        __fastcall  Clear();
            Document*   __fastcall  Add();
            void        __fastcall  Remove(int index);
            void        __fastcall  Remove(const String& name);
            Document*   __fastcall  Get(int index);
            Document*   __fastcall  Get(const String& name);

    __property          int         Count = { read = GetCount       };
};
//---------------------------------------------------------------------------
#endif
