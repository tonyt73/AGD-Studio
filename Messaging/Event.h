//---------------------------------------------------------------------------
#ifndef EventH
#define EventH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
class Event
{
private:
    String  m_Id;
public:
            __fastcall  Event(const String& id) : m_Id(id) {}

    __property  String  Id = { read = m_Id };
};
//---------------------------------------------------------------------------
template <class T>
class OnChange : public Event
{
private:
    T m_NewValue;
    T m_OldValue;
public:
    __fastcall OnChange(const String& id, const T& newValue, const T& oldValue = T())
    : Event(id)
    , m_NewValue(newValue)
    , m_OldValue(oldValue)
    {
    }

    __property  T Value = { read = m_NewValue };
    __property  T OldValue = { read = m_OldValue };
};
//---------------------------------------------------------------------------
template <class T>
class DocumentChange : public Event
{
private:
    const Document* m_Document;
    T m_Value;
public:
    __fastcall DocumentChange(const String& id, const Document* document, const T& value = T())
    : Event(id)
    , m_Document(document)
    , m_Value(value)
    {
    }

    __property  T Value = { read = m_Value };
    __property  const Document* document = { read = m_Document };
};
//---------------------------------------------------------------------------
enum MessageType { etInformation, etWarning, etError, etDebug, etHelpKeys };
class MessageEvent : public Event
{
protected:
    MessageType m_MessageType;
public:
    __fastcall MessageEvent(const String& message, MessageType type)
    : Event(message)
    , m_MessageType(type)
    {
    }

    __property  String      Message = { read = m_Id };
    __property  MessageType Type    = { read = m_MessageType };
};
//---------------------------------------------------------------------------
class ErrorMessageEvent : public MessageEvent
{
public:
    __fastcall ErrorMessageEvent(const String& message)
    : MessageEvent(message, etError)
    {
    }
};
//---------------------------------------------------------------------------
class WarningMessageEvent : public MessageEvent
{
public:
    __fastcall WarningMessageEvent(const String& message)
    : MessageEvent(message, etWarning)
    {
    }
};
//---------------------------------------------------------------------------
class InformationMessageEvent : public MessageEvent
{
public:
    __fastcall InformationMessageEvent(const String& message)
    : MessageEvent(message, etInformation)
    {
    }
};
//---------------------------------------------------------------------------
class DebugMessageEvent : public MessageEvent
{
public:
    __fastcall DebugMessageEvent(const String& message)
    : MessageEvent(message, etDebug)
    {
    }
};
//---------------------------------------------------------------------------
class HelpKeysMessageEvent : public MessageEvent
{
public:
    __fastcall HelpKeysMessageEvent(const String& message)
    : MessageEvent(message, etHelpKeys)
    {
    }
};
//---------------------------------------------------------------------------
class RoomSelected : public Event
{
private:
    TSize   m_Room;
public:
    __fastcall RoomSelected(TSize room)
    : Event("room.selected")
    , m_Room(room)
    {
    }

    __property  TSize Room = { read = m_Room };
};
//---------------------------------------------------------------------------
class SetStartRoom : public Event
{
private:
    TPoint  m_Room;
public:
    __fastcall SetStartRoom(TPoint room)
    : Event("set.start.room")
    , m_Room(room)
    {
    }

    __property  TPoint Room = { read = m_Room };
};
//---------------------------------------------------------------------------
class StartRoomChanged : public Event
{
private:
    TPoint  m_Room;
public:
    __fastcall StartRoomChanged(TPoint room)
    : Event("start.room.changed")
    , m_Room(room)
    {
    }

    __property  TPoint Room = { read = m_Room };
};
//---------------------------------------------------------------------------
class UpdateProperties : public Event
{
public:
    __fastcall UpdateProperties()
    : Event("update.properties")
    {
    }
};
//---------------------------------------------------------------------------
class WindowChangedEvent : public Event
{
private:
    const TRect&    m_Window;
public:
    __fastcall WindowChangedEvent(const TRect& window)
    : Event("window.changed")
    , m_Window(window)
    {
    }
    __property  const TRect& Window = { read = m_Window };
};
//---------------------------------------------------------------------------
#endif
