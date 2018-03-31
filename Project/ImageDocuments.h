//---------------------------------------------------------------------------
#ifndef ImageDocumentsH
#define ImageDocumentsH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
class ImageDocument : public Document
{
private:
    // TODO: Change to machine independent image format
    typedef std::vector<String>     FramesList;

            int         __fastcall  CountFrames() const;

protected:
    // width, height, format, palette
            bool                    m_MultiFrame;
            int                     m_Width;
            int                     m_Height;
            FramesList              m_Frames;


public:
                        __fastcall  ImageDocument();
    static  Document*   __fastcall  Create() { return new ImageDocument(); };

    virtual void        __fastcall  Save();

            bool        __fastcall  AddFrame();
            bool        __fastcall  DeleteFrame(int index);

            bool        __property  MultiFrame  = { read = m_MultiFrame                 };

__published:
            int         __property  Width       = { read = m_Width , write = m_Width    };
            int         __property  Height      = { read = m_Height, write = m_Height   };
            int         __property  Frames      = { read = CountFrames                  };
            // TODO: add palette info
};
//---------------------------------------------------------------------------
class SpriteDocument : public ImageDocument
{
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
#endif
