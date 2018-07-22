//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "MapDocuments.h"
#include "Project/DocumentManager.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Entity::Entity()
: m_Pt(0,0)
, m_Document(nullptr)
, m_Dirty(true)
, m_Selected(false)
{
}
//---------------------------------------------------------------------------
__fastcall Entity::Entity(const Entity& other)
: m_Pt(other.m_Pt)
, m_Id(other.m_Id)
, m_Document(other.m_Document)
, m_Dirty(true)
, m_Selected(other.m_Selected)
{
}
//---------------------------------------------------------------------------
__fastcall Entity::~Entity()
{
}
//---------------------------------------------------------------------------
Entity& __fastcall Entity::operator=(const Entity& other)
{
    m_Pt = other.m_Pt;
    m_Id = other.m_Id;
    m_Document = other.m_Document;
    m_Dirty = true;
    m_Selected = other.m_Selected;
    return *this;
}
//---------------------------------------------------------------------------
void __fastcall Entity::SetPoint(const TPoint& pt)
{
    m_Pt = pt;
    m_Dirty = true;
}
//---------------------------------------------------------------------------
TPoint __fastcall Entity::GetPoint() const
{
    if (m_Selected)
    {
        return m_Pt + m_DragPt;
    }
    return m_Pt;
}
//---------------------------------------------------------------------------
void __fastcall Entity::SetDragPoint(const TPoint& pt)
{
    m_DragPt = pt;
    m_Dirty = true;
}
//---------------------------------------------------------------------------
TPoint __fastcall Entity::GetDragPoint() const
{
    if (m_Selected)
    {
        return m_DragPt;
    }
    return TPoint();
}
//---------------------------------------------------------------------------
void __fastcall Entity::Clear()
{
    m_Pt.x = 0;
    m_Pt.y = 0;
    m_Document = nullptr;
    m_Dirty = true;
}
//---------------------------------------------------------------------------
void __fastcall Entity::Clean()
{
    m_Dirty = false;
}
//---------------------------------------------------------------------------
const ImageDocument* __fastcall Entity::GetDocument() const
{
    return m_Document;
}
//---------------------------------------------------------------------------
unsigned int __fastcall Entity::GetId() const
{
    if (m_Document != nullptr)
    {
        return m_Document->Id;
    }
    return InvalidDocumentId;
}
//---------------------------------------------------------------------------
void __fastcall Entity::SetId(unsigned int id)
{
    m_Document = dynamic_cast<ImageDocument*>(theDocumentManager.Get(id));
}
//---------------------------------------------------------------------------
void __fastcall Entity::SetSelected(bool state)
{
    m_Dirty |= m_Selected != state;
    m_Selected = state;
}
//---------------------------------------------------------------------------
void __fastcall Entity::SetDirty(bool state)
{
    m_Dirty = true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
_fastcall TiledMapDocument::TiledMapDocument(const String& name)
: Document(name)
, m_Across(11)
, m_Down(5)
, m_StartLocationX(5)
, m_StartLocationY(2)
, m_Width(32)
, m_Height(24)
, m_BackgroundColor(clBlack)
{
    m_Type = "Map";
    m_SubType = "Tiled";
    m_Folder = "Game\\Map";
    RegisterProperty("RoomsAcross", "Dimensions", "The number in rooms accross for the map");
    RegisterProperty("RoomsDown", "Dimensions", "The number in rooms down for the map");
    RegisterProperty("RoomWidth", "Dimensions", "The width in character blocks for a map room");
    RegisterProperty("RoomHeight", "Dimensions", "The height in character blocks for a map room");
    RegisterProperty("StartLocationX", "Start Room", "The x position of the start room into the map");
    RegisterProperty("StartLocationY", "Start Room", "The y position of the start room into the map");
    RegisterProperty("BackgroundColor", "Visual", "The color of the background when no tile is present");
    // json loading properties
    m_PropertyMap["Map.RoomsAcross"] = &m_Across;
    m_PropertyMap["Map.RoomsDown"] = &m_Down;
    m_PropertyMap["Map.RoomWidth"] = &m_Width;
    m_PropertyMap["Map.RoomHeight"] = &m_Height;
    m_PropertyMap["Map.StartLocationX"] = &StartLocationX;
    m_PropertyMap["Map.StartLocationY"] = &StartLocationY;
    m_PropertyMap["Map.Workspace[].X"] = &m_EntityLoader.m_Pt.x;
    m_PropertyMap["Map.Workspace[].Y"] = &m_EntityLoader.m_Pt.y;
    m_PropertyMap["Map.Workspace[].RefId"] = &m_EntityLoader.m_LoadId;
    m_PropertyMap["Map.ScratchPad[].X"] = &m_EntityLoader.m_Pt.x;
    m_PropertyMap["Map.ScratchPad[].Y"] = &m_EntityLoader.m_Pt.y;
    m_PropertyMap["Map.ScratchPad[].RefId"] = &m_EntityLoader.m_LoadId;
    m_File = GetFile();

    // message subscriptions
    ::Messaging::Bus::Subscribe<OnDocumentChange<String>>(OnDocumentChanged);
}
//---------------------------------------------------------------------------
__fastcall TiledMapDocument::~TiledMapDocument()
{
    ::Messaging::Bus::Unsubscribe<OnDocumentChange<String>>(OnDocumentChanged);
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::DoSave()
{
    Push("Map");
        Write("RoomsAcross", m_Across);
        Write("RoomsDown", m_Down);
        Write("RoomWidth", m_Width);
        Write("RoomHeight", m_Height);
        Write("StartLocationX", m_StartLocationX);
        Write("StartLocationY", m_StartLocationY);
        ArrayStart("Workspace");
        for (const auto& entity : m_Workspace)
        {
            StartObject();
                Write("X", (int)entity.m_Pt.x);
                Write("Y", (int)entity.m_Pt.y);
                Write("RefId", entity.Id);
            EndObject();
        }
        ArrayEnd(); // workspace
        ArrayStart("ScratchPad");
        for (const auto& entity : m_ScratchPad)
        {
            StartObject();
                Write("X", (int)entity.m_Pt.x);
                Write("Y", (int)entity.m_Pt.y);
                Write("RefId", entity.Id);
            EndObject();
        }
        ArrayEnd(); // scratchpad
    Pop();  // map
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::OnEndObject(const String& object)
{
    if (object == "Map.Workspace[]")
    {
        if (m_EntityLoader.m_LoadId != InvalidDocumentId)
        {
            m_EntityLoader.Id = m_EntityLoader.m_LoadId;
            if (m_EntityLoader.Image != nullptr)
            {
                m_Workspace.push_back(m_EntityLoader);
            }
            m_EntityLoader.Clear();
        }
        else
        {
            ::Messaging::Bus::Publish<ErrorMessage>(ErrorMessage("Encountered an invalid map entity while loading workspace JSON object"));
        }
    }
    else if (object == "Map.ScratchPad[]")
    {
        if (m_EntityLoader.m_LoadId != InvalidDocumentId)
        {
            m_EntityLoader.Id = m_EntityLoader.m_LoadId;
            if (m_EntityLoader.Image != nullptr)
            {
                m_ScratchPad.push_back(m_EntityLoader);
            }
            m_EntityLoader.Clear();
        }
        else
        {
            ::Messaging::Bus::Publish<ErrorMessage>(ErrorMessage("Encountered an invalid map entity while loading scratch pad JSON object"));
        }
    }
}
//---------------------------------------------------------------------------
const EntityList& __fastcall TiledMapDocument::Get(MapEntities type) const
{
    if (type == meWorkspace)
    {
        return m_Workspace;
    }
    else if (type == meScratchPad)
    {
        return m_ScratchPad;
    }
    assert(0);
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::Set(MapEntities type, const EntityList& entities)
{
    if (type == meWorkspace)
    {
        m_Workspace.clear();
        m_Workspace = entities;
    }
    else if (type == meScratchPad)
    {
        m_ScratchPad.clear();
        m_ScratchPad = entities;
    }
    else
    {
        assert(0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::OnDocumentChanged(const OnDocumentChange<String>& message)
{
    if (message.document->Type != "Image")
    {
        return;
    }
    if (message.Id == "document.renamed")
    {
        // TODO: find all the references and change them
    }
    else if (message.Id == "document.removed")
    {
        // TODO: find all the references and delete them
    }
}
//---------------------------------------------------------------------------

