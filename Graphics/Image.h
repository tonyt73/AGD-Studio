//---------------------------------------------------------------------------
#ifndef ImageH
#define ImageH
//---------------------------------------------------------------------------
#include <memory>
#include "Graphics/GraphicsBuffers.h"
//---------------------------------------------------------------------------
namespace Agdx
{
//---------------------------------------------------------------------------
// Image
// A machine independent bitmap representation
// We store ordered pixel data based on bitsPerPixel and buffer type (bitmap vs attribute)
//---------------------------------------------------------------------------
class Image
{
private:
    std::unique_ptr<GraphicsBuffer> m_GraphicsBuffer;
public:
            __fastcall  Image(unsigned int width, unsigned int height, const Agdx::GraphicsMode& graphicsMode);
    void    __fastcall  Set(const String& frameData);
    String  __fastcall  Get() const;
    void    __fastcall  SetPixel(unsigned int X, unsigned int Y, unsigned char color);
};
//---------------------------------------------------------------------------
}   // agdx
#endif
