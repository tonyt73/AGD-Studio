//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Settings.h"
#include "System/make_unique.h"
#include "System/File.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace std;
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
    Load(System::File::Combine(System::Path::Application, "Settings"));
}
//---------------------------------------------------------------------------
__fastcall Settings::~Settings()
{
    Save();
}
//---------------------------------------------------------------------------
void __fastcall Settings::Set(const String& property, const String& value)
{
         if (property == ".Application.Style")    ActiveStyle = value;
}
//---------------------------------------------------------------------------
void __fastcall Settings::Set(const String& property, const int& value)
{
         if (property == ".Welcome.Position.X")     WelcomePosition.X = value;
    else if (property == ".Welcome.Position.Y")     WelcomePosition.Y = value;
    else if (property == ".MainWindow.Position.X")  WindowPosition.X = value;
    else if (property == ".MainWindow.Position.Y")  WindowPosition.Y = value;
    else if (property == ".MainWindow.Size.Width")  WindowSize.Width = value;
    else if (property == ".MainWindow.Size.Heioght")WindowSize.Height = value;
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetActiveStyle(const String& style)
{
    m_ActiveStyle = style;
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
void __fastcall Settings::Save()
{
    Open(System::File::Combine(System::Path::Application, "Settings"));
    Push("Application");
        Write("Style", ActiveStyle);
    Pop();
    Push("Welcome");
        Push("Position");
            Write("X", (int)WelcomePosition.X);
            Write("Y", (int)WelcomePosition.Y);
        Pop();
    Pop();
    Push("MainWindow");
        Push("Position");
            Write("X", (int)WindowPosition.X);
            Write("Y", (int)WindowPosition.Y);
        Pop();
        Push("Size");
            Write("Width", (int)WindowSize.Width);
            Write("Height", (int)WindowSize.Height);
        Pop();
        Write("WindowState", (int)WindowState);
    Pop();
    Close();
}
//---------------------------------------------------------------------------
} // namespace Project
//---------------------------------------------------------------------------

