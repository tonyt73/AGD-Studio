//---------------------------------------------------------------------------
#ifndef ImageH
#define ImageH
//---------------------------------------------------------------------------
#include "GraphicsBuffer.h"
#include "Project/ImageDocument.h"
//---------------------------------------------------------------------------
namespace Visuals
{
//---------------------------------------------------------------------------
// Image
// A machine independent bitmap representation
// We store ordered pixel data based on bitsPerPixel and buffer type (bitmap vs attribute)
//---------------------------------------------------------------------------
class Image
{
private:
    std::unique_ptr<GraphicsBuffer>         m_Canvas;
    Project::ImageDocument const* const     m_Image;
    std::unique_ptr<TBitmap>                m_Bitmap;
    static std::unique_ptr<TBitmap>         m_Overlay;
    bool                                    m_IsMonochrome;

public:
                                __fastcall  Image(unsigned int width, unsigned int height, const Visuals::GraphicsMode& graphicsMode);
                                __fastcall  Image(Project::ImageDocument const * const image, const Visuals::GraphicsMode& graphicsMode);

    void                        __fastcall  ChangeFrame(int frame);
    GraphicsBuffer&             __fastcall  Canvas() const;
    void                        __fastcall  Draw(const TPoint& pt, TBitmap* canvas, TColor overlayColor = clBlack);
    std::vector<unsigned char>  __fastcall  GetExportNativeFormat() const;
};
//---------------------------------------------------------------------------
typedef std::vector<std::unique_ptr<Image>> ImageList;
typedef std::map<unsigned int, std::unique_ptr<Image>> ImageMap;
//---------------------------------------------------------------------------
} // Visuals namespace
//---------------------------------------------------------------------------
#endif
