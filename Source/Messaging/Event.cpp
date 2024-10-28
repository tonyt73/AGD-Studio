//---------------------------------------------------------------------------
#include <AgdStudio.pch.h>
//---------------------------------------------------------------------------
#include "Event.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace ::Messaging;
//---------------------------------------------------------------------------
__fastcall Event::Event(const String& id)
: m_Id(id)
{
}
//---------------------------------------------------------------------------
//template <class T>
//__fastcall OnChange::OnChange(const String& id, const T& newValue, const T& oldValue = T()))
//: Event(id)
//, m_NewValue(newValue)
//, m_OldValue(oldValue)
//{
//}
//---------------------------------------------------------------------------
//__fastcall DocumentChange::DocumentChange(const String& id, const Project::Document* document, const T& value = T())
//: Event(id)
//, m_Document(document)
//, m_Value(value)
//{
//}
//---------------------------------------------------------------------------
__fastcall MessageEvent::MessageEvent(const String& message, MessageType type)
: Event(message)
, m_MessageType(type)
{
}
//---------------------------------------------------------------------------
__fastcall RoomSelected::RoomSelected(TSize room)
: Event("room.selected")
, m_Room(room)
{
}
//---------------------------------------------------------------------------
__fastcall SetStartRoom::SetStartRoom(TPoint room)
: Event("set.start.room")
, m_Room(room)
{
}
//---------------------------------------------------------------------------
__fastcall StartRoomChanged::StartRoomChanged(TPoint room)
: Event("start.room.changed")
, m_Room(room)
{
}
//---------------------------------------------------------------------------
__fastcall UpdateProperties::UpdateProperties()
: Event("update.properties")
{
}
//---------------------------------------------------------------------------
__fastcall WindowChangedEvent::WindowChangedEvent(const TRect& window)
: Event("window.changed")
, m_Window(window)
{
}
//---------------------------------------------------------------------------
__fastcall ThemeChangedEvent::ThemeChangedEvent()
: Event("theme.changed")
{
}
//---------------------------------------------------------------------------
template class ::Messaging::OnChange<int>;
template class ::Messaging::OnChange<float>;
template class ::Messaging::OnChange<String>;
template class ::Messaging::OnChange<bool>;
template class ::Messaging::DocumentChange<String>;
//---------------------------------------------------------------------------

