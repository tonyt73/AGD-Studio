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

    void         Save();
    void         Load();
    void         OnEndObject(const String& object);

public:
                 MostRecentlyUsedList();
                ~MostRecentlyUsedList();

    void         Add(const String& name, const String& path, const String& machine, bool addToFront = true);
    void         Remove(const String& name, const String& path);
    cMRUList     GetList() const;
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
