//---------------------------------------------------------------------------
#ifndef TiledMapH
#define TiledMapH
//---------------------------------------------------------------------------
#include "Document.h"
#include "MapEntity.h"
#include "Object.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
enum MapEntityType { meMap, meRoom, meScratchPad };
const int g_MaxMapRoomsAcross  = 24;
const int g_MaxMapRoomsDown    = 16;
const int g_MaxRooms           = 254;
const int g_RoomIndexDisabled  = 254;
const int g_RoomIndexEmpty     = 255;
const int g_RoomIndexInventory = 256;
//---------------------------------------------------------------------------
class TiledMapDocument : public Document
{
protected:
    MapEntityList                   m_Map;
    mutable MapEntityList           m_RoomEntityList;
    MapEntityList                   m_ScratchPad;
    int                             m_DisabledRoomIndex;
    TPoint                          m_RoomDisabled;
    int                             m_InventoryRoomIndex;
    TPoint                          m_RoomInventory;
    int                             m_StartRoomIndex;
    TPoint                          m_StartRoomCoords;
    int                             m_ScreenCount;
    MapEntity                       m_EntityLoader;
    mutable TPoint                  m_ActiveRoom;
    mutable int                     m_RoomMapping[g_MaxMapRoomsAcross][g_MaxMapRoomsDown];          // a mapping from Studio to .AGD screen indexes
    int                             m_RoomMappingIndex;
    int                             m_MappingIndexLoadCount;
    int                             m_RoomMappingWidth;
    int                             m_RoomMappingHeight;

    void                __fastcall  OnEndObject(const String& object) override;
    void                __fastcall  OnDocumentChanged(const DocumentChange<String>& message);
    void                __fastcall  OnSetSpecialRoom(const SetSpecialRoom& event);
    void                __fastcall  DoSave() override;
    void                __fastcall  UpdateEntityRooms();
    void                __fastcall  UpdateScreenCoords();
    void                __fastcall  OnLoading() override;
    void                __fastcall  OnLoaded() override;
    int                 __fastcall  GetSpecialRoomCoords(int index) const;
    const TRect&        __fastcall  GetWindow() const;
    int                 __fastcall  GetNumberOfRooms();
    int                 __fastcall  GetMaxRooms(int index);

    __property const TRect&         Window           = { read = GetWindow                       };

public:
                        __fastcall  TiledMapDocument(const String& name);
                        __fastcall ~TiledMapDocument() override;
    static  Document*   __fastcall  Create(const String& name, const String&) { return new TiledMapDocument(name); }

    MapEntityList       __fastcall  Get(Visuals::ImageTypes type) const;
   const MapEntityList& __fastcall  GetEntities(MapEntityType type, TPoint room = TPoint(0,0)) const;
    void                __fastcall  SetEntities(MapEntityType type, const MapEntityList& entities);

    void                __fastcall  SetRoomMapping(const std::map<int, TPoint>& roomIndexToMap);
    const TRect         __fastcall  SetMinimalMapSize();
    int                 __fastcall  GetRoomIndex(const TPoint& room, bool newIdForUndefinedRoom = false) const;
    bool                __fastcall  IsRoomEmpty(int x, int y) const;
    bool                __fastcall  IsRoomIndexUsed(const int roomIndex) const;

    int                 __property  ScreenCount         = { read = m_ScreenCount                    };

__published:
    int                 __property  DisabledRoomIndex   = { read = m_DisabledRoomIndex              };
    int                 __property  DisabledRoomX       = { read = GetSpecialRoomCoords, index = 2  };
    int                 __property  DisabledRoomY       = { read = GetSpecialRoomCoords, index = 3  };
    int                 __property  InventoryRoomIndex  = { read = m_InventoryRoomIndex             };
    int                 __property  InventoryRoomX      = { read = GetSpecialRoomCoords, index = 4  };
    int                 __property  InventoryRoomY      = { read = GetSpecialRoomCoords, index = 5  };
    int                 __property  StartRoomIndex      = { read = m_StartRoomIndex                 };
    int                 __property  StartRoomX          = { read = GetSpecialRoomCoords, index = 0  };
    int                 __property  StartRoomY          = { read = GetSpecialRoomCoords, index = 1  };
    int                 __property  NumberOfRooms       = { read = GetNumberOfRooms                 };
    int                 __property  MaxRoomsAcross      = { read = GetMaxRooms, index = 0           };
    int                 __property  MaxRoomsDown        = { read = GetMaxRooms, index = 1           };
    int                 __property  Width               = { read = m_RoomMappingWidth               };
    int                 __property  Height              = { read = m_RoomMappingHeight              };
    TPoint              __property  DisabledRoom        = { read = m_RoomDisabled                   };
    TPoint              __property  InventoryRoom       = { read = m_RoomInventory                  };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
