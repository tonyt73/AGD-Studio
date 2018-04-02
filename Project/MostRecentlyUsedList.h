//---------------------------------------------------------------------------
#ifndef MostRecentlyUsedListH
#define MostRecentlyUsedListH
//---------------------------------------------------------------------------
#include "System/JsonFile.h"
//---------------------------------------------------------------------------
class MostRecentlyUsedItem
{
public:
    String  Name;
    String  Path;

    MostRecentlyUsedItem(String name, String path)
    : Name(name)
    , Path(path)
    {
    }
};
typedef std::list<MostRecentlyUsedItem> MRUList;
typedef const MRUList& cMRUList;
//---------------------------------------------------------------------------
class MostRecentlyUsedList : public System::JsonFile
{
private:
    MRUList                 m_MostRecentlyUsedList;
    String                  m_MRUName;  // used by the json loader
    String                  m_MRUPath;  // used by the json loader

    void        __fastcall  Save();
    void        __fastcall  Load();
    void        __fastcall  OnEndObject(const String& object);

public:
                __fastcall  MostRecentlyUsedList();
                __fastcall ~MostRecentlyUsedList();

    void        __fastcall  Add(const String& name, const String& path);
    void        __fastcall  Remove(const String& name, const String& path);
    cMRUList    __fastcall  GetList() const;
};
//---------------------------------------------------------------------------
#endif
