//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "MapEntity.h"
#include "Project/Documents/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
__fastcall MapEntity::MapEntity()
: m_Pt(0, 0)
, m_Id(InvalidDocumentId)
, m_LoadId(InvalidDocumentId)
, m_Document(nullptr)
, m_ImageType(Visuals::itInvalid)
, m_Dirty(true)
, m_Selected(false)
, m_SpriteType(-1)
, m_RoomLocked(false)
, m_RoomIndex(255)
{
}
//---------------------------------------------------------------------------
__fastcall MapEntity::MapEntity(const MapEntity& other)
    : m_Pt(other.m_Pt)
    , m_Id(other.m_Id)
    , m_LoadId(InvalidDocumentId)
    , m_Document(other.m_Document)
    , m_ImageType(other.m_ImageType)
    , m_Dirty(true)
    , m_Selected(other.m_Selected)
    , m_SpriteType(other.m_SpriteType)
    , m_RoomLocked(other.m_RoomLocked)
    , m_RoomIndex(other.m_RoomIndex)
{
}
//---------------------------------------------------------------------------
__fastcall MapEntity::~MapEntity()
{
}
//---------------------------------------------------------------------------
MapEntity& __fastcall MapEntity::operator=(const MapEntity& other)
{
    assert(m_Id < 10000);
    m_Pt = other.m_Pt;
    m_Id = other.m_Id;
    m_LoadId = InvalidDocumentId;
    m_Document = other.m_Document;
    m_ImageType = other.m_ImageType;
    m_Dirty = true;
    m_Selected = other.m_Selected;
    m_SpriteType = other.m_SpriteType;
    m_RoomLocked = other.m_RoomLocked;
    m_RoomIndex = other.m_RoomIndex;
    return *this;
}
//---------------------------------------------------------------------------
bool __fastcall MapEntity::operator==(const MapEntity& other)
{
    assert(m_Id < 10000);
    return (m_Pt == other.m_Pt && m_Id == other.m_Id);
}
//---------------------------------------------------------------------------
void __fastcall MapEntity::SetPoint(const TPoint& pt)
{
    m_Pt = pt;
    m_Dirty = true;
}
//---------------------------------------------------------------------------
TPoint __fastcall MapEntity::GetPoint() const
{
    return m_Selected ? m_Pt + m_DragPt : m_Pt;
}
//---------------------------------------------------------------------------
void __fastcall MapEntity::SetDragPoint(const TPoint& pt)
{
    m_DragPt = pt;
    m_Dirty = true;
}
//---------------------------------------------------------------------------
TPoint __fastcall MapEntity::GetDragPoint() const
{
    return m_Selected ? m_DragPt : TPoint();
}
//---------------------------------------------------------------------------
void __fastcall MapEntity::Clear()
{
    m_Id = InvalidDocumentId;
    m_Pt.x = 0;
    m_Pt.y = 0;
    m_SpriteType = -1;
    m_RoomLocked = false;
    m_RoomIndex = 255;
    m_Document = nullptr;
    m_Dirty = true;
}
//---------------------------------------------------------------------------
void __fastcall MapEntity::Clean()
{
    m_Dirty = false;
}
//---------------------------------------------------------------------------
ImageDocument* __fastcall MapEntity::GetDocument() const
{
    return m_Document;
}
//---------------------------------------------------------------------------
unsigned int __fastcall MapEntity::GetId() const
{
    assert(m_Id < 10000);
    return m_Id;
}
//---------------------------------------------------------------------------
void __fastcall MapEntity::SetId(unsigned int id)
{
    m_Document = dynamic_cast<ImageDocument*>(theDocumentManager.Get(id));
    m_Id = InvalidDocumentId;
    if (m_Document != nullptr) {
        m_Id = id;
        assert(m_Id < 10000);
        m_ImageType = m_Document->ImageType;
        if (m_Document->ImageType == Visuals::itSprite && m_SpriteType < 0) {
            // initialise the sprite type
            m_SpriteType = 0;
        }
    }
    m_Dirty = true;
}
//---------------------------------------------------------------------------
void __fastcall MapEntity::SetSelected(bool state)
{
    m_Dirty |= m_Selected != state;
    m_Selected = state;
}
//---------------------------------------------------------------------------
void __fastcall MapEntity::SetDirty(bool state)
{
    m_Dirty = true;
}
//---------------------------------------------------------------------------
bool __fastcall MapEntity::GetIsSprite() const
{
    return m_ImageType == Visuals::itSprite;
}
//---------------------------------------------------------------------------
void __fastcall MapEntity::SetSpriteType(int type)
{
    m_SpriteType = (type >= 0 && m_ImageType == Visuals::itSprite) ? type : -1;
}
//---------------------------------------------------------------------------
void __fastcall MapEntity::SetRoomIndex(unsigned int index)
{
    if (m_Document->CanBeLocked && !m_RoomLocked && m_RoomIndex != index) {
        m_RoomIndex = index;
        m_Dirty = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall MapEntity::SetRoomLocked(bool lock)
{
    if (m_Document->CanBeLocked) {
        m_RoomLocked = lock;
        m_Dirty = true;
    }
}
//---------------------------------------------------------------------------

