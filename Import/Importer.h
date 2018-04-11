//---------------------------------------------------------------------------
#ifndef ImporterH
#define ImporterH
//---------------------------------------------------------------------------
#include <memory>
#include <vector>
#include "Snapshot.h"
//---------------------------------------------------------------------------
class Importer
{
private:
    struct Values
    {
        TPoint          WindowPosition;
        TSize           WindowSize;
        unsigned int    Rooms;
    };

    struct Addresses
    {
        unsigned int    SpriteFrames;
        unsigned int    SpriteData;
        unsigned int    BlockImageData;
        unsigned int    BlockAttrsData;
        unsigned int    BlockPropsData;
        unsigned int    ScreenLayouts;
        unsigned int    EnemyPositions;
        unsigned int    AYSoundFx;
        unsigned int    Messages;
        unsigned int    Objects;
        unsigned int    EventCode;
    };

    static std::vector<String>  m_Keywords;
    static std::vector<String>  m_EventFiles;
    Addresses                   m_AddressOf;
    Values                      m_ValueOf;

    std::unique_ptr<Snapshot>   m_Snapshot;

    void        __fastcall  ImportWindow() const;
    void        __fastcall  ImportMessages() const;
    void        __fastcall  ImportEvents() const;
    void        __fastcall  ImportFont() const;
    void        __fastcall  ImportBlocks() const;
    void        __fastcall  ImportSprites() const;
    void        __fastcall  ImportObjects() const;
    void        __fastcall  ImportScreens() const;
    void        __fastcall  ImportMap() const;

public:
                __fastcall  Importer();

    bool        __fastcall  Convert(const String& file);

};
//---------------------------------------------------------------------------
#endif
