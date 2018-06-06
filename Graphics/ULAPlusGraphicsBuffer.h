//---------------------------------------------------------------------------
#ifndef AttributeGraphicsBufferH
#define AttributeGraphicsBufferH
//---------------------------------------------------------------------------
#include "Graphics/GraphicsBuffer.h"
//---------------------------------------------------------------------------
namespace Agdx
{
//---------------------------------------------------------------------------
// ZX Spectrum ULA+ graphics buffer
// Used by ZX Spectrum, ZX Spectrum Next
// Attributes are:
// bit 7, 6     - palette index
// bits 5,4,3   - paper
// bits 2,1,0   - ink
// attributes can be 8x8 or 8x1
// palette:
//  4 x 16 color palettes
//  each palette is 8 ink and 8 paper colours from 256 colours
//---------------------------------------------------------------------------
class ULAPlusGraphicsBuffer : public GraphicsBuffer
{
private:
public:
                        __fastcall  ULAPlusGraphicsBuffer(unsigned int width, unsigned int height, const Agdx::GraphicsMode& mode);
                        __fastcall ~ULAPlusGraphicsBuffer();

                void    __fastcall  SetPixel(unsigned int X, unsigned int Y, bool set);
                void    __fastcall  GetColor(unsigned int X, unsigned int Y, unsigned char colorIndex = 0);
                void    __fastcall  Render() const;
                void    __fastcall  Set(const String& data);
};
//---------------------------------------------------------------------------
}   // agdx
#endif
