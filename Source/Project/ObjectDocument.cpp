//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ObjectDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ObjectDocument::ObjectDocument(const String& name, const String& extra)
: ImageDocument(name)
, m_State(osDisabled)
{
    m_ImageType = itObject;
    m_CanBeLocked = true;
    m_SubType = "Object";
    m_Folder = "Images\\Objects";

    m_PropertyMap["Image.RoomIndex"] = &m_RoomIndex;
    m_PropertyMap["Image.Position.X"] = &m_Position.X;
    m_PropertyMap["Image.Position.Y"] = &m_Position.Y;
    m_PropertyMap["Image.State"] = &m_State;

    RegisterProperty("Name", "Details", "The name of the object");
    RegisterProperty("Room", "Details", "The Location of the room the Object is in. In Across (X) and Down (Y) coordinates");
    RegisterProperty("Position", "Details", "The pixel position of the object in the room");
    RegisterProperty("State", "Details", "The state the Object is in (Unassigned, Inventory or Room)");
    m_File = GetFile();
    ExtractSize(extra);
    AddFrame();
}
//---------------------------------------------------------------------------
int __fastcall ObjectDocument::GetPosition(int index)
{
    return index ? m_Position.Y : m_Position.X;
}
//---------------------------------------------------------------------------
void __fastcall ObjectDocument::SetPosition(int value, int index)
{
    if (index)
        m_Position.Y = value;
    else
        m_Position.X = value;
}
//---------------------------------------------------------------------------
void __fastcall ObjectDocument::SetRoomIndex(int value)
{
    if (0 <= value && value <= 255) {
        m_RoomIndex = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall ObjectDocument::DoSaveExtra()
{
    Write("RoomIndex", m_RoomIndex);
    Write("State", m_State);
    Push("Position");
    Write("X", (int)m_Position.X);
    Write("Y", (int)m_Position.Y);
    Pop();
}

