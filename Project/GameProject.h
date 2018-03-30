//---------------------------------------------------------------------------
#ifndef GameProjectH
#define GameProjectH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <map>
#include "System/JsonFile.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class GameProject : public System::JsonFile
{
private:
    // Game
    String                  m_Name;
    String                  m_Version;
    String                  m_Author;
    String                  m_Description;
    String                  m_Machine;
    TPoint                  m_ScreenPosition;
    TSize                   m_ScreenSize;

    //Actors*               m_Actors;
//    GameStages              m_Stages;
//    GameSounds              m_Sounds;
//    GameSprites             m_Sprites;
//    GameTiles               m_Tiles;

    void        __fastcall  Init();
    void        __fastcall  OnChangeString(const OnChange<String>& event);
    void        __fastcall  OnChangeInt(const OnChange<int>& event);

public:
                __fastcall  GameProject();
                __fastcall  GameProject(const String& name, const String& machine);
                __fastcall ~GameProject();

    void        __fastcall  Save();
    bool        __fastcall  Load(const String& file);

    __property  String             Name = { read = m_Name };
    __property  String          Version = { read = m_Version, write = m_Version };
    __property  String           Author = { read = m_Author, write = m_Author };
    __property  String      Description = { read = m_Description, write = m_Description };
    __property  String          Machine = { read = m_Machine, write = m_Machine };
    __property  TPoint   ScreenPosition = { read = m_ScreenPosition, write = m_ScreenPosition };
    __property  String       ScreenSize = { read = m_ScreenSize, write = m_ScreenSize };

//    __property  GameSounds& Sounds  = { read = m_Sounds };
//    __property  GameSprites& Sprites  = { read = m_Sprites };
//    __property  GameTiles&  Tiles   = { read = m_Tiles };
};
//---------------------------------------------------------------------------
} // project namespace
//---------------------------------------------------------------------------
#endif
