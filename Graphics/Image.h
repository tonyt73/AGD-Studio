//---------------------------------------------------------------------------
#ifndef ImageH
#define ImageH
//---------------------------------------------------------------------------
#include <memory>
#include "Graphics/GraphicsBuffer.h"
#include "Project/ImageDocuments.h"
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
    ImageDocument const * const     m_Image;
    std::unique_ptr<TBitmap>        m_Bitmap;

public:
                    __fastcall  Image(unsigned int width, unsigned int height, const Agdx::GraphicsMode& graphicsMode);
                    __fastcall  Image(ImageDocument const * const image, const Agdx::GraphicsMode& graphicsMode);

    void            __fastcall  ChangeFrame(int frame);
    GraphicsBuffer& __fastcall  Canvas() const;
    void            __fastcall  Draw(const TPoint& pt, TBitmap* canvas) const;
};
typedef std::vector<std::unique_ptr<Image>> ImageList;
typedef std::map<unsigned int, std::unique_ptr<Image>> ImageMap;
//---------------------------------------------------------------------------
}   // agdx
#endif
