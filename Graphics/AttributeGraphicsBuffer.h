//---------------------------------------------------------------------------
#ifndef AttributeGraphicsBufferH
#define AttributeGraphicsBufferH
//---------------------------------------------------------------------------
#include "Graphics/GraphicsBuffer.h"
//---------------------------------------------------------------------------
namespace Agdx
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
    unsigned char       m_iInk;
    unsigned char       m_iPaper;
    unsigned char       m_iBright;
    unsigned char       m_iFlash;

                void    __fastcall  SetInk   (unsigned char iInk);
                void    __fastcall  SetPaper (unsigned char iPaper);
                void    __fastcall  SetFlash (unsigned char iFlash);
                void    __fastcall  SetBright(unsigned char iBright);

public:
                        __fastcall  AttributeGraphicsBuffer(unsigned int width, unsigned int height, const Agdx::GraphicsMode& mode);
                        __fastcall ~AttributeGraphicsBuffer();

    void                __fastcall  SetPixel(unsigned int X, unsigned int Y, bool set);
    void                __fastcall  GetColor(unsigned int X, unsigned int Y, ColorIndex colorIndex = ciPrimary);
    void                __fastcall  Render() const;
    void                __fastcall  Set(const String& data);

    __property  unsigned char       Ink     = { read = m_iInk           , write = SetInk    };
    __property  unsigned char       Paper   = { read = m_iPaper         , write = SetPaper  };
    __property  unsigned char       Bright  = { read = m_iBright        , write = SetBright };
    __property  unsigned char       Flash   = { read = m_iFlash         , write = SetFlash  };
};
//---------------------------------------------------------------------------
}   // agdx
#endif
