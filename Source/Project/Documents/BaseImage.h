//---------------------------------------------------------------------------
#ifndef BaseImageH
#define BaseImageH
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
   typedef std::vector<String>      FramesList;
   typedef std::map<String, String> LayerMap;

           unsigned int __fastcall  CountFrames() const;
           unsigned int __fastcall  CountImagesPerFrame() const;                                // the number of minimum image sized frames, for oversized images. ie. tile 16x8 is 2 images per frame
            void        __fastcall  SetFrames(unsigned int frames);                             // set the number of frames for the image
            String      __fastcall  GetFrame(unsigned int frame) const;                         // get the full frame (if oversized)
            void        __fastcall  SetFrame(unsigned int frame, const String& data);           // set the full frame (if oversized)
            String      __fastcall  GetHint(unsigned int frame) const;                          // used by the character set (font) images

protected:
                bool                m_MultiFrame;       // flag: supports multiple frames
                bool                m_CanModifyFrames;  // flag: supports adding/deleting frames
                bool                m_CanBeLocked;      // flag: supports locking the image to a room
                unsigned int        m_Width;            // width of a frame
                unsigned int        m_Height;           // height of a frame
                unsigned int        m_NumOfFrames;      // the number of frames
                unsigned int        m_Index;            // the index of the image in its type list
                Visuals::ImageTypes m_ImageType;        // the type of graphic image we are
                FramesList          m_Frames;           // the list of frames
                String              m_FrameLoader;      // used to load frames into the above frames list
                unsigned int        m_FramesLoaded;     // a count of frames loaded
                FramesList          m_Hints;            // the list of frames
                String              m_Hint;             // a hint string
                LayerMap            m_Layers;           // the map of layers data
                String              m_LayerName;        // used to load layers into the above layers list
                String              m_LayerData;        // used to load layers into the above layers list

    virtual void        __fastcall  OnEndObject(const String& object) override;
            void        __fastcall  ExtractSize(const String& extra);

           unsigned int __fastcall  GetIndex() const;
           unsigned int __fastcall  GetLayerCount() const;
            void        __fastcall  AddLayer(const String& name, const String& value);
    virtual void        __fastcall  DoSave() override;
    virtual void        __fastcall  DoSaveExtra();

public:
                        __fastcall  ImageDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name, const String&) { return new ImageDocument(name); }
            Document*   __fastcall  Copy(const Document* document) override;


            bool        __fastcall  AddFrame(int index = -1, const String& hint = "");
            bool        __fastcall  DeleteFrame(unsigned int index);
            String      __fastcall  GetLayer(const String& name) const;
            void        __fastcall  SetLayer(const String& name, const String& value);      // set the name of a layer - ie. tiles use block type
            bool        __fastcall  LayerExists(const String& name) const;
            bool        __fastcall  IsFirstOfType() const;

            bool        __property  MultiFrame                = { read = m_MultiFrame               };
            bool        __property  CanModifyFrames           = { read = m_CanModifyFrames          };
            bool        __property  CanBeLocked               = { read = m_CanBeLocked              };
            String      __property  Frame[int index]          = { read = GetFrame, write = SetFrame };
            String      __property  Hint[int index]           = { read = GetHint                    };
           unsigned int __property  Layers                    = { read = GetLayerCount              };
   Visuals::ImageTypes  __property  ImageType                 = { read = m_ImageType                };

__published:
           unsigned int __property  Width                     = { read = m_Width                    };
           unsigned int __property  Height                    = { read = m_Height                   };
           unsigned int __property  Frames                    = { read = CountFrames                };
           unsigned int __property  ImagesPerFrame            = { read = CountImagesPerFrame        };
           unsigned int __property  Index                     = { read = GetIndex                   };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
