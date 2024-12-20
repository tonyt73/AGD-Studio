//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "ElXTree.hpp"
#include "LMDDckSite.hpp"
//---------------------------------------------------------------------------
#include "Document.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
unsigned int Document::s_NextRefId = 0;
//---------------------------------------------------------------------------
__fastcall Document::Document(const String& name)
: JsonFile()
, m_Name(Services::File::NameWithoutExtension(name))
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
    m_PropertyMap["Document.RefId"] = &m_RefId;
    m_File = GetFile();
}
//---------------------------------------------------------------------------
__fastcall Document::~Document()
{
    m_Name = Unnamed;
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
    Save();
    if (m_DockPanel != nullptr)
    {
        auto panel = static_cast<TLMDDockPanel*>(m_DockPanel);
        if (panel != nullptr)
        {
            panel->Free();
            m_DockPanel = nullptr;
        }
    }
}
//---------------------------------------------------------------------------
Document* __fastcall Document::Copy(const Document* document)
{
    m_Type = document->m_Type;
    m_SubType = document->m_SubType;
    m_Folder = document->m_Folder;
    m_ShowFileExtension = document->m_ShowFileExtension;
    m_ReadOnly = document->m_ReadOnly;
    return this;
}
//---------------------------------------------------------------------------
void __fastcall Document::SetName(String name)
{
    auto oldName = m_Name;
    auto oldFile = GetFile(m_Name);
    auto newFile = GetFile(name);
    if (Services::File::Exists(oldFile) && !Services::File::Exists(newFile))
    {
        m_Name = name;
        if (m_TreeNode)
        {
            ((TElXTreeItem*)m_TreeNode)->Text = name;
        }
        auto newFile = GetFile();
        Services::File::Rename(oldFile, newFile);
        InformationMessage("[Document] Renamed document from [" + oldFile + "] to [" + newFile + "]");
        Bus::Publish<DocumentChange<String>>(DocumentChange<String>("document.renamed", this, oldName));
    }
    else
    {
        ErrorMessage("[Document] Failed to rename document from [" + oldFile + "] to [" + newFile + "]");
    }
    m_File = GetFile();
}
//---------------------------------------------------------------------------
void __fastcall Document::SetShowFileExtension(bool value)
{
    m_ShowFileExtension = value;
    m_Name = Services::File::NameWithoutExtension(m_Name) + (!value ? String() : String("." + m_Extension));
}
//---------------------------------------------------------------------------
String __fastcall Document::GetFile(String name)
{
    if (name == "")
    {
        name = m_Name;
    }
    // Projects/{project name}
    auto file = Services::File::Combine(Services::Folders::Projects, Services::Folders::ProjectName);
    // Projects/{project name}/{document name}
    file = Services::File::Combine(file, name);
    // Projects/{project name}/{document name}.{extension)
    file = Services::File::ChangeExtension(file, m_Extension);
    return file;
}
//---------------------------------------------------------------------------
bool __fastcall Document::IsValid() const
{
    return IsValid(m_File);
}
//---------------------------------------------------------------------------
bool __fastcall Document::IsValid(const String& name) const
{
    return name.Pos(Unnamed) == 0;
}
//---------------------------------------------------------------------------
void __fastcall Document::Save()
{
    m_File = GetFile();
    if (IsValid()) {
        Open(m_File);
        if (m_SaveRefId)
        {
            Push("Document");
                Write("RefId", m_RefId);
            Pop();  // document
        }
        DoSave();
        JsonFile::Close();
    }
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
    if (Services::File::Exists(m_File))
    {
        // yes, load it
        JsonFile::Load(m_File);
        // make sure the next ref id is up to date
        s_NextRefId = std::max(s_NextRefId, m_RefId);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------

