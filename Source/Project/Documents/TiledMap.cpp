//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
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
, m_StartRoomIndex(0)
, m_RoomMappingWidth(g_MaxMapRoomsAcross)
, m_RoomMappingHeight(g_MaxMapRoomsDown)
, m_MappingIndexLoadCount(0)
{
    m_Type = "Map";
    m_SubType = "Tiled";
    m_Folder = "Game\\Map";
    if (IsValid(name))
    {
        RegisterProperty("StartLocation", "Start Room", "The coordinates of the start room into the map");
        RegisterProperty("StartScreenIndex", "AGD Screen Index", "The index of the start screen");
        RegisterProperty("StartRoomIndex", "Start Room Details", "The AGD room index of the start location");
        RegisterProperty("StartRoomX", "Start Room Details", "The rooms across to the start room location");
        RegisterProperty("StartRoomY", "Start Room Details", "The rooms down to the start room location");
        RegisterProperty("NumberOfRooms", "Map Details", "The number of rooms defined");
        RegisterProperty("MaxRoomsAcross", "Map Details", "The maximum number of rooms across that you can define");
        RegisterProperty("MaxRoomsDown", "Map Details", "The maximum number of rooms down that you can define");
        RegisterProperty("Width", "Map Details", "Minimum Width of the game map");
        RegisterProperty("Height", "Map Details", "Minimum Height of the AGD file game map");

        // json loading properties
        m_PropertyMap["Map.StartLocation"] = &StartRoomIndex;
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
        m_Registrar.Subscribe<DocumentChange<String>>(OnDocumentChanged);
        m_Registrar.Subscribe<SetStartRoom>(OnSetStartRoom);

        // reset the map
        for (auto y = 0; y < g_MaxMapRoomsDown; y++) {
            for (auto x = 0; x < g_MaxMapRoomsAcross; x++) {
                m_RoomMapping[x][y] = g_EmptyRoom;
            }
        }
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
    Push("RoomMapping");
    Write("Width", m_RoomMappingWidth);
    Write("Height", m_RoomMappingHeight);
    ArrayStart("Indexes");
    for (auto y = 0; y < m_RoomMappingHeight; y++) {
        for (auto x = 0; x < m_RoomMappingWidth; x++) {
            Write(m_RoomMapping[x][y]);
        }
    }
    ArrayEnd(); // indexes
    Pop();
    ArrayStart("Entities");
    for (const auto& entity : m_Map) {
        StartObject();
        Write("X", entity.m_Pt.x);
        Write("Y", entity.m_Pt.y);
        assert(entity.Id < 10000);
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
    ArrayEnd(); // workspace
    ArrayStart("ScratchPad");
    for (const auto& entity : m_ScratchPad) {
        StartObject();
        Write("X", entity.m_Pt.x);
        Write("Y", entity.m_Pt.y);
        Write("RefId", entity.Id);
        if (entity.SpriteType >= 0) {
            Write("SpriteType", entity.SpriteType);
        }
        EndObject();
    }
    ArrayEnd(); // scratchpad
    Pop(); // map
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

        m_RoomMapping[m_MappingIndexLoadCount % m_RoomMappingWidth][m_MappingIndexLoadCount / m_RoomMappingWidth] = m_RoomMappingIndex;
        m_MappingIndexLoadCount++;
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
const MapEntityList& __fastcall TiledMapDocument::Get(MapEntityType type, TSize room)
{
    if (type == meMap) {
        return m_Map;
    } else if (type == meScratchPad) {
        return m_ScratchPad;
    } else if (type == meRoom) {
        m_ActiveRoom = room;
        m_Room.clear();
        // Place the room entities into the room list
        auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
        auto minx = room.cx * tileSize.cx * Window.Width();
        auto miny = room.cy * tileSize.cy * Window.Height();
        auto maxx = minx + (tileSize.cx * Window.Width());
        auto maxy = miny + (tileSize.cy * Window.Height());
        auto ri = GetRoomIndex(TPoint(room.cx, room.cy));
        for (auto& entity : m_Map) {
            auto pt = entity.Pt;
            if ((minx <= pt.x && pt.x < maxx && miny <= pt.y && pt.y < maxy && !entity.RoomLocked) || (entity.RoomLocked && entity.RoomIndex == ri)) {
                auto newEntity = entity;
                // re-position entity to relative to 0,0
                newEntity.Pt = TPoint(entity.Pt.x - minx, entity.Pt.y - miny);
                m_Room.push_back(newEntity);
            }
        }
        return m_Room;
    }
    assert(0);
    m_Room.clear();
    return m_Room;
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::Set(MapEntityType type, const MapEntityList& entities)
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
        m_Room = entities;
        // place the new entities into the room
        auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
        auto minx = m_ActiveRoom.cx * tileSize.cx * Window.Width();
        auto miny = m_ActiveRoom.cy * tileSize.cy * Window.Height();
        auto maxx = minx + (tileSize.cx * Window.Width());
        auto maxy = miny + (tileSize.cy * Window.Height());

        // remove the old room items
        m_Map.erase(std::remove_if(m_Map.begin(), m_Map.end(),
            [&](const MapEntity& entity) { return (minx <= entity.Pt.x && entity.Pt.x < maxx && miny <= entity.Pt.y && entity.Pt.y < maxy); }),
            m_Map.end());

        // add the new room items adjusted for room location
        for (const auto& e : m_Room) {
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
        m_Room.erase(std::remove_if(m_Room.begin(), m_Room.end(), [&](const MapEntity& entity) { return entity.Id == message.Document->Id; }), m_Room.end());
        UpdateEntityRooms();
    }
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::OnSetStartRoom(const SetStartRoom& event)
{
    SetStartRoomCoords(event.Room);
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::SetStartRoomCoords(const TPoint& coords)
{
    auto ri = GetRoomIndex(coords);
    if (ri != g_EmptyRoom) {
        m_StartRoomIndex = ri;
        m_StartRoomCoords = coords;
        Bus::Publish<StartRoomChanged>(coords);
        Bus::Publish<UpdateProperties>(UpdateProperties());
    } else {
        // post an error to the message list
        ErrorMessage("[TiledMap] Cannot set an unused screen as the games Start Location");
    }
}
//---------------------------------------------------------------------------
int __fastcall TiledMapDocument::GetStartRoomCoords(int index) const
{
    return index ? m_StartRoomCoords.Y : m_StartRoomCoords.X;
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
            if (ri != g_EmptyRoom && IsRoomEmpty(x, y)) {
                m_RoomMapping[x][y] = g_EmptyRoom;
            }
        }
    }
    // update entity room indexes
    std::vector<unsigned int> objectsToRemove;
    for (auto entity : m_Map) {
        auto roomPt = TPoint((int)(entity.Pt.X / roomSize.cx), (int)(entity.Pt.Y / roomSize.cy));
        // recalculate the entitys room based on its current position (currently only sprites/objects can be locked to rooms)
        auto object = dynamic_cast<ObjectDocument*>(entity.Image);
        entity.RoomIndex = GetRoomIndex(roomPt, true);
        if (entity.Image->CanBeLocked && !entity.RoomLocked && object) {
            object->RoomIndex = entity.RoomIndex;
            object->State = Visuals::osRoom;
        }
        // update the location of the objects in the room (to screen space)
        if (entity.Image->ImageType == Visuals::itObject) {
            assert(object != nullptr);

            if (object->State == Visuals::osRoom && object->RoomIndex <= g_MaxRooms) {
                object->Position = TPoint(std::max(0, (int)(entity.Pt.X - (roomPt.X * roomSize.cx))), std::min(255, (int)(entity.Pt.Y - (roomPt.Y * roomSize.cy))));
            } else {
                // remove any objects from the map that are not assigned to a room
                objectsToRemove.push_back(entity.Id);
            }
        }
    }
    for (auto id : objectsToRemove) {
        m_Map.erase(std::remove_if(m_Map.begin(), m_Map.end(), [&](const MapEntity& e) { return e.Id == id; }));
    }
    Bus::Publish<UpdateProperties>(UpdateProperties());
}
//---------------------------------------------------------------------------
bool __fastcall TiledMapDocument::IsRoomEmpty(int x, int y)
{
    return (Get(meRoom, TSize(x, y)).size() == 0);
}
//---------------------------------------------------------------------------
bool __fastcall TiledMapDocument::IsRoomIndexUsed(const int roomIndex) const
{
    assert(0 <= roomIndex && roomIndex <= g_MaxRooms);
    bool inUse = false;
    for (auto y = 0; y < g_MaxMapRoomsDown && !inUse; y++) {
        for (auto x = 0; x < g_MaxMapRoomsAcross && !inUse; x++) {
            inUse = m_RoomMapping[x][y] == roomIndex;
        }
    }
    return inUse;
}
//---------------------------------------------------------------------------
const TRect __fastcall TiledMapDocument::SetMinimalMapSize()
{
    UpdateEntityRooms();
    m_ScreenCount = 0;
    TRect rect(g_MaxMapRoomsAcross, g_MaxMapRoomsDown, 0, 0);
    for (auto y = 0; y < g_MaxMapRoomsDown; y++) {
        for (auto x = 0; x < g_MaxMapRoomsAcross; x++) {
            if (m_RoomMapping[x][y] != g_EmptyRoom) {
                rect.Left   = std::min(x, (int)rect.Left  );
                rect.Top    = std::min(y, (int)rect.Top   );
                rect.Right  = std::max(x, (int)rect.Right );
                rect.Bottom = std::max(y, (int)rect.Bottom);
                m_ScreenCount++;
            }
        }
    }
    rect.Inflate(1,0,1,0);
    m_RoomMappingWidth  = rect.Right;
    m_RoomMappingHeight = rect.Bottom;
    return rect;
}
//---------------------------------------------------------------------------
int __fastcall TiledMapDocument::GetRoomIndex(const TPoint& room, bool newIdForUndefinedRoom)
{
    // get either the existing room index or make a new one if required
    auto ri = m_RoomMapping[room.X][room.Y];
    if (ri == g_EmptyRoom && newIdForUndefinedRoom) {
        // find the lowest unused room index
        for (ri = 0; ri <= g_MaxRooms; ri++) {
            // does this ri exist in the list of rooms
            if (!IsRoomIndexUsed(ri)) {
                // no, so assign it to the room
                m_RoomMapping[room.X][room.Y]  = ri;
                break;
            }
        }
        if (ri == g_EmptyRoom) {
            // no rooms left
            ErrorMessage("[TiledMap] There are no rooms available! All 254 rooms are assigned a location.");
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
    for (auto y = 0; y < g_MaxMapRoomsDown; y++)
        for (auto x = 0; x < g_MaxMapRoomsAcross; x++)
            m_RoomMapping[x][y] = g_EmptyRoom;
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
    auto wi = (WindowDocument*)theDocumentManager.Get("Window", "Definition", "Window");
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
            count += m_RoomMapping[x][y] == g_EmptyRoom ? 0 : 1;
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

