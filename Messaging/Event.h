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
class OnDocumentChange : public Event
{
private:
    const Document* m_Document;
    T m_Value;
public:
    __fastcall OnDocumentChange(const String& id, const Document* document, const T& value = T())
    : Event(id)
    , m_Document(document)
    , m_Value(value)
    {
    }

    __property  T Value = { read = m_Value };
    __property  Document document = { read = m_Document };
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
class OnMapResized : public Event
{
private:
    unsigned int m_Width;
    unsigned int m_Height;

public:
    __fastcall OnMapResized(unsigned int width, unsigned int height)
    : Event("MapResized")
    , m_Width(width)
    , m_Height(height)
    {
    }

    __property  unsigned int Width = { read = m_Width, write = m_Width };
    __property  unsigned int Height = { read = m_Height, write = m_Height };
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
class StartRoomSet : public Event
{
private:
    TPoint  m_Room;
public:
    __fastcall StartRoomSet(TPoint room)
    : Event("start.room.set")
    , m_Room(room)
    {
    }

    __property  TPoint Room = { read = m_Room };
};
//---------------------------------------------------------------------------
#endif
