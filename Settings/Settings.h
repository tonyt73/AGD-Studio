//---------------------------------------------------------------------------
#ifndef SettingsH
#define SettingsH
//---------------------------------------------------------------------------
#include "System/JsonFile.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class Settings : System::JsonFile
{
public:
    static Settings& __fastcall get();
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

private:
    TWindowState                m_WindowState;
    String                      m_ActiveStyle;
    TPoint                      m_WindowPosition;
    TSize                       m_WindowSize;
    TPoint                      m_WelcomePosition;

    void            __fastcall  Set(const String& property, const String& value);
    void            __fastcall  Set(const String& property, const int& value);

    void            __fastcall  SetActiveStyle(const String& style);
    void            __fastcall  SetWelcomePosition(const TPoint& position);
    void            __fastcall  SetWindowPosition(const TPoint& position);
    void            __fastcall  SetWindowState(const TWindowState& state);
    void            __fastcall  SetWindowSize(const TSize& size);

    void            __fastcall  Save();

public:
                    __fastcall  Settings();
                    __fastcall ~Settings();

    TWindowState    __property  WindowState     = { read = m_WindowState    , write = SetWindowState     };
    String           __property ActiveStyle     = { read = m_ActiveStyle    , write = SetActiveStyle     };
    TPoint          __property  WindowPosition  = { read = m_WindowPosition , write = SetWindowPosition  };
    TSize           __property  WindowSize      = { read = m_WindowSize     , write = SetWindowSize      };
    TPoint          __property  WelcomePosition = { read = m_WelcomePosition, write = SetWelcomePosition };
};
//---------------------------------------------------------------------------
} // namespace Project
//---------------------------------------------------------------------------
#define appSettings Project::Settings::get()
//---------------------------------------------------------------------------
#endif
