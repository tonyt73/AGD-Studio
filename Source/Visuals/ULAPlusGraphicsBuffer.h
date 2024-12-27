//---------------------------------------------------------------------------
#ifndef ULAPlusGraphicsBufferH
#define ULAPlusGraphicsBufferH
//---------------------------------------------------------------------------
#include "GraphicsBuffer.h"
//---------------------------------------------------------------------------
namespace Visuals
{
//---------------------------------------------------------------------------
// ZX Spectrum ULA+ graphics buffer
// Used by ZX Spectrum, ZX Spectrum Next
// Attributes are:
// bits 7, 6    - palette index
// bits 5,4,3   - paper
// bits 2,1,0   - ink
// attributes can be 8x8 or 8x1
// palette:
//  4 x 16 color palettes
//  each palette is 8 ink and 8 paper colours from 256 colours
// The 4x16(64) palette entries are stored as 8bit RGB colours;
// basically indexes into the 24bit RGB CLUT
//---------------------------------------------------------------------------
class ULAPlusGraphicsBuffer : public GraphicsBuffer
{
private:
    void        __fastcall  OnEvent(const Event& event);
public:
                __fastcall  ULAPlusGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode);

    void        __fastcall  SetPixel(unsigned int X, unsigned int Y, bool set) override;
    void        __fastcall  GetColor(unsigned int X, unsigned int Y, unsigned char colorIndex = 0) override;
    void        __fastcall  Render() const override;
    void        __fastcall  Set(const String& data) override;

    bool        __fastcall  CanExport(int layer, ImageTypes ofType) const;
};
//---------------------------------------------------------------------------
} // Visuals namespace
//---------------------------------------------------------------------------
#endif
