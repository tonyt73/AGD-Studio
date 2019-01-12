//---------------------------------------------------------------------------
#ifndef GraphicsBufferH
#define GraphicsBufferH
//---------------------------------------------------------------------------
#include "Graphics/GraphicsTypes.h"
#include "Graphics/GraphicsMode.h"
//---------------------------------------------------------------------------
// Pixel Masks for 1, 2, 4 and 8 pixels per byte
extern const unsigned char* g_PixelMasks[];
extern const unsigned char* g_PixelShfts[];
//---------------------------------------------------------------------------
namespace Agdx
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
                        __fastcall  GraphicsBuffer() = delete;
protected:
    typedef std::vector<ByteBuffer> Buffers;

    const Agdx::GraphicsMode&       m_GraphicsMode;     // the graphic mode definition
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
 std::unique_ptr<Graphics::TBitmap> m_Bitmap;           // the Windows bitmap we render to
    bool                            m_RenderInGreyscale;// flag: Indicates we render in greyscale
    bool                            m_Drawing;          // flag: Indicates we are drawing pixels; don't render immediately

                        __fastcall  GraphicsBuffer(unsigned int width, unsigned int height, const Agdx::GraphicsMode& mode);
    void                __fastcall  PushBuffer(unsigned int size);
    unsigned int        __fastcall  GetNumberOfBuffers() const;
    unsigned int        __fastcall  GetSizeOfBuffer(int index) const;
  virtual unsigned char __fastcall  GetColorIndex(unsigned char index) const;
  virtual void          __fastcall  SetColorIndex(unsigned char index, int logicalIndex);
    void                __fastcall  SetRenderInGreyscale(bool value);
    unsigned char       __fastcall  RemapPixel(unsigned char pixel) const;
    virtual void        __fastcall  Render() const = 0;

public:
    virtual             __fastcall ~GraphicsBuffer();

                                    // Make a suitable buffer for the buffer type
    static void         __fastcall  Make(unsigned int width, unsigned int height, const Agdx::GraphicsMode& mode, std::unique_ptr<GraphicsBuffer>& buffer);
                                    // sets the pixel to the specified palette color index
    virtual void        __fastcall  SetPixel(unsigned int X, unsigned int Y, bool set = true) = 0;
                                    // retrieves the pixel color at the position specified
    virtual void        __fastcall  GetColor(unsigned int X, unsigned int Y, unsigned char colorIndex = 0) = 0;
                                    // Retrieves the specified buffer index from the graphics buffer
    void                __fastcall  GetBuffer(int index, ByteBuffer& buffer) const;
std::vector<unsigned char>          // Get the native byte data for the buffer
                        __fastcall  GetNative(ImageTypes type) const;
                                    // Get the hex data of the image
    String              __fastcall  Get() const;
                                    // Set the bitmap data from the hex data
    virtual void        __fastcall  Set(const String& data) = 0;
                                    // Copy the image onto the bitmap
    void                __fastcall  Draw(TBitmap* bitmap) const;
                                    // Copy the image bitmap onto the destination bitmap
    void                __fastcall  Assign(TBitmap* bitmap) const;
                                    // Begin drawing operations on the canvas
    void                __fastcall  Begin();
                                    // End drawing operations on the canvas
    void                __fastcall  End();

    // Properties
                                    // Dimensions
    unsigned int        __property  Width  = { read = m_Width  };
    unsigned int        __property  Height = { read = m_Height };
    unsigned int        __property  ScalarX = { read = m_ScalarX };
    unsigned int        __property  ScalarY = { read = m_ScalarY };
                                    // Color
    unsigned char       __property  Color[unsigned char index] = { read = GetColorIndex, write = SetColorIndex };
                                    // Buffer info (used by image tools)
    BufferType          __property  BufferType = { read = m_BufferType };
    unsigned int        __property  NumberOfBuffers = { read = GetNumberOfBuffers };
    unsigned int        __property  SizeOfBuffer[int index] = { read = GetSizeOfBuffer };
    bool                __property  RenderInGreyscale = { read = m_RenderInGreyscale, write = SetRenderInGreyscale };
};
//---------------------------------------------------------------------------
// TODO: To be implemented if MSX support is added
//class CharacterMapGraphicsBuffer : public GraphicsBuffer
//{
//private:
//
//    BufferType          __fastcall  GetBufferType(int index) { return btInvalid}
//
//public:
//                        __fastcall  CharacterMapGraphicsBuffer(unsigned int width, unsigned int height, const Agdx::GraphicsMode& mode);
//
//    void                __fastcall  Render() const;
//    void                __fastcall  GetBuffer(BufferType type, ByteBuffer& buffer) const;
//};
//---------------------------------------------------------------------------
}   // agdx
#endif
