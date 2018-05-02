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
            void        __fastcall  SetFrames(int frames);

protected:
    // width, height, format, palette
            bool                    m_MultiFrame;
            int                     m_Width;
            int                     m_Height;
            FramesList              m_Frames;


public:
                        __fastcall  ImageDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new ImageDocument(name); };

    virtual void        __fastcall  Save();

            bool        __fastcall  AddFrame();
            bool        __fastcall  DeleteFrame(int index);

            bool        __property  MultiFrame  = { read = m_MultiFrame                   };

__published:
            int         __property  Width       = { read = m_Width    , write = m_Width   };
            int         __property  Height      = { read = m_Height   , write = m_Height  };
            int         __property  Frames      = { read = CountFrames, write = SetFrames };
            // TODO: add palette info
};
//---------------------------------------------------------------------------
class SpriteDocument : public ImageDocument
{
public:
                        __fastcall  SpriteDocument(const String& name);
    static Document*    __fastcall  Create(const String& name, const String& extra) { return new SpriteDocument(name); };
};
//---------------------------------------------------------------------------
class ObjectDocument : public ImageDocument
{
private:

public:
                        __fastcall  ObjectDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new ObjectDocument(name); };
};
//---------------------------------------------------------------------------
class TileDocument : public ImageDocument
{
private:

public:
                        __fastcall  TileDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TileDocument(name); };
};
//---------------------------------------------------------------------------
#endif
