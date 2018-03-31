//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Messaging/Messaging.h"
#include "Project/ProjectDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ProjectDocument::ProjectDocument()
: Document()
, m_Machine("unknown")
, m_Version("0.1")
, m_Description("")
, m_Author("Anonymous")
{
    m_Name = "unnamed";
    m_Extension = "agdx";
    m_Type = "Game";
    m_SubType = "Configuration";
    m_Folder = "Game\\Configuration";
    RegisterProperty("Name", "Details", "The name of your game");
    RegisterProperty("Author", "Details", "Your name");
    RegisterProperty("Version", "Details", "The version of your game");
    RegisterProperty("Description", "Details", "A description of your game");
    RegisterProperty("Machine", "Details", "The machine target of the game");

    // json loading properties
    m_PropertyMap[".Project.Version"] = &m_Version;
    m_PropertyMap[".Project.Author"] = &m_Author;
    m_PropertyMap[".Project.Description"] = &m_Description;
    m_PropertyMap[".Project.Machine"] = &m_Machine;
    m_PropertyMap[".Files.Array.Object.Name"] = &m_FileInfo.Name;
    m_PropertyMap[".Files.Array.Object.Type"] = &m_FileInfo.Type;
    m_PropertyMap[".Files.Array.Object.SubType"] = &m_FileInfo.SubType;

    ::Messaging::Bus::Subscribe<OnChange<String>>(OnChangeString);
}
//---------------------------------------------------------------------------
__fastcall ProjectDocument::ProjectDocument(const String& name)
: ProjectDocument()
{
    m_Name = name;
}
//---------------------------------------------------------------------------
void __fastcall ProjectDocument::OnEndObject(const String& object)
{
    if (object == ".Files.Array.Object")
    {
        m_Files.push_back(m_FileInfo);
    }
}
//---------------------------------------------------------------------------
void __fastcall ProjectDocument::Save()
{
    // Documents/{project name}
    auto file = System::File::Combine(System::Path::Projects, System::Path::ProjectName);
    // Documents/{project name}/{project name}.agdx
    file = System::File::Combine(file, System::Path::ProjectName + ".agdx");
    file = System::File::ChangeExtension(file, m_Extension);
    m_File = file;
    Open(file);
    Push("Project");
        Write("Version", m_Version);
        Write("Author", m_Author);
        Write("Description", m_Description);
        Write("Machine", m_Machine);
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
    Close();
}
//---------------------------------------------------------------------------
bool __fastcall ProjectDocument::Load()
{
    // Documents/{project name}
    auto file = System::File::Combine(System::Path::Projects, System::Path::ProjectName);
    // Documents/{project name}/{project name}.agdx
    file = System::File::Combine(file, System::Path::ProjectName);
    file = System::File::ChangeExtension(file, m_Extension);
    m_File = file;
    return Document::Load();
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
         if (event.Id == "project.version"      ) m_Version = event.Value;
    else if (event.Id == "project.author"       ) m_Author = event.Value;
    else if (event.Id == "project.description"  ) m_Description = event.Value;
         if (event.Id == "project.name"         )
         {
             Name = event.Value;
         }
}
//---------------------------------------------------------------------------
void __fastcall ProjectDocument::SetName(const String& name)
{
    if (name.Trim().LowerCase() != m_Name.Trim().LowerCase())
    {
        System::Path::Rename(System::Path::lpProjects, m_Name.Trim(), name.Trim());
        m_Name = name.Trim();
    }
}
//---------------------------------------------------------------------------
