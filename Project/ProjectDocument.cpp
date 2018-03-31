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
}
//---------------------------------------------------------------------------
__fastcall ProjectDocument::ProjectDocument(const String& name, const String& machine)
: Document()
, m_Machine(machine)
, m_Version("0.1")
, m_Description("")
, m_Author("Anonymous")
{
    m_Name = name;
    m_Type = "Game";
    m_SubType = "Configuration";
    m_Folder = "Game\\Configuration";
    RegisterProperty("Name", "Details", "The name of your game");
    RegisterProperty("Author", "Details", "Your name");
    RegisterProperty("Version", "Details", "The version of your game");
    RegisterProperty("Description", "Details", "A description of your game");
    RegisterProperty("Machine", "Details", "The machine target of the game");

    // json loading properties
    m_PropertyMap[".Game.Version"] = &m_Version;
    m_PropertyMap[".Game.Author"] = &m_Author;
    m_PropertyMap[".Game.Description"] = &m_Description;
    m_PropertyMap[".Game.Machine"] = &m_Machine;

    ::Messaging::Bus::Subscribe<OnChange<String>>(OnChangeString);
}
//---------------------------------------------------------------------------
void __fastcall ProjectDocument::Save()
{
    auto folder = System::File::Combine(System::Path::Projects, m_Name);
    auto file = System::File::Combine(folder, "project");
    Open(file);
    Document::Save();
    Push("Project");
        Write("Version", m_Version);
        Write("Author", m_Author);
        Write("Description", m_Description);
        Write("Machine", m_Machine);
    Pop();  // Project
    Close();
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
    m_Name = name;
    // TODO: Rename folder
}
//---------------------------------------------------------------------------
