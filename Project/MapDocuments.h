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
    TPoint          m_Pt;
    unsigned int    m_Id;
    unsigned int    m_LoadId;
    ImageDocument*  m_Document;
    bool            m_Dirty;

    friend class TiledMapDocument;

    void                __fastcall  SetPoint(const TPoint& pt);
   const ImageDocument* __fastcall  GetDocument() const;
    unsigned int        __fastcall  GetId() const;
    void                __fastcall  SetId(unsigned int id);

public:
                        __fastcall  Entity();

    void                __fastcall  Clear();
    void                __fastcall  Clean();

    __property  unsigned int                Id    = { read = GetId, write = SetId   };
    __property  ImageDocument const * const Image = { read = GetDocument            };
    __property  TPoint                      Pt    = { read = m_Pt, write = SetPoint };
    __property  bool                        Dirty = { read = m_Dirty                };
};
typedef std::vector<Entity>     EntityList;
//---------------------------------------------------------------------------
enum MapEntities { meWorkspace, meScratchPad };
//---------------------------------------------------------------------------
class TiledMapDocument : public Document
{
protected:
    EntityList                      m_Workspace;
    EntityList                      m_ScratchPad;

            int                     m_Across;
            int                     m_Down;
            int                     m_Width;
            int                     m_Height;
            int                     m_StartLocationX;
            int                     m_StartLocationY;
            TColor                  m_BackgroundColor;
            Entity                  m_EntityLoader;

            void        __fastcall  OnEndObject(const String& object);
            void        __fastcall  OnDocumentChanged(const OnDocumentChange<String>& message);
            void        __fastcall  DoSave();

public:
                        __fastcall  TiledMapDocument(const String& name);
                        __fastcall ~TiledMapDocument();
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TiledMapDocument(name); };

            void        __fastcall  Get(MapEntities type, EntityList& entities) const;
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
