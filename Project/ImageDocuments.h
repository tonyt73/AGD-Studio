//---------------------------------------------------------------------------
#ifndef ImageDocumentsH
#define ImageDocumentsH
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Project/DocumentSet.h"
//---------------------------------------------------------------------------
class ImageDocument : public Document
{
private:
    // width, height, format, palette
            int                     m_Width;
            int                     m_Height;
            // Machine specific image
public:
                        __fastcall  ImageDocument();
    static  Document*   __fastcall  Create() { return new ImageDocument(); };

            void        __fastcall  Save();

__published:
            int         __property  Width       = { read = m_Width , write = m_Width    };
            int         __property  Height      = { read = m_Height, write = m_Height   };
            // TODO: add palette info
};
//---------------------------------------------------------------------------
class ImageDocumentSet : public DocumentSet
{
private:
            int                     m_Width;
            int                     m_Height;
            int                     m_Count;
public:
                        __fastcall  ImageDocumentSet();
    static  Document*   __fastcall  Create() { return new ImageDocumentSet(); };

__published:
    __property          int         Width       = { read = m_Width , write = m_Width    };
    __property          int         Height      = { read = m_Height, write = m_Height   };
    __property          int         Count       = { read = m_Count                      };  // TODO: change to GetCount()
};
//---------------------------------------------------------------------------
class SpriteDocument : public ImageDocumentSet
{
private:
public:
                        __fastcall  SpriteDocument();
    static Document*    __fastcall  Create() { return new SpriteDocument(); };
};
//---------------------------------------------------------------------------
class ObjectDocument : public ImageDocument
{
private:

public:
                        __fastcall  ObjectDocument();
    static  Document*   __fastcall  Create() { return new ObjectDocument(); };
};
//---------------------------------------------------------------------------
class TileDocument : public ImageDocument
{
private:

public:
                        __fastcall  TileDocument();
    static  Document*   __fastcall  Create() { return new TileDocument(); };
};
//---------------------------------------------------------------------------
class TileSetDocument : public ImageDocumentSet
{
private:
            int                     m_TileWidth;
            int                     m_TileHeight;
            bool                    m_IsTransparent;
            TColor                  m_TransparentColor;

public:

                        __fastcall  TileSetDocument();
    static  Document*   __fastcall  Create() { return new TileSetDocument(); };

__published:
    __property          int         TileWidth       = { read = m_TileWidth          , write = m_TileWidth       };
    __property          int         TileHeight      = { read = m_TileHeight         , write = m_TileHeight      };
    __property          bool        IsTransparent   = { read = m_IsTransparent      , write = m_IsTransparent   };
    __property          TColor      TransparentColor= { read = m_TransparentColor   , write = m_TransparentColor};
};
//---------------------------------------------------------------------------
#endif
