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
    TPoint                          m_Pt;           // position of the entity
    TPoint                          m_DragPt;       // the offset of the entity been dragged
    unsigned int                    m_Id;           // the document id
    unsigned int                    m_LoadId;
    ImageDocument*                  m_Document;     // the image document we represent
    bool                            m_Dirty;        // flag: entity needs to be rendered
    bool                            m_Selected;     // flag: entity is selected
    int                             m_SpriteType;   // the type of sprite
    bool                            m_RoomLocked;   // the sprite is locked to the room
    unsigned int                    m_RoomIndex;    // the index of the room we are locked to

    friend class TiledMapDocument;

    void                __fastcall  SetPoint(const TPoint& pt);
    TPoint              __fastcall  GetPoint() const;
    void                __fastcall  SetDragPoint(const TPoint& pt);
    TPoint              __fastcall  GetDragPoint() const;
   ImageDocument* const __fastcall  GetDocument() const;
    unsigned int        __fastcall  GetId() const;
    void                __fastcall  SetId(unsigned int id);
    void                __fastcall  SetSelected(bool state);
    void                __fastcall  SetDirty(bool state);
    void                __fastcall  SetSpriteType(int type);
    void                __fastcall  SetRoomIndex(unsigned int index);
	void                __fastcall  SetRoomLocked(bool lock);

public:
						__fastcall  Entity();
						__fastcall  Entity(const Entity& other);
						__fastcall ~Entity();

	Entity&             __fastcall  operator=(const Entity& other);
	bool                __fastcall  operator==(const Entity& other);

	void                __fastcall  Clear();
	void                __fastcall  Clean();

	__property  unsigned int        Id          = { read = GetId, write = SetId                 };
	__property ImageDocument* const Image       = { read = GetDocument                          };
	__property  TPoint              Pt          = { read = GetPoint, write = SetPoint           };
	__property  TPoint              DragPt      = { read = GetDragPoint, write = SetDragPoint   };
	__property  bool                Dirty       = { read = m_Dirty, write = SetDirty            };
	__property  bool                Selected    = { read = m_Selected, write = SetSelected      };
	__property  int                 SpriteType  = { read = m_SpriteType, write = SetSpriteType  };
	__property  bool                RoomLocked  = { read = m_RoomLocked, write = SetRoomLocked  };
	__property  unsigned int        RoomIndex   = { read = m_RoomIndex, write = SetRoomIndex    };
};
typedef std::vector<Entity>     EntityList;
//---------------------------------------------------------------------------
enum MapEntities { meMap, meRoom, meScratchPad };
const int g_MaxMapRoomsAcross = 16;
const int g_MaxMapRoomsDown   = 16;
//---------------------------------------------------------------------------
class TiledMapDocument : public Document
{
protected:
    EntityList                      m_Map;
    EntityList                      m_Room;
    EntityList                      m_ScratchPad;

                                    // TODO: Convert to AGDX:Point for better display in the property editor
			int                     m_StartRoomIndex;
			AGDX::Point				m_StartRoomCoords;
			int                     m_ScreenCount;
			Entity                  m_EntityLoader;
			TSize                   m_ActiveRoom;
			std::vector<int>        m_RoomMapping; // a mapping from Studio to .AGD screen indexes
			int                     m_RoomMappingWidth;
			int                     m_RoomMappingHeight;
			int                     m_RoomMappingIndex;

			void        __fastcall  OnEndObject(const String& object);
			void        __fastcall  OnDocumentChanged(const DocumentChange<String>& message);
			void        __fastcall  OnSetStartRoom(const SetStartRoom& event);
			void        __fastcall  DoSave();
			void        __fastcall  UpdateEntityRooms();
            void        __fastcall  UpdateScreenCoords();
			void        __fastcall  OnLoaded();
            void        __fastcall  SetStartRoomCoords(const AGDX::Point& coords);


public:
						__fastcall  TiledMapDocument(const String& name);
						__fastcall ~TiledMapDocument();
	static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TiledMapDocument(name); };

			EntityList  __fastcall  Get(ImageTypes type) const;
	const   EntityList& __fastcall  Get(MapEntities type, TSize room = TSize(0,0));
			void        __fastcall  Set(MapEntities type, const EntityList& entities);

			TRect       __fastcall  GetMinimalMapSize();
			int         __fastcall  GetRoomIndex(const AGDX::Point& room, bool newIdForUndefinedRoom = false);
			bool        __fastcall  IsRoomEmpty(int x, int y);

			int         __property  ScreenCount = { read = m_ScreenCount };

__published:
	__property          int         StartRoomIndex	    = { read = m_StartRoomIndex  };
	__property          AGDX::Point StartRoomLocation   = { read = m_StartRoomCoords, write = SetStartRoomCoords };
};
//---------------------------------------------------------------------------
#endif
