//---------------------------------------------------------------------------
#ifndef MapDocumentsH
#define MapDocumentsH
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Project/ImageDocuments.h"
//---------------------------------------------------------------------------
class TiledMapDocument : public Document
{
private:
    struct Entity
    {
        unsigned int    x;
        unsigned int    y;
        Document*       doc;
        String          name;
        String          type;
        String          subType;
    } _entity;
    typedef std::vector<Entity>     EntityList;

    EntityList                      m_Entities;

            int                     m_Across;
            int                     m_Down;
            int                     m_Width;
            int                     m_Height;
            int                     m_StartLocationX;
            int                     m_StartLocationY;
            TColor                  m_BackgroundColor;
            Entity                  m_EntityLoader;

            void        __fastcall  OnEndObject(const String& object);

public:
                        __fastcall  TiledMapDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TiledMapDocument(name); };

            void        __fastcall  Save();

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
