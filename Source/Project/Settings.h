//---------------------------------------------------------------------------
#ifndef SettingsH
#define SettingsH
//---------------------------------------------------------------------------
#include "Messaging/Event.h"
#include "Services/JsonFile.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class Settings : public Services::JsonFile
{
public:
    static Settings& __fastcall get();
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

private:
    TWindowState                m_WindowState;
    TPoint                      m_WindowPosition;
    TSize                       m_WindowSize;
    TPoint                      m_WelcomePosition;
    bool                        m_WelcomeSkipOnStartup;
    bool                        m_WelcomeSkipOnClose;
    bool                        m_LoadLastProject;
    String                      m_ActiveStyle;
    String                      m_LastProject;
    String                      m_Developer;
    String                      m_DefaultMachine;

    void            __fastcall  SetActiveStyle(const String& style);
    void            __fastcall  SetWelcomePosition(const TPoint& position);
    void            __fastcall  SetWindowPosition(const TPoint& position);
    void            __fastcall  SetWindowState(const TWindowState& state);
    void            __fastcall  SetWindowSize(const TSize& size);
    void            __fastcall  SetBool(int index, bool value);
    void            __fastcall  SetString(int index, String value);

    void            __fastcall  Save();

public:
                    __fastcall  Settings();
                    __fastcall ~Settings();

    TWindowState    __property  WindowState             = { read = m_WindowState            , write = SetWindowState        };
    TPoint          __property  WindowPosition          = { read = m_WindowPosition         , write = SetWindowPosition     };
    TSize           __property  WindowSize              = { read = m_WindowSize             , write = SetWindowSize         };
    TPoint          __property  WelcomePosition         = { read = m_WelcomePosition        , write = SetWelcomePosition    };
    bool            __property  WelcomeSkipOnStartup    = { read = m_WelcomeSkipOnStartup   , write = SetBool, index = 0    };
    bool            __property  WelcomeSkipOnClose      = { read = m_WelcomeSkipOnClose     , write = SetBool, index = 1    };
    bool            __property  LoadLastProject         = { read = m_LoadLastProject        , write = SetBool, index = 2    };
    String          __property  ActiveStyle             = { read = m_ActiveStyle            , write = SetString, index = 0  };
    String          __property  LastProject             = { read = m_LastProject            , write = SetString, index = 1  };
    String          __property  Developer               = { read = m_Developer              , write = SetString, index = 2  };
    String          __property  DefaultMachine          = { read = m_DefaultMachine         , write = SetString, index = 3  };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#define appSettings Project::Settings::get()
//---------------------------------------------------------------------------
#endif
