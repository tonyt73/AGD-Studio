//---------------------------------------------------------------------------
#ifndef ImportRoomH
#define ImportRoomH
//---------------------------------------------------------------------------
//#include "ImportWindow.h"
//---------------------------------------------------------------------------
typedef std::vector<unsigned char> ScreenData;
typedef struct {
    unsigned char   Type;
    unsigned char   Index;
    unsigned char   ScreenIndex;
    TPoint          Position;
} SpritePosition;
typedef std::vector<SpritePosition> Sprites;
//---------------------------------------------------------------------------
class ImportRoom
{
private:

public:
    ScreenData          m_Blocks;
    Sprites             m_Sprites;

            __fastcall  ImportRoom(const String& data, unsigned int screenIndex);
};
//---------------------------------------------------------------------------
typedef std::vector<std::unique_ptr<ImportRoom>> ScreenList;
//---------------------------------------------------------------------------
#endif
