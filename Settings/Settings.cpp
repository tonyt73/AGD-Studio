//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Settings.h"
#include "System/File.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Project
{
static Settings* instance = nullptr;
Settings& __fastcall Settings::get()
{
    if (instance == nullptr)
    {
        instance = new Settings();
    }
    return *instance;
}
//---------------------------------------------------------------------------
__fastcall Settings::Settings()
: JsonFile()
{
    m_PropertyMap[".{}.Application.{}.Style"] = &m_ActiveStyle;
    m_PropertyMap[".{}.Project.{}.Developer"] = &m_Developer;
    m_PropertyMap[".{}.Project.{}.DefaultMachine"] = &m_DefaultMachine;
    m_PropertyMap[".{}.Project.{}.LastLoad"] = &m_LastProject;
    m_PropertyMap[".{}.Project.{}.LoadLastOnStartup"] = &m_LoadLastProject;
    m_PropertyMap[".{}.Welcome.{}.Position.{}.X"] = &m_WelcomePosition.X;
    m_PropertyMap[".{}.Welcome.{}.Position.{}.Y"] = &m_WelcomePosition.Y;
    m_PropertyMap[".{}.Welcome.{}.SkipOnStartup"] = &m_WelcomeSkipOnStartup;
    m_PropertyMap[".{}.Welcome.{}.SkipOnShutdown"] = &m_WelcomeSkipOnClose;
    m_PropertyMap[".{}.MainWindow.{}.Position.{}.X"] = &m_WindowPosition.X;
    m_PropertyMap[".{}.MainWindow.{}.Position.{}.Y"] = &m_WindowPosition.Y;
    m_PropertyMap[".{}.MainWindow.{}.Size.{}.Width"] = &m_WindowSize.Width;
    m_PropertyMap[".{}.MainWindow.{}.Size.{}.Height"] = &m_WindowSize.Height;

    Load(System::File::Combine(System::Path::Application, "Settings.json"));
}
//---------------------------------------------------------------------------
__fastcall Settings::~Settings()
{
    Save();
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetWelcomePosition(const TPoint& position)
{
    m_WelcomePosition = position;
    Save();
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetWindowPosition(const TPoint& position)
{
    m_WindowPosition = position;
    Save();
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetWindowState(const TWindowState& state)
{
    m_WindowState = state;
    Save();
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetWindowSize(const TSize& size)
{
    m_WindowSize = size;
    Save();
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
    Save();
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
    Save();
}
//---------------------------------------------------------------------------
void __fastcall Settings::Save()
{
    // {
    Open(System::File::Combine(System::Path::Application, "Settings.json"));
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
            Write("X", (int)WelcomePosition.X);
            Write("Y", (int)WelcomePosition.Y);
        Pop(); // }
        Write("SkipOnStartup", m_WelcomeSkipOnStartup);
        Write("SkipOnShutdown", m_WelcomeSkipOnClose);
    Pop(); // }
    Push("MainWindow"); // {
        Push("Position"); // {
            Write("X", (int)WindowPosition.X);
            Write("Y", (int)WindowPosition.Y);
        Pop(); // {
        Push("Size"); // {
            Write("Width", (int)WindowSize.Width);
            Write("Height", (int)WindowSize.Height);
        Pop(); // }
        Write("WindowState", (int)WindowState);
    Pop(); // }
    // }
    Close();
}
//---------------------------------------------------------------------------
} // namespace Project
//---------------------------------------------------------------------------

