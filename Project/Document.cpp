//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "ElXTree.hpp"
#include "LMDDckSite.hpp"
#include "Project/Document.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
unsigned int Document::s_NextRefId = 0;
//---------------------------------------------------------------------------
__fastcall Document::Document(const String& name)
: JsonFile()
, m_Name(System::File::NameWithoutExtension(name))
, m_Type("No Type")
, m_SubType("No SubType")
, m_Extension("json")
, m_ShowFileExtension(false)
, m_ReadOnly(false)
, m_Folder("Misc\\Files")
, m_TreeNode(nullptr)
, m_DockPanel(nullptr)
, m_RefId(InvalidDocumentId)
, m_SaveRefId(false)
{
    m_Type = "Document";
    RegisterProperty("Name", "Details", "The name of the asset/document");
    RegisterProperty("Path", "Details", "The full path of the document");
    RegisterProperty("Name", "Details", "The name of the asset/document");
    RegisterProperty("Classification", "Details", "The classification of the document");
    //m_PropertyMap["Document.Name"] = &m_Name;
    m_PropertyMap["Document.RefId"] = &m_RefId;
    m_File = GetFile();
}
//---------------------------------------------------------------------------
__fastcall Document::~Document()
{
    Close();
}
//----------------------------------------------------------------------------
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
void __fastcall Document::AssignId()
{
    if (m_SaveRefId && m_RefId == InvalidDocumentId)
    {
        m_RefId = ++s_NextRefId;
    }
}
//---------------------------------------------------------------------------
void __fastcall Document::Close()
{
    JsonFile::Close();
    auto panel = static_cast<TLMDDockPanel*>(m_DockPanel);
    if (panel != nullptr)
    {
        panel->Free();
        m_DockPanel = nullptr;
    }
}
//---------------------------------------------------------------------------
void __fastcall Document::SetName(String name)
{
    auto oldName = m_Name;
    auto oldFile = GetFile(m_Name);
    auto newFile = GetFile(name);
    if (System::File::Exists(oldFile) && !System::File::Exists(newFile))
    {
        m_Name = name;
        if (m_TreeNode)
        {
            ((TElXTreeItem*)m_TreeNode)->Text = name;
        }
        auto newFile = GetFile();
        System::File::Rename(oldFile, newFile);
        ::Messaging::Bus::Publish<DocumentChange<String>>(DocumentChange<String>("document.renamed", this, oldName));
    }
    else
    {
        ::Messaging::Bus::Publish<MessageEvent>(ErrorMessageEvent("Failed to rename document from [" + oldFile + "] to [" + newFile + "]"));
    }
    m_File = GetFile();
}
//---------------------------------------------------------------------------
void __fastcall Document::SetShowFileExtension(bool value)
{
    m_ShowFileExtension = value;
    m_Name = System::File::NameWithoutExtension(m_Name) + (!value ? String() : String("." + m_Extension));
}
//---------------------------------------------------------------------------
String __fastcall Document::GetFile(String name)
{
    if (name == "")
    {
        name = m_Name;
    }
    // Projects/{project name}
    auto file = System::File::Combine(System::Path::Projects, System::Path::ProjectName);
    // Projects/{project name}/{document name}
    file = System::File::Combine(file, name);
    // Projects/{project name}/{document name}.{extension)
    file = System::File::ChangeExtension(file, m_Extension);
    return file;
}
//---------------------------------------------------------------------------
void __fastcall Document::Save()
{
    m_File = GetFile();
    Open(m_File);
    if (m_SaveRefId)
    {
        Push("Document");
            Write("RefId", m_RefId);
        Pop();  // document
    }
    DoSave();
    Close();
}
//---------------------------------------------------------------------------
bool __fastcall Document::Load()
{
    m_RefId = InvalidDocumentId;
    if (m_File.Trim() == "")
    {
        m_File = GetFile();
    }
    // does it exist?
    if (System::File::Exists(m_File))
    {
        // yes, load it
        JsonFile::Load(m_File);
        // make sure the next ref id is up to date
        s_NextRefId = max(s_NextRefId, m_RefId);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------

