//---------------------------------------------------------------------------
#ifndef ImageDocumentsH
#define ImageDocumentsH
//---------------------------------------------------------------------------
#include "Project/Document.h"
#include "Graphics/GraphicsTypes.h"
//---------------------------------------------------------------------------
// ImageDocument
// This class encapulates what is an image document.
// It is only used to manage the image content (aka: frames).
// It DOES NOT know the format of the image data; as that is specified by the
// the project machine and graphics mode used.
// All frames are stored in a machine independent graphic format in hex.
// Basically it is standard bitmap data. Conversion to machine specific graphic
// mode format is done during the build process.
// Only the graphic mode class knows how to encode this information.
//---------------------------------------------------------------------------
class ImageDocument : public Document
{
private:
    typedef std::vector<String>     FramesList;

            void        __fastcall  OnEndObject(const String& object);
            int         __fastcall  CountFrames() const;
            int         __fastcall  CountImagesPerFrame() const;
            void        __fastcall  SetFrames(int frames);
            String      __fastcall  GetFrame(int frame) const;
            void        __fastcall  SetFrame(int frame, const String& data);

protected:
            bool                    m_MultiFrame;       // flag: supports multiple frames
            bool                    m_CanDeleteFrames;  // flag: supports deleting frames
            int                     m_Width;            // width of a frame
            int                     m_Height;           // height of a frame
            int                     m_NumOfFrames;      // the number of frames
            ImageTypes              m_ImageType;        // the type of graphic image we are
            FramesList              m_Frames;           // the list of frames
            String                  m_FrameLoader;      // used to load frames into the above frames list

            void        __fastcall  ExtractSize(const String& extra);

public:
                        __fastcall  ImageDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new ImageDocument(name); };

    virtual void        __fastcall  Save();

            bool        __fastcall  AddFrame();
            bool        __fastcall  DeleteFrame(int index);

            bool        __property  MultiFrame      = { read = m_MultiFrame                 };
            String      __property  Frame           = { read = GetFrame, write = SetFrame   };

__published:
            int         __property  Width           = { read = m_Width                      };
            int         __property  Height          = { read = m_Height                     };
            int         __property  Frames          = { read = CountFrames                  };
            int         __property  ImagesPerFrame  = { read = CountImagesPerFrame          };
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
public:
                        __fastcall  ObjectDocument(const String& name, const String& extra);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new ObjectDocument(name, extra); };
};
//---------------------------------------------------------------------------
class TileDocument : public ImageDocument
{
public:
                        __fastcall  TileDocument(const String& name, const String& extra);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TileDocument(name, extra); };
};
//---------------------------------------------------------------------------
class CharacterSetDocument : public ImageDocument
{
public:
                        __fastcall  CharacterSetDocument(const String& name, const String& extra);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new CharacterSetDocument(name, extra); };
};
//---------------------------------------------------------------------------
#endif
