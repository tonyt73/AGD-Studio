//---------------------------------------------------------------------------
#ifndef BitmapGraphicsBufferH
#define BitmapGraphicsBufferH
//---------------------------------------------------------------------------
#include "GraphicsBuffer.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
namespace Visuals
{
//---------------------------------------------------------------------------
// A paletted bitmap buffer has pixels defined as a color value stored in a byte.
// This buffer supports 1 bit (monochrome) to 2, 4 or 8 bits per colour.
//---------------------------------------------------------------------------
class BitmapGraphicsBuffer : public GraphicsBuffer
{
private:
    Registrar   m_Registrar;
    void        OnEvent(const Event& event);
public:
                BitmapGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode);
               ~BitmapGraphicsBuffer();

    void        SetPixel(unsigned int X, unsigned int Y, bool set);
    void        GetColor(unsigned int X, unsigned int Y, unsigned char colorIndex = 0);
    void        Render() const;
    void        Set(const String& data);
};
//---------------------------------------------------------------------------
} // Visuals namespace
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
