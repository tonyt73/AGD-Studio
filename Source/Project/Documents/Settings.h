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
    static Settings&  __fastcall get();
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;

private:
    TPoint                      m_WindowPosition;
    TSize                       m_WindowSize;
    TWindowState                m_WindowState;
    TPoint                      m_WelcomePosition;
    bool                        m_WelcomeSkipOnStartup;
    bool                        m_WelcomeSkipOnClose;
    bool                        m_LoadLastProject;
    String                      m_ActiveStyle;
    String                      m_LastProject;
    String                      m_Developer;
    String                      m_DefaultMachine;
    String                      m_CodeEditorFontName;
    int                         m_CodeEditorFontHeight;

    void            __fastcall  SetActiveStyle(const String& style);
    void            __fastcall  SetWelcomePosition(const TPoint& position);
    void            __fastcall  SetWindowPosition(const TPoint& position);
    void            __fastcall  SetWindowState(const TWindowState& state);
    void            __fastcall  SetWindowSize(const TSize& size);
    void            __fastcall  SetBool(int index, bool value);
    void            __fastcall  SetString(int index, String value);

public:
                    __fastcall  Settings();
                    __fastcall ~Settings();
    void            __fastcall  Save();

    __property  TWindowState    WindowState             = { read = m_WindowState            , write = SetWindowState                };
    __property  TPoint          WindowPosition          = { read = m_WindowPosition         , write = SetWindowPosition             };
    __property  TSize           WindowSize              = { read = m_WindowSize             , write = SetWindowSize                 };
    __property  TPoint          WelcomePosition         = { read = m_WelcomePosition        , write = SetWelcomePosition            };
    __property  bool            WelcomeSkipOnStartup    = { read = m_WelcomeSkipOnStartup   , write = SetBool           , index = 0 };
    __property  bool            WelcomeSkipOnClose      = { read = m_WelcomeSkipOnClose     , write = SetBool           , index = 1 };
    __property  bool            LoadLastProject         = { read = m_LoadLastProject        , write = SetBool           , index = 2 };
    __property  String          ActiveStyle             = { read = m_ActiveStyle            , write = SetString         , index = 0 };
    __property  String          LastProject             = { read = m_LastProject            , write = SetString         , index = 1 };
    __property  String          Developer               = { read = m_Developer              , write = SetString         , index = 2 };
    __property  String          DefaultMachine          = { read = m_DefaultMachine         , write = SetString         , index = 3 };
    __property  String          CodeEditorFontName      = { read = m_CodeEditorFontName     , write = SetString         , index = 4 };
    __property  String          CodeEditorFontHeight    = { read = m_CodeEditorFontHeight   , write = m_CodeEditorFontHeight        };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#define theAppSettings Project::Settings::get()
//---------------------------------------------------------------------------
#endif
