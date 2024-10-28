//---------------------------------------------------------------------------
#ifndef MostRecentlyUsedListH
#define MostRecentlyUsedListH
//---------------------------------------------------------------------------
#include "Services/JsonFile.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class MostRecentlyUsedItem
{
public:
    String      Name;
    String      Path;
    String      Machine;

    MostRecentlyUsedItem()
    {
    }

    MostRecentlyUsedItem(String name, String path, String machine)
    : Name(name)
    , Path(path)
    , Machine(machine)
    {
    }
};
typedef std::list<MostRecentlyUsedItem> MRUList;
typedef const MRUList& cMRUList;
//---------------------------------------------------------------------------
class MostRecentlyUsedList : public Services::JsonFile
{
private:
    MRUList                 m_MostRecentlyUsedList;
    MostRecentlyUsedItem    m_Loader;
    bool                    m_Loading;

    void        __fastcall  Save();
    void        __fastcall  Load();
    void        __fastcall  OnEndObject(const String& object);

public:
                __fastcall  MostRecentlyUsedList();
                __fastcall ~MostRecentlyUsedList();

    void        __fastcall  Add(const String& name, const String& path, const String& machine, bool addToFront = true);
    void        __fastcall  Remove(const String& name, const String& path);
    cMRUList    __fastcall  GetList() const;
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
