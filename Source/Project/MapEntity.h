//---------------------------------------------------------------------------
#ifndef MapEntityH
#define MapEntityH
//---------------------------------------------------------------------------
#include "ImageDocument.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class TiledMapDocument;
class MapEntity
{
protected:
    friend class TiledMapDocument;

protected:
                TPoint              m_Pt;           // position of the entity
                TPoint              m_DragPt;       // the offset of the entity been dragged
                unsigned int        m_Id;           // the document id
                unsigned int        m_LoadId;
                ImageDocument*      m_Document;     // the image document we represent
                Visuals::ImageTypes m_ImageType;    // the type of image
                bool                m_Dirty;        // flag: entity needs to be rendered
                bool                m_Selected;     // flag: entity is selected
                int                 m_SpriteType;   // the type of sprite
                bool                m_RoomLocked;   // the sprite is locked to the room
                unsigned int        m_RoomIndex;    // the index of the room we are locked to

    void                __fastcall  SetPoint(const TPoint& pt);
    TPoint              __fastcall  GetPoint() const;
    void                __fastcall  SetDragPoint(const TPoint& pt);
    TPoint              __fastcall  GetDragPoint() const;
   ImageDocument* const __fastcall  GetDocument() const;
    unsigned int        __fastcall  GetId() const;
    bool                __fastcall  GetIsSprite() const;
    void                __fastcall  SetId(unsigned int id);
    void                __fastcall  SetSelected(bool state);
    void                __fastcall  SetDirty(bool state);
    void                __fastcall  SetSpriteType(int type);
    void                __fastcall  SetRoomIndex(unsigned int index);
    void                __fastcall  SetRoomLocked(bool lock);

public:
                        __fastcall  MapEntity();
                        __fastcall  MapEntity(const MapEntity& other);
                        __fastcall ~MapEntity();

    MapEntity&          __fastcall  operator=(const MapEntity& other);
    bool                __fastcall  operator==(const MapEntity& other);

    void                __fastcall  Clear();
    void                __fastcall  Clean();

    __property  unsigned int        Id          = { read = GetId, write = SetId                 };
    __property ImageDocument* const Image       = { read = GetDocument                          };
    __property  TPoint              Pt          = { read = GetPoint, write = SetPoint           };
    __property  TPoint              DragPt      = { read = GetDragPoint, write = SetDragPoint   };
    __property  bool                Dirty       = { read = m_Dirty, write = SetDirty            };
    __property  bool                Selected    = { read = m_Selected, write = SetSelected      };
    __property  bool                IsSprite    = { read = GetIsSprite                          };
    __property  int                 SpriteType  = { read = m_SpriteType, write = SetSpriteType  };
    __property  Visuals::ImageTypes Type        = { read = m_ImageType                          };
    __property  bool                RoomLocked  = { read = m_RoomLocked, write = SetRoomLocked  };
    __property  unsigned int        RoomIndex   = { read = m_RoomIndex, write = SetRoomIndex    };
};
//---------------------------------------------------------------------------
typedef std::vector<MapEntity>      MapEntityList;
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
