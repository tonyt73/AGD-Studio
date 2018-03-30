//---------------------------------------------------------------------------
#include "agd.pch.h"
#include "AppSettings.h"
#include "System.IniFiles.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
RSAppSettings& RSAppSettings::get()
{
    static RSAppSettings instance;
    return instance;
}
//---------------------------------------------------------------------------
__fastcall RSAppSettings::RSAppSettings()
: m_WindowState(wsNormal)
, m_ActiveStyle("Carbon")
{
    Load();
}
//---------------------------------------------------------------------------
__fastcall RSAppSettings::~RSAppSettings()
{
    Save();
}
//---------------------------------------------------------------------------
void __fastcall RSAppSettings::Load()
{
	auto ini = std::make_unique<TIniFile>(ChangeFileExt(Application->ExeName, ".ini"));

	m_ActiveStyle = ini->ReadString("UI", "Style", "Carbon");
	m_WindowState = (TWindowState)ini->ReadInteger("UI", "WindowState", (int)wsNormal);

	if (m_WindowState == wsMinimized)
	{
		m_WindowState = wsNormal;
	}

	m_WindowPosition.X = ini->ReadInteger("UI", "WindowLeft", 0);
	m_WindowPosition.Y  = ini->ReadInteger("UI", "WindowTop", 0);
	m_WindowSize.Width  = ini->ReadInteger("UI", "WindowWidth", Screen->Width);
	m_WindowSize.Height = ini->ReadInteger("UI", "WindowHeight", Screen->Height);
	m_WelcomePosition.X = ini->ReadInteger("UI", "WelcomeLeft", 0);
	m_WelcomePosition.Y = ini->ReadInteger("UI", "WelcomeTop", 0);
}
//---------------------------------------------------------------------------
void __fastcall RSAppSettings::Save()
{
    std::unique_ptr<TIniFile>ini(new TIniFile(ChangeFileExt(Application->ExeName, ".ini")));

    ini->WriteString("UI", "Style", m_ActiveStyle);
    ini->WriteInteger("UI", "WindowLeft", m_WindowPosition.X);
    ini->WriteInteger("UI", "WindowTop", m_WindowPosition.Y);
    ini->WriteInteger("UI", "WindowWidth", m_WindowSize.Width);
    ini->WriteInteger("UI", "WindowHeight", m_WindowSize.Height);
    ini->WriteInteger("UI", "WelcomeLeft", m_WelcomePosition.X);
    ini->WriteInteger("UI", "WelcomeTop", m_WelcomePosition.Y);
    if (Application->MainForm)
    {
        ini->WriteInteger("UI", "WindowState", (int)Application->MainForm->WindowState);
    }
}
//---------------------------------------------------------------------------
