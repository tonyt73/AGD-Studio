//---------------------------------------------------------------------------
#ifndef GraphicsBuffersH
#define GraphicsBuffersH
//---------------------------------------------------------------------------
#include "Graphics/GraphicsTypes.h"
#include "Graphics/GraphicsMode.h"
//---------------------------------------------------------------------------
enum ColorIndex { ciPrimary, ciSecondary };
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
    typedef std::vector<UnsignedCharBuffer> Buffers;

    GraphicsMode                    m_GraphicsMode;     // the graphic mode definition
    unsigned int                    m_Width;            // the width of the buffer in pixels
    unsigned int                    m_Height;           // the height of the buffer in pixels
    unsigned int                    m_Stride;           // the stride of the buffer in bytes
    unsigned int                    m_PixelsPerByte;    // the number of pixel per bytes (inv of bits / pixels)
    unsigned int                    m_NumberOfBuffers;  // the number of data buffers using by this buffer type
    Buffers                         m_Buffers;          // the list of buffers
    BufferType                      m_BufferType;       // the type of graphics buffer this is
    unsigned char                   m_SetColors[2];     // the primary[0] and secondary[1] colors used to set/unset pixels

                        __fastcall  GraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode);
    void                __fastcall  PushBuffer(unsigned int size);
    unsigned int        __fastcall  GetNumberOfBuffers() const;
    unsigned char       __fastcall  GetColorIndex(ColorIndex index) const;
    void                __fastcall  SetColorIndex(ColorIndex index, int colorIndex);

public:
    virtual             __fastcall ~GraphicsBuffer();

                                    // Make a suitable buffer for the buffer type
    static void         __fastcall  Make(unsigned int width, unsigned int height, const GraphicsMode& mode, std::unique_ptr<GraphicsBuffer>& buffer);
                                    // sets the pixel to the specified palette color index
    virtual void        __fastcall  SetPixel(unsigned int X, unsigned int Y, bool set) = 0;
                                    // retrieves the pixel color at the position specified
  virtual unsigned char __fastcall  GetColor(unsigned int X, unsigned int Y) const = 0;
                                    // Retrieves the specified buffer index from the graphics buffer
    void                __fastcall  GetBuffer(int index, UnsignedCharBuffer& buffer) const;
                                    // Render the graphics buffer to the bitmap
    virtual void        __fastcall  Render(TBitmap* bitmap, bool inGreyscale) const = 0;

    unsigned int        __property  Width  = { read = m_Width  };
    unsigned int        __property  Height = { read = m_Height };
    BufferType          __property  BufferType = { read = m_BufferType };
    unsigned int        __property  NumberOfBuffers = { read = GetNumberOfBuffers };
    unsigned char       __property  Color[ColorIndex index] = { read = GetColorIndex, write = SetColorIndex };
};
//---------------------------------------------------------------------------
// A paletted bitmap buffer has pixels defined as a color value stored in a byte.
// This buffer supports 1 bit (monochrome) to 2, 4 or 8 bits per colour.
//
//---------------------------------------------------------------------------
class BitmapGraphicsBuffer : public GraphicsBuffer
{
public:
                        __fastcall  BitmapGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode);
                        __fastcall ~BitmapGraphicsBuffer();

    void                __fastcall  SetPixel(unsigned int X, unsigned int Y, bool set);
    unsigned char       __fastcall  GetColor(unsigned int X, unsigned int Y) const;
    void                __fastcall  Render(TBitmap* bitmap, bool inGreyscale) const;
};
//---------------------------------------------------------------------------
// ZX Spectrum style attribute graphics buffer
// Used by ZX Spectrum, Timex, Sam Coupe, Enterprise 64
// Attributes are:
// bit 7        - flash
// bit 6        - bright
// bits 5,4,3   - paper
// bits 2,1,0   - ink
// attributes can be 8x8 or 8x1
//---------------------------------------------------------------------------
class AttributeGraphicsBuffer : public GraphicsBuffer
{
public:
                        __fastcall  AttributeGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode);
                        __fastcall ~AttributeGraphicsBuffer();

    void                __fastcall  SetPixel(unsigned int X, unsigned int Y, bool set);
    unsigned char       __fastcall  GetColor(unsigned int X, unsigned int Y) const;
    void                __fastcall  Render(TBitmap* bitmap, bool inGreyscale) const;
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
//                        __fastcall  CharacterMapGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode);
//
//    void                __fastcall  Render(TBitmap* bitmap, bool inGreyscale) const;
//    void                __fastcall  GetBuffer(BufferType type, UnsignedCharBuffer& buffer) const;
//};
//---------------------------------------------------------------------------
#endif
