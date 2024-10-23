//---------------------------------------------------------------------------
#ifndef GraphicsBufferH
#define GraphicsBufferH
//---------------------------------------------------------------------------
#include "GraphicsTypes.h"
#include "GraphicsMode.h"
//---------------------------------------------------------------------------
// Pixel Masks for 1, 2, 4 and 8 pixels per byte
extern const unsigned char* g_PixelMasks[];
extern const unsigned char* g_PixelShfts[];
//---------------------------------------------------------------------------
namespace Visuals
{
//---------------------------------------------------------------------------
// GraphicsBuffer base class.
// Defines the common attributes of a graphics buffer.
// A graphics buffer is made up of 1 or more data buffers.
// Data buffers are generally used for pixel, attribute (color info) or character map data.
//---------------------------------------------------------------------------
class GraphicsBuffer
{
private:
                                    GraphicsBuffer() = delete;
protected:
    typedef std::vector<ByteBuffer> Buffers;

    const GraphicsMode&             m_GraphicsMode;     // the graphic mode definition
    unsigned int                    m_Width;            // the width of the buffer in pixels
    unsigned int                    m_Height;           // the height of the buffer in pixels
    float                           m_ScalarX;          // the width scalar
    float                           m_ScalarY;          // the height scalar
    unsigned int                    m_Stride;           // the stride of the buffer in bytes
    unsigned int                    m_PixelsPerByte;    // the number of pixel per bytes (inv of bits / pixels)
    unsigned int                    m_NumberOfBuffers;  // the number of data buffers using by this buffer type
    Buffers                         m_Buffers;          // the list of buffers
    BufferType                      m_BufferType;       // the type of graphics buffer this is
    std::vector<unsigned char>      m_SetColors;        // the list of color choices and their logical color index (i.e. pen/brush or ink/paper/flash/bright)
	std::unique_ptr<TBitmap>        m_Bitmap;           // the Windows bitmap we render to
    bool                            m_RenderInGreyscale;// flag: Indicates we render in greyscale
    bool                            m_Drawing;          // flag: Indicates we are drawing pixels; don't render immediately

                                    GraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode);
    void                            PushBuffer(unsigned int size);
    unsigned int                    GetNumberOfBuffers() const;
    unsigned int                    GetSizeOfBuffer(int index) const;
    virtual unsigned char           GetColorIndex(unsigned char index) const;
    virtual void                    SetColorIndex(unsigned char index, int logicalIndex);
    void                            SetRenderInGreyscale(bool value);
    unsigned char                   RemapPixel(unsigned char pixel) const;
    virtual void                    Render() const = 0;

public:
    virtual                        ~GraphicsBuffer();

                                    // Make a suitable buffer for the buffer type
    static void                     Make(unsigned int width, unsigned int height, const Visuals::GraphicsMode& mode, std::unique_ptr<GraphicsBuffer>& buffer);
                                    // sets the pixel to the specified palette color index
    virtual void                    SetPixel(unsigned int X, unsigned int Y, bool set = true) = 0;
                                    // retrieves the pixel color at the position specified
    virtual void                    GetColor(unsigned int X, unsigned int Y, unsigned char colorIndex = 0) = 0;
                                    // Retrieves the specified buffer index from the graphics buffer
    void                            GetBuffer(int index, ByteBuffer& buffer) const;
                                    // Get the native byte data for the buffer
    std::vector<unsigned char>      GetNative(ImageTypes type) const;
                                    // Get the hex data of the image
    String                          Get() const;
                                    // Set the bitmap data from the hex data
    virtual void                    Set(const String& data) = 0;
                                    // Copy the image onto the bitmap
    void                            Draw(TBitmap* bitmap, bool inMonochrome = false) const;
                                    // Copy the image bitmap onto the destination bitmap
    void                            Assign(TBitmap* bitmap) const;
                                    // Begin drawing operations on the canvas
    void                            Begin();
                                    // End drawing operations on the canvas
    void                            End();

    // Properties
                                    // Dimensions
    unsigned int        __property  Width                       = { read = m_Width                                           };
    unsigned int        __property  Height                      = { read = m_Height                                          };
    unsigned int        __property  ScalarX                     = { read = m_ScalarX                                         };
    unsigned int        __property  ScalarY                     = { read = m_ScalarY                                         };
                                    // Color
    unsigned char       __property  Color[unsigned char index]  = { read = GetColorIndex, write = SetColorIndex              };
                                    // Buffer info (used by image tools)
    BufferType          __property  BufferType                  = { read = m_BufferType                                      };
    unsigned int        __property  NumberOfBuffers             = { read = GetNumberOfBuffers                                };
    unsigned int        __property  SizeOfBuffer[int index]     = { read = GetSizeOfBuffer                                   };
    bool                __property  RenderInGreyscale           = { read = m_RenderInGreyscale, write = SetRenderInGreyscale };
};
//---------------------------------------------------------------------------
// TODO: To be implemented if MSX support is added
//class CharacterMapGraphicsBuffer : public GraphicsBuffer
//{
//private:
//
//    BufferType           GetBufferType(int index) { return btInvalid}
//
//public:
//                         CharacterMapGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode);
//
//    void                 Render() const;
//    void                 GetBuffer(BufferType type, ByteBuffer& buffer) const;
//};
//---------------------------------------------------------------------------
} // Visuals namespace
//---------------------------------------------------------------------------
#endif
