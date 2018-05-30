//---------------------------------------------------------------------------
#ifndef ImageH
#define ImageH
//---------------------------------------------------------------------------
#include <memory>
#include "Graphics/GraphicsBuffer.h"
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
    std::unique_ptr<GraphicsBuffer> m_Canvas;

public:
                    __fastcall  Image(unsigned int width, unsigned int height, const Agdx::GraphicsMode& graphicsMode);
    GraphicsBuffer& __fastcall  Canvas() const;
};
//---------------------------------------------------------------------------
}   // agdx
#endif
