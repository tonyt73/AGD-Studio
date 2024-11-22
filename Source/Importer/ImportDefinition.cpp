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
    m_PropertyMap["Window.Strip"] = &m_Sections.Window.Strip;
    m_PropertyMap["Controls.Match"] = &m_Sections.Controls.Pattern;
    m_PropertyMap["Controls.Strip"] = &m_Sections.Controls.Strip;
    m_PropertyMap["JumpTable.Match"] = &m_Sections.JumpTable.Pattern;
    m_PropertyMap["JumpTable.Strip"] = &m_Sections.JumpTable.Strip;
    m_PropertyMap["Objects.Match"] = &m_Sections.Objects.Pattern;
    m_PropertyMap["Objects.Strip"] = &m_Sections.Objects.Strip;
    m_PropertyMap["Sprites.Match"] = &m_Sections.Sprites.Pattern;
    m_PropertyMap["Sprites.Strip"] = &m_Sections.Sprites.Strip;
    m_PropertyMap["Blocks.Match"] = &m_Sections.Blocks.Pattern;
    m_PropertyMap["Blocks.Strip"] = &m_Sections.Blocks.Strip;
    m_PropertyMap["Font.Match"] = &m_Sections.Font.Pattern;
    m_PropertyMap["Font.Strip"] = &m_Sections.Font.Strip;
    m_PropertyMap["Palette.Match"] = &m_Sections.Palette.Pattern;
    m_PropertyMap["Palette.Strip"] = &m_Sections.Palette.Strip;
    m_PropertyMap["Events.Match"] = &m_Sections.Events.Pattern;
    m_PropertyMap["Events.Strip"] = &m_Sections.Events.Strip;
    m_PropertyMap["Messages.Match"] = &m_Sections.Messages.Pattern;
    m_PropertyMap["Messages.Strip"] = &m_Sections.Messages.Strip;
    m_PropertyMap["Screens.Match"] = &m_Sections.Screens.Pattern;
    m_PropertyMap["Screens.Strip"] = &m_Sections.Screens.Strip;
    m_PropertyMap["Map.Match"] = &m_Sections.Map.Pattern;
    m_PropertyMap["Map.Strip"] = &m_Sections.Map.Strip;
}
//---------------------------------------------------------------------------
void __fastcall ImportDefinition::Load(const String& name)
{
    // Load our import definition
    Services::JsonFile::Load(Services::File::Combine(Services::Folders::Application, "Importers" + Services::Folders::Separator + name + ".json"));
}
//---------------------------------------------------------------------------
