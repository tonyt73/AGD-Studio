//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Document.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Document::Document()
: m_Name("Unnamed")
, m_Type("No Type")
, m_SubType("No SubType")
, m_MultiDoc(false)
, m_Folder("Misc\\Files")
, m_TreeNode(nullptr)
, m_DockPanel(nullptr)
{
    m_Type = "Document";
    RegisterProperty("Name", "Object", "The name of the asset/document");
}
//---------------------------------------------------------------------------
void __fastcall Document::RegisterProperty(const String& property, const String& category, const String& info)
{
    m_PropertyInfo[property] = { category, info };
}
//---------------------------------------------------------------------------
const Document::TPropertyInfoMap& __fastcall Document::GetPropertyInfo() const
{
    return m_PropertyInfo;
}
//---------------------------------------------------------------------------
String __fastcall Document::GetPropertyInfo(const String& property) const
{
    auto info = m_PropertyInfo.find(property);
    if (info != m_PropertyInfo.end())
    {
        return info->second.info;
    }
    return "Invalid property";
}
//---------------------------------------------------------------------------
void __fastcall Document::Save()
{
    Push("Document");
        Write("Name", m_Name);
    Pop();  // document
}
//---------------------------------------------------------------------------
bool __fastcall Document::Load(const String& file)
{
    // does it exist?
    if (!System::File::Exists(file))
        return false;
    // yes, load it
    JsonFile::Load(file);
    return true;
}
//---------------------------------------------------------------------------

