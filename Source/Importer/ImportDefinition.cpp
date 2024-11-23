//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "ImportDefinition.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Importer;
//---------------------------------------------------------------------------
__fastcall ImportDefinition::ImportDefinition(const String& name)
: JsonFile()
, m_Name(name)
{
    m_PropertyMap["Name"] = &m_Name;
    m_PropertyMap["Format"] = &m_Format;
    m_PropertyMap["Window.Match"] = &m_Sections.Window.Pattern;
    m_PropertyMap["ControlSet.Match"] = &m_Sections.ControlSet.Pattern;
    m_PropertyMap["JumpTable.Match"] = &m_Sections.JumpTable.Pattern;
    m_PropertyMap["Objects.Match"] = &m_Sections.Objects.Pattern;
    m_PropertyMap["Sprites.Match"] = &m_Sections.Sprites.Pattern;
    m_PropertyMap["Blocks.Match"] = &m_Sections.Blocks.Pattern;
    m_PropertyMap["Font.Match"] = &m_Sections.Font.Pattern;
    m_PropertyMap["Palette.Match"] = &m_Sections.Palette.Pattern;
    m_PropertyMap["Events.Match"] = &m_Sections.Events.Pattern;
    m_PropertyMap["MessageList.Match"] = &m_Sections.Messages.Pattern;
    m_PropertyMap["Screens.Match"] = &m_Sections.Screens.Pattern;
    m_PropertyMap["SpritePosition.Match"] = &m_Sections.SpritePosition.Pattern;
    m_PropertyMap["Map.Match"] = &m_Sections.Map.Pattern;
}
//---------------------------------------------------------------------------
bool __fastcall ImportDefinition::Load(const String& name)
{
    // Load our import definition
    auto file = Services::File::Combine(Services::Folders::Application, "Importers" + Services::Folders::Separator + name + ".json");
    if (Services::File::Exists(file)) {
        Services::JsonFile::Load(Services::File::Combine(Services::Folders::Application, "Importers" + Services::Folders::Separator + name + ".json"));
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
