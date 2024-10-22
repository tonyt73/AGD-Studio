//---------------------------------------------------------------------------
#ifndef ImageDocumentH
#define ImageDocumentH
//---------------------------------------------------------------------------
#include "Document.h"
#include "Visuals/GraphicsTypes.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
// ImageDocument
// This class encapulates what is an image document.
// It is only used to manage the image content (aka: frames and optionally layers).
// It DOES NOT know the format of the image data; as that is specified by the
// the project machine and graphics mode used.
// All frames are stored in their machine dependent graphic format in hex.
// Basically it is standard bitmap data.
// Only the graphic mode class knows how to encode this information.
//---------------------------------------------------------------------------
class ImageDocument : public Document
{
private:
    typedef std::vector<String>     FramesList;
    typedef std::map<String, String>LayerMap;

            int          CountFrames() const;
            int          CountImagesPerFrame() const;
            void         SetFrames(int frames);
            String       GetFrame(int frame) const;
            void         SetFrame(int frame, const String& data);
            String       GetHint(int frame) const;

protected:
            bool                    m_MultiFrame;       // flag: supports multiple frames
            bool                    m_CanModifyFrames;  // flag: supports adding/deleting frames
            bool                    m_CanBeLocked;      // flag: supports locking the image to a room
            int                     m_Width;            // width of a frame
            int                     m_Height;           // height of a frame
            int                     m_NumOfFrames;      // the number of frames
            int                     m_Index;            // the index of the image in its type list
            Visuals::ImageTypes     m_ImageType;        // the type of graphic image we are
            FramesList              m_Frames;           // the list of frames
            String                  m_FrameLoader;      // used to load frames into the above frames list
            int                     m_FramesLoaded;     // a count of frames loaded
            FramesList              m_Hints;            // the list of frames
            String                  m_Hint;             // a hint string
            LayerMap                m_Layers;           // the map of layers data
            String                  m_LayerName;        // used to load layers into the above layers list
            String                  m_LayerData;        // used to load layers into the above layers list

    virtual void         OnEndObject(const String& object);
            void         ExtractSize(const String& extra);

            int          GetIndex() const;
            int          GetLayerCount() const;
            void         AddLayer(const String& name, const String& value);
    virtual void         DoSave();
    virtual void         DoSaveExtra();

public:
                         ImageDocument(const String& name);
    static  Document*    Create(const String& name, const String& extra) { return new ImageDocument(name); };

            bool         AddFrame(int index = -1, const String& hint = "");
            bool         DeleteFrame(int index);
            String       GetLayer(const String& name);
            void         SetLayer(const String& name, const String& value);
            bool         LayerExists(const String& name) const;
            bool         IsFirstOfType() const;

            bool        __property  MultiFrame      = { read = m_MultiFrame                 };
            bool        __property  CanModifyFrames = { read = m_CanModifyFrames            };
            bool        __property  CanBeLocked     = { read = m_CanBeLocked                };
            String      __property  Frame[int index]= { read = GetFrame, write = SetFrame   };
            String      __property  Hint[int index] = { read = GetHint                      };
            int         __property  Layers          = { read = GetLayerCount                };
   Visuals::ImageTypes  __property  ImageType       = { read = m_ImageType                  };

__published:
            int         __property  Width           = { read = m_Width                      };
            int         __property  Height          = { read = m_Height                     };
            int         __property  Frames          = { read = CountFrames                  };
            int         __property  ImagesPerFrame  = { read = CountImagesPerFrame          };
            int         __property  Index           = { read = GetIndex                     };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
