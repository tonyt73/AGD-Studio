//---------------------------------------------------------------------------
#ifndef EventH
#define EventH
//---------------------------------------------------------------------------
#include "Project/Documents/Document.h"
//---------------------------------------------------------------------------
namespace MsgBus
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

    __property  T                        Value    = { read = m_Value    };
    __property  const Project::Document* Document = { read = m_Document };
};
//---------------------------------------------------------------------------
class OpenDocument : public Event
{
private:
   Project::Document*       m_Document;
public:
    __fastcall              OpenDocument(Project::Document* document)
                            : Event("open.document")
                            , m_Document(document)
                            {
                            }

    __property Project::Document* Document = { read = m_Document };
};
//---------------------------------------------------------------------------
class DocumentAdded : public Event
{
private:
   Project::Document*       m_Document;
public:
    __fastcall              DocumentAdded(Project::Document* document)
                            : Event("document.added")
                            , m_Document(document)
                            {
                            }

    __property Project::Document* Document = { read = m_Document };
};
//---------------------------------------------------------------------------
enum MessageType { etInformation, etWarning, etError, etDebug, etClear, etHelpKeys };
class MessageEvent : public Event
{
protected:
    MessageType             m_MessageType;
    String                  m_Extra;
public:
    __fastcall              MessageEvent(const String& message, MessageType type, String extra = "")
                            : Event(message)
                            , m_MessageType(type)
                            , m_Extra(extra)
                            {
                            }

    __property  String      Message = { read = m_Id          };
    __property  String      Extra   = { read = m_Extra       };
    __property  MessageType Type    = { read = m_MessageType };
};
//---------------------------------------------------------------------------
class RoomSelected : public Event
{
private:
    TPoint                  m_Room;
public:
    __fastcall              RoomSelected(TPoint room)
                            : Event("room.selected")
                            , m_Room(room)
                            {
                            }

    __property  TPoint      Room = { read = m_Room };
};
//---------------------------------------------------------------------------
class SetSpecialRoom : public Event
{
private:
    TPoint                  m_RoomPt;
    int                     m_RoomIndex;
public:
    __fastcall              SetSpecialRoom(const TPoint& roomPt, int roomIndex)
                            : Event("set.special.room")
                            , m_RoomPt(roomPt)
                            , m_RoomIndex(roomIndex)
                            {
                            }

    __property  TPoint      Room  = { read = m_RoomPt    };
    __property  TPoint      Index = { read = m_RoomIndex };
};
//---------------------------------------------------------------------------
class SpecialRoomChanged : public Event
{
private:
    TPoint                  m_RoomPt;
    int                     m_RoomIndex;
public:
    __fastcall              SpecialRoomChanged(const TPoint& roomPt, int roomIndex)
                            : Event("special.room.changed")
                            , m_RoomPt(roomPt)
                            , m_RoomIndex(roomIndex)
                            {
                            }

    __property  TPoint      Room  = { read = m_RoomPt    };
    __property  TPoint      Index = { read = m_RoomIndex };
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
} // MsgBus namespace
//---------------------------------------------------------------------------
#define ClearMessage(a)          Bus::Publish<MessageEvent>(MessageEvent((a), etClear      ))
#define ErrorMessage(a)          Bus::Publish<MessageEvent>(MessageEvent((a), etError      ))
#define WarningMessage(a)        Bus::Publish<MessageEvent>(MessageEvent((a), etWarning    ))
#define InformationMessage(a)    Bus::Publish<MessageEvent>(MessageEvent((a), etInformation))
#define DebugMessage(a)          Bus::Publish<MessageEvent>(MessageEvent((a), etDebug      ))
#define HelpKeysMessage(a)       Bus::Publish<MessageEvent>(MessageEvent((a), etHelpKeys   ))
#define HelpKeysNameMessage(a,b) Bus::Publish<MessageEvent>(MessageEvent((a), etHelpKeys, b))
//---------------------------------------------------------------------------
#endif
