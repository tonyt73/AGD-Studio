//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "FileDefinitions.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
__fastcall FileDefinitions::FileDefinitions()
{
    m_PropertyMap["Files[].Filename"] = &m_DefinitionLoader.Filename;
    m_PropertyMap["Files[].Section"] = &m_DefinitionLoader.Section;
    m_PropertyMap["Files[].Type"] = &m_DefinitionLoader.Type;
    Load();
}
//---------------------------------------------------------------------------
void __fastcall FileDefinitions::Load()
{
    auto file = Services::File::Combine(Services::Folders::Common, "File Definitions.json");
    if (Services::File::Exists(file))
    {
        // yes, load it
        Services::JsonFile::Load(file);
    }
}
//---------------------------------------------------------------------------
void __fastcall FileDefinitions::OnEndObject(const String& object)
{
    if (object == "Files[]")
    {
        m_Definitions.push_back(m_DefinitionLoader);
    }
}
//---------------------------------------------------------------------------
const FileDefinitions::DefinitionList& __fastcall FileDefinitions::GetDefinitions() const
{
    return m_Definitions;
}
//---------------------------------------------------------------------------
