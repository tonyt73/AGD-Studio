//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Settings.h"
#include "Services/File.h"
#include "Services/Folders.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
static Settings* instance = nullptr;
Settings& __fastcall Settings::get()
{
    if (instance == nullptr)
    {
        Services::Folders::Init();
        instance = new Settings();
    }
    return *instance;
}
//---------------------------------------------------------------------------
__fastcall Settings::Settings()
: JsonFile()
{
    m_PropertyMap["Application.Style"        ] = &m_ActiveStyle;
    m_PropertyMap["Project.Developer"        ] = &m_Developer;
    m_PropertyMap["Project.DefaultMachine"   ] = &m_DefaultMachine;
    m_PropertyMap["Project.LastLoaded"       ] = &m_LastProject;
    m_PropertyMap["Project.LoadLastOnStartup"] = &m_LoadLastProject;
    m_PropertyMap["Welcome.Position.X"       ] = &m_WelcomePosition.X;
    m_PropertyMap["Welcome.Position.Y"       ] = &m_WelcomePosition.Y;
    m_PropertyMap["Welcome.SkipOnStartup"    ] = &m_WelcomeSkipOnStartup;
    m_PropertyMap["Welcome.SkipOnShutdown"   ] = &m_WelcomeSkipOnClose;
    m_PropertyMap["MainWindow.Position.X"    ] = &m_WindowPosition.X;
    m_PropertyMap["MainWindow.Position.Y"    ] = &m_WindowPosition.Y;
    m_PropertyMap["MainWindow.Size.Width"    ] = &m_WindowSize.Width;
    m_PropertyMap["MainWindow.Size.Height"   ] = &m_WindowSize.Height;

    Load(Services::File::Combine(Services::Folders::Common, "Settings.json"));
}
//---------------------------------------------------------------------------
__fastcall Settings::~Settings()
{
    Save();
}
//---------------------------------------------------------------------------
void __fastcall  Settings::SetWelcomePosition(const TPoint& position)
{
    m_WelcomePosition = position;
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetWindowPosition(const TPoint& position)
{
    m_WindowPosition = position;
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetWindowState(const TWindowState& state)
{
    m_WindowState = state;
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetWindowSize(const TSize& size)
{
    m_WindowSize = size;
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetBool(int index, bool value)
{
    switch (index)
    {
        case 0: m_WelcomeSkipOnStartup = value; break;
        case 1: m_WelcomeSkipOnClose = value; break;
        case 2: m_LoadLastProject = value; break;
    }
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetString(int index, String value)
{
    switch (index)
    {
        case 0: m_ActiveStyle = value; break;
        case 1: m_LastProject = value; break;
        case 2: m_Developer = value; break;
        case 3: m_DefaultMachine = value; break;
    }
}
//---------------------------------------------------------------------------
void __fastcall Settings::Save()
{
    // {
    Open(Services::File::Combine(Services::Folders::Common, "Settings.json"));
    Push("Application"); // {
        Write("Style", ActiveStyle);
    Pop(); // }
    Push("Project");    // {
        Write("Developer", m_Developer);
        Write("DefaultMachine", m_DefaultMachine);
        Write("LastLoaded", m_LastProject);
        Write("LoadLastOnStartup", m_LoadLastProject);
    Pop();  // }
    Push("Welcome"); // {
        Push("Position"); // {
            Write("X", WelcomePosition.X);
            Write("Y", WelcomePosition.Y);
        Pop(); // }
        Write("SkipOnStartup", m_WelcomeSkipOnStartup);
        Write("SkipOnShutdown", m_WelcomeSkipOnClose);
    Pop(); // }
    Push("MainWindow"); // {
        Push("Position"); // {
            Write("X", WindowPosition.X);
            Write("Y", WindowPosition.Y);
        Pop(); // {
        Push("Size"); // {
            Write("Width", WindowSize.Width);
            Write("Height", WindowSize.Height);
        Pop(); // }
        Write("WindowState", (int)WindowState);
    Pop(); // }
    // }
    Close();
}
//---------------------------------------------------------------------------

