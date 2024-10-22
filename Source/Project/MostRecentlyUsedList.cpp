//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "MostRecentlyUsedList.h"
#include "Services/File.h"
#include "Services/Folders.h"
#include "Services/JsonFile.h"
#include "Services/Guard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
 MostRecentlyUsedList::MostRecentlyUsedList()
: JsonFile()
{
    m_PropertyMap["List[].Name"] = &m_Loader.Name;
    m_PropertyMap["List[].Path"] = &m_Loader.Path;
    m_PropertyMap["List[].Machine"] = &m_Loader.Machine;
    Load();
}
//---------------------------------------------------------------------------
MostRecentlyUsedList::~MostRecentlyUsedList()
{
    Save();
}
//---------------------------------------------------------------------------
void MostRecentlyUsedList::Load()
{
    auto file = Services::File::Combine(Services::Folders::Common, "Mru.json");
    if (Services::File::Exists(file))
    {
        GUARD(m_Loading);
        Services::JsonFile::Load(file);
    }
}
//---------------------------------------------------------------------------
void MostRecentlyUsedList::Save()
{
    if (m_Loading) return;
    auto file = Services::Folders::Common + "Mru.json";
    Open(file); // {
    ArrayStart("List"); // [
    for (const auto& mru : m_MostRecentlyUsedList)
    {
        StartObject();  // {
            Write("Name", mru.Name);
            Write("Path", mru.Path);
            Write("Machine", mru.Machine);
        EndObject();    // }
    }
    ArrayEnd(); // ] List
    Close(); // }
}
//---------------------------------------------------------------------------
void MostRecentlyUsedList::OnEndObject(const String& object)
{
    if (object == "List[]")
    {
        Add(m_Loader.Name, m_Loader.Path, m_Loader.Machine, false);
    }
}
//---------------------------------------------------------------------------
void MostRecentlyUsedList::Add(const String& name, const String& path, const String& machine, bool addToFront)
{
    if (m_MostRecentlyUsedList.size() > 4)
    {
        m_MostRecentlyUsedList.pop_back();
    }
    auto relativePath = Services::Folders::GetFolderRelativeTo(Services::Folders::lpDocuments, path);
    if (addToFront)
        m_MostRecentlyUsedList.push_front(MostRecentlyUsedItem(name, relativePath, machine));
    else
        m_MostRecentlyUsedList.push_back(MostRecentlyUsedItem(name, relativePath, machine));
    Save();
}
//---------------------------------------------------------------------------
void MostRecentlyUsedList::Remove(const String& name, const String& path)
{
    auto relativePath = Services::Folders::GetFolderRelativeTo(Services::Folders::lpDocuments, path);
    auto pos = relativePath.Pos('&');
    if (pos > 0)
    {
        relativePath = relativePath.SubString(0, pos-1) + relativePath.SubString(pos+1, relativePath.Length() - pos);
    }
    m_MostRecentlyUsedList.erase(std::remove_if(
        m_MostRecentlyUsedList.begin(),
        m_MostRecentlyUsedList.end(),
        [&](const MostRecentlyUsedItem& item) { return (item.Name == name && item.Path == relativePath); }), m_MostRecentlyUsedList.end());
    Save();
}
//---------------------------------------------------------------------------
cMRUList MostRecentlyUsedList::GetList() const
{
    return m_MostRecentlyUsedList;
}
//---------------------------------------------------------------------------

