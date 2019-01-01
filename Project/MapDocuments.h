//---------------------------------------------------------------------------
#ifndef MapDocumentsH
#define MapDocumentsH
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Project/ImageDocuments.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
class TiledMapDocument;
class Entity
{
protected:
    TPoint          m_Pt;           // position of the entity
    TPoint          m_DragPt;       // the offset of the entity been dragged
    unsigned int    m_Id;           // the document id
    unsigned int    m_LoadId;
    ImageDocument*  m_Document;     // the image document we represent
    bool            m_Dirty;        // flag: entity needs to be rendered
    bool            m_Selected;     // flag: entity is selected

    friend class TiledMapDocument;

    void                __fastcall  SetPoint(const TPoint& pt);
    TPoint              __fastcall  GetPoint() const;
    void                __fastcall  SetDragPoint(const TPoint& pt);
    TPoint              __fastcall  GetDragPoint() const;
   const ImageDocument* __fastcall  GetDocument() const;
    unsigned int        __fastcall  GetId() const;
    void                __fastcall  SetId(unsigned int id);
    void                __fastcall  SetSelected(bool state);
    void                __fastcall  SetDirty(bool state);

public:
                        __fastcall  Entity();
                        __fastcall  Entity(const Entity& other);
                        __fastcall ~Entity();

    Entity&             __fastcall  operator=(const Entity& other);

    void                __fastcall  Clear();
    void                __fastcall  Clean();

    __property  unsigned int                Id       = { read = GetId, write = SetId                };
    __property  ImageDocument const * const Image    = { read = GetDocument                         };
    __property  TPoint                      Pt       = { read = GetPoint, write = SetPoint          };
    __property  TPoint                      DragPt   = { read = GetDragPoint, write = SetDragPoint  };
    __property  bool                        Dirty    = { read = m_Dirty, write = SetDirty           };
    __property  bool                        Selected = { read = m_Selected, write = SetSelected     };
};
typedef std::vector<Entity>     EntityList;
//---------------------------------------------------------------------------
enum MapEntities { meMap, meRoom, meScratchPad };
//---------------------------------------------------------------------------
class TiledMapDocument : public Document
{
protected:
    EntityList                      m_Map;
    EntityList                      m_Room;
    EntityList                      m_ScratchPad;

            int                     m_Across;
            int                     m_Down;
            int                     m_Width;
            int                     m_Height;
            int                     m_StartLocationX;
            int                     m_StartLocationY;
            TColor                  m_BackgroundColor;
            Entity                  m_EntityLoader;
            TSize                   m_ActiveRoom;

            void        __fastcall  OnEndObject(const String& object);
            void        __fastcall  OnDocumentChanged(const DocumentChange<String>& message);
            void        __fastcall  OnStartRoomSet(const StartRoomSet& event);
            void        __fastcall  DoSave();
            void        __fastcall  GetRoom(int room);

public:
                        __fastcall  TiledMapDocument(const String& name);
                        __fastcall ~TiledMapDocument();
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TiledMapDocument(name); };

    const   EntityList& __fastcall  Get(MapEntities type, TSize room = TSize(0,0));
            void        __fastcall  Set(MapEntities type, const EntityList& entities);

__published:
    __property          int         RoomsAcross     = { read = m_Across         , write = m_Across          };
    __property          int         RoomsDown       = { read = m_Down           , write = m_Down            };
    __property          int         RoomWidth       = { read = m_Width          , write = m_Width           };
    __property          int         RoomHeight      = { read = m_Height         , write = m_Height          };
    __property          int         StartLocationX  = { read = m_StartLocationX , write = m_StartLocationX  };
    __property          int         StartLocationY  = { read = m_StartLocationY , write = m_StartLocationY  };
    __property          TColor      BackgroundColor = { read = m_BackgroundColor, write = m_BackgroundColor };
};
//---------------------------------------------------------------------------
#endif
