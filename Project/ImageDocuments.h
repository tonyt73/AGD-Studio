//---------------------------------------------------------------------------
#ifndef ImageDocumentsH
#define ImageDocumentsH
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Graphics/GraphicsTypes.h"
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
            bool                    m_CanDeleteFrames;
            int                     m_Width;
            int                     m_Height;
            int                     m_NumOfFrames;
            FramesList              m_Frames;

            void        __fastcall  ExtractSize(const String& extra, const ImageTypes& type);

public:
                        __fastcall  ImageDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new ImageDocument(name); };

    virtual void        __fastcall  Save();

            bool        __fastcall  AddFrame();
            bool        __fastcall  DeleteFrame(int index);

            bool        __property  MultiFrame  = { read = m_MultiFrame };


__published:
            int         __property  Width       = { read = m_Width      };
            int         __property  Height      = { read = m_Height     };
            int         __property  Frames      = { read = CountFrames  };
            // TODO: add palette info
};
//---------------------------------------------------------------------------
class SpriteDocument : public ImageDocument
{
public:
                        __fastcall  SpriteDocument(const String& name, const String& extra);
    static Document*    __fastcall  Create(const String& name, const String& extra) { return new SpriteDocument(name, extra); };
};
//---------------------------------------------------------------------------
class ObjectDocument : public ImageDocument
{
private:

public:
                        __fastcall  ObjectDocument(const String& name, const String& extra);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new ObjectDocument(name, extra); };
};
//---------------------------------------------------------------------------
class TileDocument : public ImageDocument
{
private:

public:
                        __fastcall  TileDocument(const String& name, const String& extra);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TileDocument(name, extra); };
};
//---------------------------------------------------------------------------
class CharacterSetDocument : public ImageDocument
{
private:

public:
                        __fastcall  CharacterSetDocument(const String& name, const String& extra);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new CharacterSetDocument(name, extra); };
};
//---------------------------------------------------------------------------
#endif
