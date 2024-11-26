//---------------------------------------------------------------------------
#ifndef EventH
#define EventH
//---------------------------------------------------------------------------
#include "Project/Documents/Document.h"
//---------------------------------------------------------------------------
namespace Messaging
{
//---------------------------------------------------------------------------
class Event
{
private:
                String      m_Id;
public:
    __fastcall              Event(const String& id)
                            : m_Id(id)
                            {
                            }

    __property  String      Id = { read = m_Id };
};
//---------------------------------------------------------------------------
template <class T>
class OnChange : public Event
{
private:
    T                       m_NewValue;
    T                       m_OldValue;
public:
    __fastcall              OnChange(const String& id, const T& newValue, const T& oldValue = T())
                            : Event(id)
                            , m_NewValue(newValue)
                            , m_OldValue(oldValue)
                            {
                            }

    __property  T           Value    = { read = m_NewValue };
    __property  T           OldValue = { read = m_OldValue };
};
//---------------------------------------------------------------------------
template <class T>
class DocumentChange : public Event
{
private:
   const Project::Document* m_Document;
    T                       m_Value;
public:
    __fastcall              DocumentChange(const String& id, const Project::Document* document, const T& value = T())
                            : Event(id)
                            , m_Document(document)
                            , m_Value(value)
                            {
                            }

    __property  T            Value    = { read = m_Value    };
    __property  const Project::Document* document = { read = m_Document };
};
//---------------------------------------------------------------------------
enum MessageType { etInformation, etWarning, etError, etDebug, etClear, etHelpKeys };
class MessageEvent : public Event
{
protected:
    MessageType             m_MessageType;
public:
    __fastcall              MessageEvent(const String& message, MessageType type)
                            : Event(message)
                            , m_MessageType(type)
                            {
                            }

    __property  String      Message = { read = m_Id };
    __property  MessageType Type    = { read = m_MessageType };
};
//---------------------------------------------------------------------------
class RoomSelected : public Event
{
private:
    TSize                   m_Room;
public:
    __fastcall              RoomSelected(TSize room)
                            : Event("room.selected")
                            , m_Room(room)
                            {
                            }

    __property  TSize       Room = { read = m_Room };
};
//---------------------------------------------------------------------------
class SetStartRoom : public Event
{
private:
    TPoint                  m_Room;
public:
    __fastcall              SetStartRoom(const TPoint& room)
                            : Event("set.start.room")
                            , m_Room(room)
                            {
                            }

    __property  TPoint      Room = { read = m_Room };
};
//---------------------------------------------------------------------------
class StartRoomChanged : public Event
{
private:
    TPoint                  m_Room;
public:
    __fastcall              StartRoomChanged(const TPoint& room)
                            : Event("start.room.changed")
                            , m_Room(room)
                            {
                            }

    __property  TPoint      Room = { read = m_Room };
};
//---------------------------------------------------------------------------
class UpdateProperties : public Event
{
public:
    __fastcall              UpdateProperties()
                            : Event("update.properties")
                            {
                            }
};
//---------------------------------------------------------------------------
class WindowChangedEvent : public Event
{
private:
    const TRect&            m_Window;
public:
    __fastcall              WindowChangedEvent(const TRect& window)
                            : Event("window.changed")
                            , m_Window(window)
                            {
                            }

    __property  const TRect& Window = { read = m_Window };
};
//---------------------------------------------------------------------------
class ThemeChangedEvent : public Event
{
public:
    __fastcall              ThemeChangedEvent()
                            : Event("theme.changed")
                            {
                            }
};
//---------------------------------------------------------------------------
} // Messaging namespace
#define ClearMessage(a)         Bus::Publish<MessageEvent>(MessageEvent((a), etClear      ))
#define ErrorMessage(a)         Bus::Publish<MessageEvent>(MessageEvent((a), etError      ))
#define WarningMessage(a)       Bus::Publish<MessageEvent>(MessageEvent((a), etWarning    ))
#define InformationMessage(a)   Bus::Publish<MessageEvent>(MessageEvent((a), etInformation))
#define DebugMessage(a)         Bus::Publish<MessageEvent>(MessageEvent((a), etDebug      ))
#define HelpKeysMessage(a)      Bus::Publish<MessageEvent>(MessageEvent((a), etHelpKeys   ))
//---------------------------------------------------------------------------
#endif
