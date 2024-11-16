//---------------------------------------------------------------------------
#ifndef ImportMapH
#define ImportMapH
//---------------------------------------------------------------------------
//#include "ImportWindow.h"
#include "ImportRoom.h"
//---------------------------------------------------------------------------
//typedef std::vector<unsigned char> MapData;
//---------------------------------------------------------------------------
class ImportMap
{
private:
    int                 m_Width;
    int                 m_Height;
    int                 m_StartScreen;
    TRect               m_Rect;

public:
//    MapData             m_MapData;
    int                 m_MapData[16][16];

            __fastcall  ImportMap(const String& data);

    int     __property  Width       = { read = m_Width       };
    int     __property  Height      = { read = m_Height      };
    int     __property  StartScreen = { read = m_StartScreen };
    TRect   __property  Rect        = { read = m_Rect        };
};
//---------------------------------------------------------------------------
#endif
