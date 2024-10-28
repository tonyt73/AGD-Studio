//---------------------------------------------------------------------------
#ifndef AttributeGraphicsBufferH
#define AttributeGraphicsBufferH
//---------------------------------------------------------------------------
#include "GraphicsBuffer.h"
//---------------------------------------------------------------------------
namespace Visuals
{
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
private:
public:
            __fastcall  AttributeGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode);
            __fastcall ~AttributeGraphicsBuffer();

    void    __fastcall  SetPixel(unsigned int X, unsigned int Y, bool set);
    void    __fastcall  GetColor(unsigned int X, unsigned int Y, unsigned char colorIndex = 0);
    void    __fastcall  Render() const;
    void    __fastcall  Set(const String& data);
};
//---------------------------------------------------------------------------
} // Visuals namespace
//---------------------------------------------------------------------------
#endif
