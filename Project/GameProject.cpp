//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "GameProject.h"
#include "Messaging/Messaging.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
__fastcall GameProject::GameProject()
: System::JsonFile()
, m_Name("")
, m_Version("0.1")
, m_Author("Anonymous")
, m_Machine("")
{
	Init();
}
//---------------------------------------------------------------------------
__fastcall GameProject::GameProject(const String& name, const String& machine)
: System::JsonFile()
, m_Name(name)
, m_Version("0.1")
, m_Author("Anonymous")
, m_Machine(machine)
{
	Init();
}
//---------------------------------------------------------------------------
__fastcall GameProject::~GameProject()
{
}
//---------------------------------------------------------------------------
void __fastcall GameProject::Init()
{
	m_PropertyMap[".Game.Name"] = &m_Name;
	m_PropertyMap[".Game.Version"] = &m_Version;
	m_PropertyMap[".Game.Author"] = &m_Author;
	m_PropertyMap[".Game.Description"] = &m_Description;
	m_PropertyMap[".Game.Machine"] = &m_Machine;
	m_PropertyMap[".Game.Screen.X"] = &m_ScreenPosition.X;
	m_PropertyMap[".Game.Screen.Y"] = &m_ScreenPosition.Y;
	m_PropertyMap[".Game.Screen.Width"] = &m_ScreenSize.Width;
	m_PropertyMap[".Game.Screen.Height"] = &m_ScreenSize.Height;

    ::Messaging::Bus::Subscribe<OnChange<String>>(OnChangeString);
    ::Messaging::Bus::Subscribe<OnChange<int>>(OnChangeInt);
}
//---------------------------------------------------------------------------
void __fastcall GameProject::Save()
{
	auto folder = System::File::Combine(System::Path::Projects, m_Name);
	auto file = System::File::Combine(folder, "project");
	Open(file);
	Push("Game");
    	Write("Name", m_Name);
        Write("Version", m_Version);
        Write("Author", m_Author);
        Write("Description", m_Description);
        Write("Machine", m_Machine);
    	Push("Screen");
            Write("X", (int)m_ScreenPosition.X);
            Write("Y", (int)m_ScreenPosition.Y);
            Write("Width", (int)m_ScreenSize.Width);
            Write("Height", (int)m_ScreenSize.Height);
    	Pop();  // Screen
	Pop();  // Game
	Close();
	// TODO: Save all the game objects (actors.json, tiles.json, sprites.json etc)
//	m_Sounds.Save(folder);
//    m_Sprites.Save(folder);
//    m_Tiles.Save(folder);
//    m_Stages.Save(folder);
	::Messaging::Bus::Publish<OnChange<String>>(OnChange<String>("project.saved", m_Name));
}
//---------------------------------------------------------------------------
bool __fastcall GameProject::Load(const String& file)
{
	// does it exist?
	if (!System::File::Exists(file))
		return false;
	// yes, load it
	JsonFile::Load(file);
	// do we need to load the full game?
	// TODO: Load all the game objects
	bool bAllLoaded = true;
//	bAllLoaded &= m_Sounds.Load(folder);
//	bAllLoaded &= m_Sprites.Load(folder);
//	bAllLoaded &= m_Tiles.Load(folder);
//	bAllLoaded &= m_Stages.Load(folder);
	return bAllLoaded;
}
//---------------------------------------------------------------------------
void __fastcall GameProject::OnChangeString(const OnChange<String>& event)
{
         if (event.Id == "project.version" ) m_Version = event.Value;
    else if (event.Id == "project.author"  ) m_Author = event.Value;
}
//---------------------------------------------------------------------------
void __fastcall GameProject::OnChangeInt(const OnChange<int>& event)
{
}
//---------------------------------------------------------------------------
} // project namespace
//---------------------------------------------------------------------------
