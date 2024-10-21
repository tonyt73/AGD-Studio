//---------------------------------------------------------------------------
#ifndef ObjectDocumentH
#define ObjectDocumentH
//---------------------------------------------------------------------------
#include "ImageDocument.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class ObjectDocument : public ImageDocument
{
private:
    // note: for the IDE property editor to work on there properties, they must be new'd for TPersisent to work
            int                     m_RoomIndex;
            TPoint                  m_Position;
            Visuals::ObjectState    m_State;

            int         __fastcall  GetPosition(int index);
            void        __fastcall  SetPosition(int value, int index);
            void        __fastcall  SetRoomIndex(int value);

protected:
    virtual void        __fastcall  DoSaveExtra();

public:
                            __fastcall  ObjectDocument(const String& name, const String& extra);
static Project::Document*   __fastcall  Create(const String& name, const String& extra) { return new ObjectDocument(name, extra); };

    __property       const TPoint&  Position    = { read = m_Position, write = m_Position   };

__published:
    __property                 int  RoomIndex   = { read = m_RoomIndex, write = SetRoomIndex};
    __property                 int  X           = { read = GetPosition, index = 0           };
    __property                 int  Y           = { read = GetPosition, index = 1           };
    Visuals::ObjectState __property State       = { read = m_State, write = m_State         };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
