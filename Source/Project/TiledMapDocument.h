//---------------------------------------------------------------------------
#ifndef TiledMapDocumentH
#define TiledMapDocumentH
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Project/MapEntity.h"
#include "Project/ObjectDocument.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
enum MapEntityType { meMap, meRoom, meScratchPad };
const int g_MaxMapRoomsAcross = 16;
const int g_MaxMapRoomsDown   = 16;
//---------------------------------------------------------------------------
class TiledMapDocument : public Document
{
protected:
    MapEntityList                   m_Map;
    MapEntityList                   m_Room;
    MapEntityList                   m_ScratchPad;

    int                             m_StartRoomIndex;
    TPoint                          m_StartRoomCoords;
    int                             m_ScreenCount;
    MapEntity                       m_EntityLoader;
    TSize                           m_ActiveRoom;
    std::vector<int>                m_RoomMapping; // a mapping from Studio to .AGD screen indexes
    int                             m_RoomMappingWidth;
    int                             m_RoomMappingHeight;
    int                             m_RoomMappingIndex;

    void                __fastcall  OnEndObject(const String& object);
    void                __fastcall  OnDocumentChanged(const DocumentChange<String>& message);
    void                __fastcall  OnSetStartRoom(const SetStartRoom& event);
    void                __fastcall  DoSave();
    void                __fastcall  UpdateEntityRooms();
    void                __fastcall  UpdateScreenCoords();
    void                __fastcall  OnLoading();
    void                __fastcall  OnLoaded();
    int                 __fastcall  GetStartRoomCoords(int index) const;
    void                __fastcall  SetStartRoomCoords(const TPoint& coords);
    const TRect&        __fastcall  GetWindow() const;
    int                 __fastcall  GetNumberOfRooms();
    int                 __fastcall  GetMaxRooms(int index);

    __property const TRect&         Window           = { read = GetWindow                       };

public:
                        __fastcall  TiledMapDocument(const String& name);
                        __fastcall ~TiledMapDocument();
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TiledMapDocument(name); };

    MapEntityList       __fastcall  Get(ImageTypes type) const;
   const MapEntityList& __fastcall  Get(MapEntityType type, TSize room = TSize(0,0));
    void                __fastcall  Set(MapEntityType type, const MapEntityList& entities);

    TRect               __fastcall  GetMinimalMapSize();
    int                 __fastcall  GetRoomIndex(const TPoint& room, bool newIdForUndefinedRoom = false);
    bool                __fastcall  IsRoomEmpty(int x, int y);

    int                 __property  ScreenCount     = { read = m_ScreenCount                    };

__published:
    int                 __property  StartRoomIndex  = { read = m_StartRoomIndex                 };
    int                 __property  StartRoomX      = { read = GetStartRoomCoords, index = 0    };
    int                 __property  StartRoomY      = { read = GetStartRoomCoords, index = 1    };
    int                 __property  NumberOfRooms   = { read = GetNumberOfRooms                 };
    int                 __property  MaxRoomsAcross  = { read = GetMaxRooms, index = 0           };
    int                 __property  MaxRoomsDown    = { read = GetMaxRooms, index = 1           };
};
//---------------------------------------------------------------------------
#endif
