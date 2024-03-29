//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "ElXTree.hpp"
#include "Messaging/Messaging.h"
#include "Project/ProjectDocument.h"
#include "Project/ProjectManager.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ProjectDocument::ProjectDocument(const String& name, const String& machine)
: Document(name)
, m_MachineName(machine)
, m_MachineConfig(nullptr)
, m_Version("0.1")
, m_Description("")
, m_Author("Anonymous")
{
    m_Extension = "agdx";
    m_Type = "Game";
    m_SubType = "Configuration";
    m_Folder = "Game\\Configuration";

    RegisterProperty("Name", "Project Details", "The name of your game");
    RegisterProperty("Author", "Project Details", "Your name");
    RegisterProperty("Version", "Project Details", "The version of your game");
    RegisterProperty("Description", "Project Details", "A description of your game");
    RegisterProperty("Machine", "Machine Details", "The machine target of the game");
    RegisterProperty("GraphicsMode", "Machine Details", "The graphics mode of the target machine");
    RegisterProperty("ScreenWidth", "Machine Details", "The width of the screen in pixels");
    RegisterProperty("ScreenHeight", "Machine Details", "The height of the screen in pixels");

    // json loading properties
    m_PropertyMap["Project.Version"] = &m_Version;
    m_PropertyMap["Project.Author"] = &m_Author;
    m_PropertyMap["Project.Description"] = &m_Description;
    m_PropertyMap["Project.Machine"] = &m_MachineName;
    m_PropertyMap["Files[].Name"] = &m_FileInfo.Name;
    m_PropertyMap["Files[].Type"] = &m_FileInfo.Type;
    m_PropertyMap["Files[].SubType"] = &m_FileInfo.SubType;

    m_Registrar.Subscribe<OnChange<String>>(OnChangeString);

    // load the machine configuration
    m_MachineConfig = std::make_unique<MachineConfig>(machine);
    if (machine != "")
    {
        // Load the machine
        m_MachineConfig->Load(m_MachineName);
    }
}
//---------------------------------------------------------------------------
__fastcall ProjectDocument::~ProjectDocument()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void __fastcall ProjectDocument::OnEndObject(const String& object)
{
    if (object == "Files[]")
    {
        m_Files.push_back(m_FileInfo);
    }
}
//---------------------------------------------------------------------------
const MachineConfig& __fastcall ProjectDocument::MachineConfiguration() const
{
    return *m_MachineConfig;
}
//---------------------------------------------------------------------------
String __fastcall ProjectDocument::GetGraphicsMode() const
{
    return m_MachineConfig->GraphicsMode()->Name;
}
//---------------------------------------------------------------------------
int __fastcall ProjectDocument::GetScreenSize(int index) const
{
    return index ? m_MachineConfig->GraphicsMode()->Height : m_MachineConfig->GraphicsMode()->Width;
}
//---------------------------------------------------------------------------
MachineConfig& __fastcall ProjectDocument::WritableMachineConfiguration() const
{
    return *m_MachineConfig;
}
//---------------------------------------------------------------------------
void __fastcall ProjectDocument::DoSave()
{
    Push("Project");
        Write("Version", m_Version);
        Write("Author", m_Author);
        Write("Description", m_Description);
        Write("Machine", m_MachineConfig->Name);
    Pop();  // Project
    ArrayStart("Files");
    for (const auto& fi : m_Files)
    {
        StartObject();
            Write("Name", fi.Name);
            Write("Type", fi.Type);
            Write("SubType", fi.SubType);
        EndObject();
    }
    ArrayEnd(); // Files
}
//---------------------------------------------------------------------------
bool __fastcall ProjectDocument::Load()
{
    m_File = GetFile();
    auto result = Document::Load();
    // Load the machine
    m_MachineConfig->Load(m_MachineName);
    return result;
}
//---------------------------------------------------------------------------
void __fastcall ProjectDocument::ClearFiles()
{
    m_Files.clear();
}
//---------------------------------------------------------------------------
void __fastcall ProjectDocument::AddFile(const String& file, const String& type, const String& subType)
{
    FileInfo fi { file, type, subType };
    m_Files.push_back(fi);
}
//---------------------------------------------------------------------------
const FileList& __fastcall ProjectDocument::Files() const
{
    return m_Files;
}
//---------------------------------------------------------------------------
void __fastcall ProjectDocument::OnChangeString(const OnChange<String>& event)
{
         if (event.Id == "project.version"      ) m_Version     = event.Value;
    else if (event.Id == "project.author"       ) m_Author      = event.Value;
    else if (event.Id == "project.description"  ) m_Description = event.Value;
         if (event.Id == "project.name"         ) Name          = event.Value;
}
//---------------------------------------------------------------------------
String __fastcall ProjectDocument::GetFile() const
{
    // Documents/{project name}
    auto file = System::File::Combine(System::Path::Projects, System::Path::ProjectName);
    // Documents/{project name}/{project name}
    file = System::File::Combine(file, System::Path::ProjectName);
    // Documents/{project name}/{project name}.agdx
    file = System::File::ChangeExtension(file, m_Extension);
    return file;
}
//---------------------------------------------------------------------------
void __fastcall ProjectDocument::SetName(String name)
{
    if (name.Trim().LowerCase() != m_Name.Trim().LowerCase() && !System::Path::Exists(System::Path::lpProjects, name))
    {
        auto fromName = m_Name.Trim();
        auto toName = name.Trim();
        Document::SetName(toName );
        System::Path::ProjectName = toName ;
        System::Path::Rename(System::Path::lpProjects, fromName, toName);
        if (m_TreeNode)
        {
            auto node = ((TElXTreeItem*)m_TreeNode);
            // TODO: Use messaging to get the UI to update this
            // Rename the root node that has the project name
            node->Parent->Parent->Parent->Text = name;
        }
    }
}
//---------------------------------------------------------------------------
