//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "MostRecentlyUsedList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MostRecentlyUsedList::MostRecentlyUsedList()
: JsonFile()
{
    m_PropertyMap[".{}.List.[].{}.Name"] = &m_MRUName;
    m_PropertyMap[".{}.List.[].{}.Path"] = &m_MRUPath;
    Load();
}
//---------------------------------------------------------------------------
__fastcall MostRecentlyUsedList::~MostRecentlyUsedList()
{
    Save();
}
//---------------------------------------------------------------------------
void __fastcall MostRecentlyUsedList::Load()
{
    auto file = System::File::Combine(System::Path::Application, "Mru.json");
    if (System::File::Exists(file))
    {
        // yes, load it
        System::JsonFile::Load(file);
    }
}
//---------------------------------------------------------------------------
void __fastcall MostRecentlyUsedList::Save()
{
    auto file = System::Path::Application + "Mru.json";
    Open(file); // {
    ArrayStart("List"); // [
    for (const auto& mru : m_MostRecentlyUsedList)
    {
        StartObject();  // {
            Write("Name", mru.Name);
            Write("Path", mru.Path);
        EndObject();    // }
    }
    ArrayEnd(); // ] List
    Close(); // }
}
//---------------------------------------------------------------------------
void __fastcall MostRecentlyUsedList::OnEndObject(const String& object)
{
    if (object == ".{}.List.[].{}")
    {
        Add(m_MRUName, m_MRUPath);
    }
}
//---------------------------------------------------------------------------
void __fastcall MostRecentlyUsedList::Add(const String& name, const String& path)
{
    if (m_MostRecentlyUsedList.size() > 7)
    {
        m_MostRecentlyUsedList.pop_front();
    }
    auto relativePath = System::Path::GetFolderRelativeTo(System::Path::lpDocuments, path);
    m_MostRecentlyUsedList.push_back(MostRecentlyUsedItem(name, relativePath));
    Save();
}
//---------------------------------------------------------------------------
void __fastcall MostRecentlyUsedList::Remove(const String& name, const String& path)
{
    auto relativePath = System::Path::GetFolderRelativeTo(System::Path::lpDocuments, path);
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
cMRUList __fastcall MostRecentlyUsedList::GetList() const
{
    return m_MostRecentlyUsedList;
}
//---------------------------------------------------------------------------

