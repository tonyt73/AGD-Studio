//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "TiledMapDocument.h"
#include "DocumentManager.h"
#include "WindowDocument.h"
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
        m_PropertyMap["Map.RoomMapping.Width"] = &m_RoomMappingWidth;
        m_PropertyMap["Map.RoomMapping.Height"] = &m_RoomMappingHeight;
        m_PropertyMap["Map.RoomMapping.Indexes[]"] = &m_RoomMappingIndex;
        m_File = GetFile();

        // message subscriptions
        m_Registrar.Subscribe<DocumentChange<String>>(OnDocumentChanged);
        m_Registrar.Subscribe<SetStartRoom>(OnSetStartRoom);
        for (auto i = 0; i < m_RoomMappingWidth * m_RoomMappingHeight; i++) {
            m_RoomMapping.push_back(255);
        }
    }
}
//---------------------------------------------------------------------------
TiledMapDocument::~TiledMapDocument()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void TiledMapDocument::DoSave()
{
    Push("Map");
    Write("StartLocation", StartRoomIndex);
    Push("RoomMapping");
    Write("Width", m_RoomMappingWidth);
    Write("Height", m_RoomMappingHeight);
    ArrayStart("Indexes");
    for (auto index : m_RoomMapping) {
        Write(index);
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
void TiledMapDocument::OnEndObject(const String& object)
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
        m_RoomMapping.push_back(m_RoomMappingIndex);
    }
}
//---------------------------------------------------------------------------
MapEntityList TiledMapDocument::Get(Visuals::ImageTypes type) const
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
const MapEntityList& TiledMapDocument::Get(MapEntityType type, TSize room)
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
void TiledMapDocument::Set(MapEntityType type, const MapEntityList& entities)
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
void TiledMapDocument::OnDocumentChanged(const DocumentChange<String>& message)
{
    if (message.document != nullptr && message.document->Type != "Image") {
        return;
    }
    if (message.Id == "document.renamed" && message.document != nullptr) {
        // TODO: find all the references and change them
    } else if (message.Id == "document.removing" && message.document != nullptr) {
        m_Map.erase(std::remove_if(m_Map.begin(), m_Map.end(), [&](const MapEntity& entity) { return entity.Id == message.document->Id; }), m_Map.end());
        m_ScratchPad.erase(std::remove_if(m_ScratchPad.begin(), m_ScratchPad.end(), [&](const MapEntity& entity) { return entity.Id == message.document->Id; }), m_ScratchPad.end());
        m_Room.erase(std::remove_if(m_Room.begin(), m_Room.end(), [&](const MapEntity& entity) { return entity.Id == message.document->Id; }), m_Room.end());
        UpdateEntityRooms();
    }
}
//---------------------------------------------------------------------------
void TiledMapDocument::OnSetStartRoom(const SetStartRoom& event)
{
    SetStartRoomCoords(event.Room);
}
//---------------------------------------------------------------------------
void TiledMapDocument::SetStartRoomCoords(const TPoint& coords)
{
    auto ri = GetRoomIndex(coords);
    if (ri != 255) {
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
void TiledMapDocument::UpdateEntityRooms()
{
    auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
    auto roomSize = TSize(Window.Width() * tileSize.cx, Window.Height() * tileSize.cy);
    // remove room mappings for empty rooms
    for (auto y = 0; y < g_MaxMapRoomsDown; y++) {
        for (auto x = 0; x < g_MaxMapRoomsAcross; x++) {
            auto ri = m_RoomMapping[y * g_MaxMapRoomsAcross + x];
            if (ri != 255 && IsRoomEmpty(x, y)) {
                m_RoomMapping[y * g_MaxMapRoomsAcross + x] = 255;
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

            if (object->State == Visuals::osRoom && object->RoomIndex < 254) {
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
bool TiledMapDocument::IsRoomEmpty(int x, int y)
{
    return (Get(meRoom, TSize(x, y)).size() == 0);
}
//---------------------------------------------------------------------------
bool TiledMapDocument::IsRoomIndexUsed(const int roomIndex) const
{
    assert(roomIndex != 255);
    auto maxRooms = m_RoomMappingWidth * m_RoomMappingHeight;
    assert(0 <= roomIndex && roomIndex < maxRooms);
    for (auto i = 0; i < maxRooms; i++) {
        if (m_RoomMapping[i] == roomIndex) {
            return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
TRect TiledMapDocument::GetMinimalMapSize()
{
    m_ScreenCount = 0;
    TRect rect(g_MaxMapRoomsAcross, g_MaxMapRoomsDown, 0, 0);
    for (auto y = 0; y < g_MaxMapRoomsDown; y++) {
        for (auto x = 0; x < g_MaxMapRoomsAcross; x++) {
            auto ri = m_RoomMapping[y * g_MaxMapRoomsAcross + x];
            if (ri != 255) {
                rect.Left   = std::min(x, (int)rect.Left  );
                rect.Right  = std::max(x, (int)rect.Right );
                rect.Top    = std::min(y, (int)rect.Top   );
                rect.Bottom = std::max(y, (int)rect.Bottom);
                m_ScreenCount++;
            }
        }
    }
    rect.Left = std::max((int)(rect.Left - 1), 0);
    rect.Right = std::min((int)(rect.Right + 1), 16);
    return rect;
}
//---------------------------------------------------------------------------
int TiledMapDocument::GetRoomIndex(const TPoint& room, bool newIdForUndefinedRoom)
{
    assert(0 <= room.X && room.X < m_RoomMappingWidth);
    assert(0 <= room.Y && room.Y < m_RoomMappingHeight);
    // get either the existing room index or make a new one if required
    auto ri = m_RoomMapping[room.Y * m_RoomMappingWidth + room.X];
    if (ri == 255 && newIdForUndefinedRoom) {
        // find the lowest unused room index
        auto maxRooms = m_RoomMappingWidth * m_RoomMappingHeight;
        for (auto ri = 0; ri < maxRooms; ri++) {
            // does this ri exist in the list of rooms
            if (!IsRoomIndexUsed(ri)) {
                // no, so assign it to the room
                break;
            }
        }
        if (ri != 255) {
            m_RoomMapping[room.Y * m_RoomMappingWidth + room.X] = ri;
        } else {
            // no rooms left
            // TODO: Show an error dialog
        }
    }
    return ri;
}
//---------------------------------------------------------------------------
void TiledMapDocument::UpdateScreenCoords()
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
void TiledMapDocument::OnLoading()
{
    m_RoomMapping.clear();
}
//---------------------------------------------------------------------------
void TiledMapDocument::OnLoaded()
{
    if (m_RoomMapping.size() != m_RoomMappingWidth * m_RoomMappingHeight) {
        ErrorMessage("[TiledMap] The Room Mapping object in the TileMap.json file has " + IntToStr((int)m_RoomMapping.size()) + " indexes when it should have " + IntToStr(m_RoomMappingWidth * m_RoomMappingHeight));
    }
    GetMinimalMapSize();
    UpdateScreenCoords();
    //UpdateEntityRooms();
}
//---------------------------------------------------------------------------
const TRect& TiledMapDocument::GetWindow() const
{
    auto wi = (WindowDocument*)theDocumentManager.Get("Window", "Definition", "Window");
    if (wi != nullptr) {
        return wi->Rect;
    }
    return TRect();
}
//---------------------------------------------------------------------------
int __fastcall TiledMapDocument::GetNumberOfRooms()
{
    int count = 0;
    for (auto room : m_RoomMapping) {
        count += room == 255 ? 0 : 1;
    }
    return count;
}
//---------------------------------------------------------------------------
int __fastcall TiledMapDocument::GetMaxRooms(int index)
{
    return index ? g_MaxMapRoomsDown : g_MaxMapRoomsAcross;
}
//---------------------------------------------------------------------------

