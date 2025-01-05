//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "TiledMap.h"
#include "DocumentManager.h"
#include "Window.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
_fastcall TiledMapDocument::TiledMapDocument(const String& name)
: Document(name)
, m_DisabledRoomIndex(g_RoomIndexDisabled)
, m_StartRoomIndex(0)
, m_MappingIndexLoadCount(0)
, m_RoomMappingWidth(g_MaxMapRoomsAcross)
, m_RoomMappingHeight(g_MaxMapRoomsDown)
, m_RoomDisabled(1,0)
, m_RoomInventory(0,0)
{
    m_Type = "Map";
    m_SubType = "Tiled";
    m_Folder = "Game\\Map";
    if (IsValid(name)) {
        //RegisterProperty("StartLocation", "Start Room", "The coordinates of the player Start room in the map");
        RegisterProperty("StartRoomIndex", "Start Room Details", "The AGD room index of the Start location");
        RegisterProperty("StartRoomX", "Start Room Details", "The rooms across to the Start room location");
        RegisterProperty("StartRoomY", "Start Room Details", "The rooms down to the Start room location");
        RegisterProperty("DisabledRoomIndex", "Disabled Room Details", "The AGD room index of the Disabled room location");
        RegisterProperty("DisabledRoomX", "Disabled Room Details", "The rooms across to the Disabled room location");
        RegisterProperty("DisabledRoomY", "Disabled Room Details", "The rooms down to the Disabled room location");
        RegisterProperty("InventoryRoomX", "Disabled Room Details", "The rooms across to the Disabled room location");
        RegisterProperty("InventoryRoomY", "Disabled Room Details", "The rooms down to the Disabled room location");
        RegisterProperty("NumberOfRooms", "Map Details", "The number of rooms/screens defined");
        RegisterProperty("MaxRoomsAcross", "Map Details", "The maximum number of rooms across that you can define");
        RegisterProperty("MaxRoomsDown", "Map Details", "The maximum number of rooms down that you can define");
        RegisterProperty("Width", "Map Details", "Minimum Width of the game map");
        RegisterProperty("Height", "Map Details", "Minimum Height of the AGD file game map");

        // json loading properties
        m_PropertyMap["Map.StartLocation"] = &StartRoomIndex;
        m_PropertyMap["Map.Inventory.X"] = &m_RoomInventory.X;
        m_PropertyMap["Map.Inventory.Y"] = &m_RoomInventory.Y;
        m_PropertyMap["Map.Entities[].X"] = &m_EntityLoader.m_Pt.x;
        m_PropertyMap["Map.Entities[].Y"] = &m_EntityLoader.m_Pt.y;
        m_PropertyMap["Map.Entities[].RefId"] = &m_EntityLoader.m_LoadId;
        m_PropertyMap["Map.Entities[].SpriteType"] = &m_EntityLoader.m_SpriteType;
        m_PropertyMap["Map.Entities[].Room.Locked"] = &m_EntityLoader.m_RoomLocked;
        m_PropertyMap["Map.Entities[].Room.Index"] = &m_EntityLoader.m_RoomIndex;
        m_PropertyMap["Map.ScratchPad[].X"] = &m_EntityLoader.m_Pt.x;
        m_PropertyMap["Map.ScratchPad[].Y"] = &m_EntityLoader.m_Pt.y;
        m_PropertyMap["Map.ScratchPad[].RefId"] = &m_EntityLoader.m_LoadId;
        m_PropertyMap["Map.ScratchPad[].SpriteType"] = &m_EntityLoader.m_SpriteType;
        m_PropertyMap["Map.RoomMapping.Width"] = &m_RoomMappingWidth;               // the size of the map we are loading
        m_PropertyMap["Map.RoomMapping.Height"] = &m_RoomMappingHeight;
        m_PropertyMap["Map.RoomMapping.Indexes[]"] = &m_RoomMappingIndex;
        m_File = GetFile();

        // message subscriptions
        m_Registrar.Subscribe<DocumentChange<String>>(_FnBind(TiledMapDocument::OnDocumentChanged));
        m_Registrar.Subscribe<SetSpecialRoom>(_FnBind(TiledMapDocument::OnSetSpecialRoom));

        // reset the map
        for (auto y = 0; y < g_MaxMapRoomsDown; y++) {
            for (auto x = 0; x < g_MaxMapRoomsAcross; x++) {
                m_RoomMapping[x][y] = g_RoomIndexEmpty;
            }
        }
        // set the disabled room index
        m_RoomMapping[m_RoomDisabled.X][m_RoomDisabled.Y] = g_RoomIndexDisabled;
        // set the inventory room index
        m_RoomMapping[m_RoomInventory.X][m_RoomInventory.Y] = g_RoomIndexInventory;
    }
}
//---------------------------------------------------------------------------
__fastcall TiledMapDocument::~TiledMapDocument()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::DoSave()
{
    Push("Map");
        Write("StartLocation", StartRoomIndex);
//        Push("Inventory");
//            Write("X", m_RoomInventory.X);
//            Write("Y", m_RoomInventory.Y);
//        Pop();
        Push("RoomMapping");
            Write("Width", m_RoomMappingWidth);
            Write("Height", m_RoomMappingHeight);
            ArrayStart("Indexes");
            for (auto y = 0; y < m_RoomMappingHeight; y++) {
                for (auto x = 0; x < m_RoomMappingWidth; x++) {
                    Write(m_RoomMapping[x][y]);
                }
            }
            ArrayEnd(); // Indexes
        Pop(); // RoomMapping
        ArrayStart("Entities");
        for (const auto& entity : m_Map) {
            StartObject();
            Write("X", entity.m_Pt.x);
            Write("Y", entity.m_Pt.y);
            Write("RefId", entity.Id);
            if (entity.IsSprite && entity.SpriteType >= 0) {
                Write("SpriteType", entity.SpriteType);
                Push("Room");
                Write("Locked", entity.RoomLocked);
                Write("Index", entity.RoomIndex);
                Pop();
            }
            EndObject();
        }
        ArrayEnd(); // Entities
        ArrayStart("ScratchPad");
        for (const auto& entity : m_ScratchPad) {
            StartObject();
            Write("X", entity.m_Pt.x);
            Write("Y", entity.m_Pt.y);
            Write("RefId", entity.Id);
            EndObject();
        }
        ArrayEnd(); // ScratchPad
    Pop(); // Map
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::OnEndObject(const String& object)
{
    if (object == "Map.Entities[]") {
        if (m_EntityLoader.m_LoadId != InvalidDocumentId) {
            // load the entities document
            m_EntityLoader.Id = m_EntityLoader.m_LoadId;
            if (m_EntityLoader.Image != nullptr) {
                m_Map.push_back(m_EntityLoader);
            } else {
                ErrorMessage("[TiledMap] The Workspace editor failed to load the required image for a map entity.");
            }
            m_EntityLoader.Clear();
        } else {
            ErrorMessage("[TiledMap] Encountered an invalid map entity while loading workspace JSON object");
        }
    } else if (object == "Map.ScratchPad[]") {
        if (m_EntityLoader.m_LoadId != InvalidDocumentId) {
            m_EntityLoader.Id = m_EntityLoader.m_LoadId;
            if (m_EntityLoader.Image != nullptr) {
                m_ScratchPad.push_back(m_EntityLoader);
            } else {
                ErrorMessage("[TiledMap] The ScatchPad editor failed to load the required image for a map entity.");
            }
            m_EntityLoader.Clear();
        } else {
            ErrorMessage("[TiledMap] Encountered an invalid map entity while loading scratch pad JSON object");
        }
    } else if (object == "Map.RoomMapping.Indexes[]") {
        auto x = m_MappingIndexLoadCount % m_RoomMappingWidth;
        auto y = m_MappingIndexLoadCount / m_RoomMappingWidth;
        m_RoomMapping[x][y] = m_RoomMappingIndex;
        m_MappingIndexLoadCount++;
        if (m_RoomMappingIndex == g_RoomIndexDisabled) {
            m_RoomDisabled.X = x;
            m_RoomDisabled.Y = y;
        }
        if (m_RoomMappingIndex == g_RoomIndexInventory) {
            m_RoomInventory.X = x;
            m_RoomInventory.Y = y;
        }
    }
}
//---------------------------------------------------------------------------
MapEntityList __fastcall TiledMapDocument::Get(Visuals::ImageTypes type) const
{
    MapEntityList list;
    for (const auto& entity : m_Map) {
        if (entity.Image->ImageType == type) {
            list.push_back(entity);
        }
    }
    return list;
}
//---------------------------------------------------------------------------
const MapEntityList& __fastcall TiledMapDocument::GetEntities(MapEntityType type, TPoint room) const
{
    if (type == meMap) {
        return m_Map;
    } else if (type == meScratchPad) {
        return m_ScratchPad;
    } else if (type == meRoom) {
        m_ActiveRoom = room;
        m_RoomEntityList.clear();
        // Place the room entities into the room list
        auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
        auto minx = room.x * tileSize.cx * Window.Width();
        auto miny = room.y * tileSize.cy * Window.Height();
        auto maxx = minx + (tileSize.cx * Window.Width());
        auto maxy = miny + (tileSize.cy * Window.Height());
        auto ri = GetRoomIndex(TPoint(room.x, room.y));
        for (auto& entity : m_Map) {
            auto pt = entity.Pt;
            if ((minx <= pt.x && pt.x < maxx && miny <= pt.y && pt.y < maxy && !entity.RoomLocked) || (entity.RoomLocked && entity.RoomIndex == ri)) {
                auto newEntity = entity;
                // re-position entity to relative to 0,0
                newEntity.Pt = TPoint(entity.Pt.x - minx, entity.Pt.y - miny);
                m_RoomEntityList.push_back(newEntity);
            }
        }
        return m_RoomEntityList;
    }
    assert(0);
    m_RoomEntityList.clear();
    return m_RoomEntityList;
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::SetEntities(MapEntityType type, const MapEntityList& entities)
{
    if (type == meMap) {
        m_Map.clear();
        m_Map = entities;
        UpdateEntityRooms();
        Bus::Publish<Event>(Event("map.updated"));
    } else if (type == meScratchPad) {
        m_ScratchPad.clear();
        m_ScratchPad = entities;
    } else if (type == meRoom) {
        m_RoomEntityList = entities;
        // place the new entities into the room
        auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
        auto minx = m_ActiveRoom.x * tileSize.cx * Window.Width();
        auto miny = m_ActiveRoom.y * tileSize.cy * Window.Height();
        auto maxx = minx + (tileSize.cx * Window.Width());
        auto maxy = miny + (tileSize.cy * Window.Height());

        // remove the old room items
        m_Map.erase(std::remove_if(m_Map.begin(), m_Map.end(),
            [&](const MapEntity& entity) { return (minx <= entity.Pt.x && entity.Pt.x < maxx && miny <= entity.Pt.y && entity.Pt.y < maxy); }),
            m_Map.end());

        // add the new room items adjusted for room location
        for (const auto& e : m_RoomEntityList) {
            auto ne = e;
            ne.Pt = TPoint(e.Pt.x + minx, e.Pt.y + miny);
            m_Map.push_back(ne);
        }
        UpdateEntityRooms();
        Bus::Publish<Event>(Event("map.updated"));
    } else {
        assert(0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::OnDocumentChanged(const DocumentChange<String>& message)
{
    if (message.Document != nullptr && message.Document->Type != "Image") {
        return;
    }
    if (message.Id == "document.renamed" && message.Document != nullptr) {
        // TODO: find all the references and change them
    } else if (message.Id == "document.removing" && message.Document != nullptr) {
        m_Map.erase(std::remove_if(m_Map.begin(), m_Map.end(), [&](const MapEntity& entity) { return entity.Id == message.Document->Id; }), m_Map.end());
        m_ScratchPad.erase(std::remove_if(m_ScratchPad.begin(), m_ScratchPad.end(), [&](const MapEntity& entity) { return entity.Id == message.Document->Id; }), m_ScratchPad.end());
        m_RoomEntityList.erase(std::remove_if(m_RoomEntityList.begin(), m_RoomEntityList.end(), [&](const MapEntity& entity) { return entity.Id == message.Document->Id; }), m_RoomEntityList.end());
        UpdateEntityRooms();
    }
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::OnSetSpecialRoom(const SetSpecialRoom& event)
{
    auto ri = GetRoomIndex(event.Room);
    if (event.Index < g_MaxRooms) {
        m_StartRoomIndex = ri;
        m_StartRoomCoords = event.Room;
        Bus::Publish<SpecialRoomChanged>(SpecialRoomChanged(event.Room, ri));
        Bus::Publish<UpdateProperties>(UpdateProperties());
    } else if (event.Index == g_RoomIndexDisabled) {
        // Set disabled room
        if (ri == g_RoomIndexEmpty) {
            m_RoomMapping[m_RoomDisabled.X][m_RoomDisabled.Y] = g_RoomIndexEmpty;
            m_RoomDisabled = event.Room;
            m_RoomMapping[m_RoomDisabled.X][m_RoomDisabled.Y] = g_RoomIndexDisabled;
            Bus::Publish<SpecialRoomChanged>(SpecialRoomChanged(event.Room, event.Index));
            Bus::Publish<UpdateProperties>(UpdateProperties());
        } else {
            // post an error to the message list
            ErrorMessage("[TiledMap] Cannot set Disabled room location as the room must be empty.");
        }
    } else if (event.Index == g_RoomIndexInventory) {
        // Set inventory room
        if (ri == g_RoomIndexEmpty) {
            m_RoomMapping[m_RoomInventory.X][m_RoomInventory.Y] = g_RoomIndexEmpty;
            m_RoomDisabled = event.Room;
            m_RoomMapping[m_RoomInventory.X][m_RoomInventory.Y] = g_RoomIndexInventory;
            Bus::Publish<SpecialRoomChanged>(SpecialRoomChanged(event.Room, event.Index));
            Bus::Publish<UpdateProperties>(UpdateProperties());
        } else {
            // post an error to the message list
            ErrorMessage("[TiledMap] Cannot set Inventory room location as the room must be empty.");
        }
    } else {
        // post an error to the message list
        ErrorMessage("[TiledMap] Cannot set Start location to room 254 (Disabled) or 255 (Empty) or 256 (Inventory)");
    }
}
//---------------------------------------------------------------------------
int __fastcall TiledMapDocument::GetSpecialRoomCoords(int index) const
{
    switch (index) {
        case 0: return m_StartRoomCoords.X;
        case 1: return m_StartRoomCoords.Y;
        case 2: return m_RoomDisabled.X;
        case 3: return m_RoomDisabled.Y;
    }
    return -1;
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::UpdateEntityRooms()
{
    auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
    auto roomSize = TSize(Window.Width() * tileSize.cx, Window.Height() * tileSize.cy);
    // remove room mappings for empty rooms
    for (auto y = 0; y < g_MaxMapRoomsDown; y++) {
        for (auto x = 0; x < g_MaxMapRoomsAcross; x++) {
            auto ri = m_RoomMapping[x][y];
            if (ri < g_MaxRooms && IsRoomEmpty(x, y)) {
                m_RoomMapping[x][y] = g_RoomIndexEmpty;
            }
        }
    }
    // update object room indexes from entities
    std::vector<unsigned int> objectsToRemove;
    for (auto& entity : m_Map) {
        auto object = dynamic_cast<ObjectDocument*>(entity.Image);
        if (object != nullptr && entity.RoomIndex <= g_RoomIndexDisabled) {
            auto roomPt = TPoint(static_cast<int>(entity.Pt.X / roomSize.cx), static_cast<int>(entity.Pt.Y / roomSize.cy));
            if (entity.RoomIndex < g_MaxRooms) {
                // recalculate the entitys room based on its current position (currently only sprites/objects can be locked to rooms)
                auto ri = GetRoomIndex(roomPt, true);
                if (entity.Image->CanBeLocked && !entity.RoomLocked && object && object->State == Visuals::osRoom && object->RoomIndex != entity.RoomIndex) {
                    object->RoomIndex = entity.RoomIndex;
                }
                // update the location of the objects in the room (to screen space)
                if (object->RoomIndex < g_MaxRooms) {
                    object->Position = TPoint(std::max(0L, entity.Pt.X - (roomPt.X * roomSize.cx)), std::min(roomSize.cy, entity.Pt.Y - (roomPt.Y * roomSize.cy)));
                } else {
                    // remove any objects from the map that are not assigned to a room ( < 0 || >= 255 || state is osInventory)
                    objectsToRemove.push_back(entity.Id);
                }
            }
        }
    }
    for (auto id : objectsToRemove) {
        m_Map.erase(std::remove_if(m_Map.begin(), m_Map.end(), [&](const MapEntity& e) { return e.Id == id; }));
    }
    Bus::Publish<UpdateProperties>(UpdateProperties());
}
//---------------------------------------------------------------------------
bool __fastcall TiledMapDocument::IsRoomEmpty(int x, int y) const
{
    return (GetEntities(meRoom, TPoint(x, y)).size() == 0);
}
//---------------------------------------------------------------------------
bool __fastcall TiledMapDocument::IsRoomIndexUsed(const int roomIndex) const
{
    assert(0 <= roomIndex && roomIndex < g_MaxRooms);
    bool inUse = false;
    for (auto y = 0; y < g_MaxMapRoomsDown && !inUse; y++) {
        for (auto x = 0; x < g_MaxMapRoomsAcross && !inUse; x++) {
            inUse = m_RoomMapping[x][y] == roomIndex;
        }
    }
    return inUse;
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::SetRoomMapping(const std::map<int, TPoint>& roomIndexToMap)
{
    for (auto map : roomIndexToMap) {
        m_RoomMapping[map.second.X][map.second.Y] = map.first;
    }
}
//---------------------------------------------------------------------------
const TRect __fastcall TiledMapDocument::SetMinimalMapSize()
{
    UpdateEntityRooms();
    m_ScreenCount = 0;
    TRect rect(g_MaxMapRoomsAcross, g_MaxMapRoomsDown, 0, 0);
    for (LONG y = 0; y < g_MaxMapRoomsDown; y++) {
        for (LONG x = 0; x < g_MaxMapRoomsAcross; x++) {
            if (m_RoomMapping[x][y] < g_MaxRooms) {
                rect.Left   = std::min(x, rect.Left  );
                rect.Top    = std::min(y, rect.Top   );
                rect.Right  = std::max(x, rect.Right );
                rect.Bottom = std::max(y, rect.Bottom);
                m_ScreenCount++;
            }
        }
    }
    rect.Inflate(1,0,1,0);
    m_RoomMappingWidth  = g_MaxMapRoomsAcross;  //rect.Right;
    m_RoomMappingHeight = g_MaxMapRoomsDown;    //rect.Bottom;
    return rect;
}
//---------------------------------------------------------------------------
int __fastcall TiledMapDocument::GetRoomIndex(const TPoint& room, bool newIdForUndefinedRoom) const
{
    // get either the existing room index or make a new one if required
    auto ri = m_RoomMapping[room.X][room.Y];
    if (ri == g_RoomIndexEmpty && newIdForUndefinedRoom) {
        // find the lowest unused room index
        for (ri = 0; ri < g_MaxRooms; ri++) {
            // does this ri exist in the list of rooms
            if (!IsRoomIndexUsed(ri)) {
                if (ri == 28) {
                    int a = 0;
                }
                // no, so assign it to the room
                m_RoomMapping[room.X][room.Y] = ri;
                break;
            }
        }
        if (ri >= g_MaxRooms) {
            // no rooms left
            ErrorMessage("[TiledMap] There are no rooms available! All 253 rooms are assigned a location.");
        }
    }
    return ri;
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::UpdateScreenCoords()
{
    for (auto y = 0; y < g_MaxMapRoomsDown; y++) {
        for (auto x = 0; x < g_MaxMapRoomsAcross; x++) {
            const auto& coords = TPoint(x, y);
            auto ri = GetRoomIndex(coords);
            if (ri == m_StartRoomIndex) {
                m_StartRoomCoords = coords;
                return;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::OnLoading()
{
    // reset the map
    for (auto y = 0; y < g_MaxMapRoomsDown; y++) {
        for (auto x = 0; x < g_MaxMapRoomsAcross; x++) {
            m_RoomMapping[x][y] = g_RoomIndexEmpty;
        }
    }
    // set the disabled room index
    m_RoomMapping[m_RoomDisabled.X][m_RoomDisabled.Y] = g_RoomIndexDisabled;
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::OnLoaded()
{
    UpdateScreenCoords();
}
//---------------------------------------------------------------------------
const TRect& __fastcall TiledMapDocument::GetWindow() const
{
    static TRect emptyRect = TRect(0,0,0,0);
    auto wi = dynamic_cast<WindowDocument*>(theDocumentManager.Get("Window", "Definition", "Window"));
    if (wi != nullptr) {
        return wi->Rect;
    }
    return emptyRect;
}
//---------------------------------------------------------------------------
int __fastcall TiledMapDocument::GetNumberOfRooms()
{
    int count = 0;
    for (auto y = 0; y < g_MaxMapRoomsDown; y++) {
        for (auto x = 0; x < g_MaxMapRoomsAcross; x++) {
            count += m_RoomMapping[x][y] < g_MaxRooms ? 1 : 0;
        }
    }
    return count;
}
//---------------------------------------------------------------------------
int __fastcall TiledMapDocument::GetMaxRooms(int index)
{
    return index ? g_MaxMapRoomsDown : g_MaxMapRoomsAcross;
}
//---------------------------------------------------------------------------

