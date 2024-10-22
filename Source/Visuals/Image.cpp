//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Image.h"
#include "GraphicsBuffer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Visuals;
//---------------------------------------------------------------------------
std::unique_ptr<TBitmap> Image::m_Overlay = nullptr;
//---------------------------------------------------------------------------
Image::Image(unsigned int width, unsigned int height, const GraphicsMode& graphicsMode)
: m_Image(nullptr)
, m_IsMonochrome(false)
{
    GraphicsBuffer::Make(width, height, graphicsMode, m_Canvas);
}
//---------------------------------------------------------------------------
Image::Image(Project::ImageDocument const * const image, const Visuals::GraphicsMode& graphicsMode)
: m_Image(image)
, m_IsMonochrome(false)
{
    GraphicsBuffer::Make(image->Width, image->Height, graphicsMode, m_Canvas);
    Canvas().Set(image->Frame[0]);
    m_Bitmap = std::make_unique<TBitmap>();
    m_Bitmap->Width = image->Width;
    m_Bitmap->Height = image->Height;
    m_Bitmap->PixelFormat = pf32bit;
    m_Canvas->Draw(m_Bitmap.get());
    if (m_Overlay == nullptr)
    {
        m_Overlay = std::make_unique<TBitmap>();
        m_Overlay->PixelFormat = pf32bit;
        m_Overlay->Width = 1;
        m_Overlay->Height = 1;
    }
}
//---------------------------------------------------------------------------
GraphicsBuffer& Image::Canvas() const
{
    return *(m_Canvas.get());
}
//---------------------------------------------------------------------------
void Image::ChangeFrame(int frame)
{
    Canvas().Set(m_Image->Frame[frame]);
}
//---------------------------------------------------------------------------
void Image::Draw(const TPoint& pt, TBitmap* canvas, TColor overlayColor)
{
    if (overlayColor == clBlack)
    {
        if (m_IsMonochrome)
        {
            // restore image to color
            m_IsMonochrome = false;
            m_Canvas->Draw(m_Bitmap.get());
        }
        BitBlt(canvas->Canvas->Handle, pt.x, pt.y, m_Image->Width, m_Image->Height, m_Bitmap->Canvas->Handle, 0, 0, SRCCOPY);
    }
    else
    {
        if (!m_IsMonochrome)
        {
            // convert image to monochrome
            m_IsMonochrome = true;
            m_Canvas->Draw(m_Bitmap.get(), true);
        }
        BitBlt(canvas->Canvas->Handle, pt.x, pt.y, m_Image->Width, m_Image->Height, m_Bitmap->Canvas->Handle, 0, 0, SRCCOPY);
        // overlay the color
        BLENDFUNCTION bfn;
        bfn.BlendOp = AC_SRC_OVER;
        bfn.BlendFlags = 0;
        bfn.SourceConstantAlpha = 128;
        bfn.AlphaFormat = 0;
        ((TColor*)m_Overlay->ScanLine[0])[0] = overlayColor;
        AlphaBlend(canvas->Canvas->Handle, pt.x, pt.y, m_Image->Width, m_Image->Height, m_Overlay->Canvas->Handle, 0, 0, 1, 1, bfn);
    }
}
//---------------------------------------------------------------------------
std::vector<unsigned char> Image::GetExportNativeFormat() const
{
    return m_Canvas->GetNative(m_Image->ImageType);
}
//---------------------------------------------------------------------------

