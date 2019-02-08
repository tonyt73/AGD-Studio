//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Image.h"
#include "GraphicsBuffer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Agdx;
//---------------------------------------------------------------------------
std::unique_ptr<TBitmap> Image::m_Overlay = nullptr;
//---------------------------------------------------------------------------
__fastcall Image::Image(unsigned int width, unsigned int height, const GraphicsMode& graphicsMode)
: m_Image(nullptr)
{
    GraphicsBuffer::Make(width, height, graphicsMode, m_Canvas);
}
//---------------------------------------------------------------------------
__fastcall Image::Image(ImageDocument const * const image, const Agdx::GraphicsMode& graphicsMode)
: m_Image(image)
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
GraphicsBuffer& __fastcall Image::Canvas() const
{
    return *(m_Canvas.get());
}
//---------------------------------------------------------------------------
void __fastcall Image::ChangeFrame(int frame)
{
    Canvas().Set(m_Image->Frame[frame]);
}
//---------------------------------------------------------------------------
void __fastcall Image::Draw(const TPoint& pt, TBitmap* canvas, TColor overlayColor) const
{
    BitBlt(canvas->Canvas->Handle, pt.x, pt.y, m_Image->Width, m_Image->Height, m_Bitmap->Canvas->Handle, 0, 0, SRCCOPY);
    if (overlayColor != clBlack)
    {
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
std::vector<unsigned char> __fastcall Image::GetExportNativeFormat() const
{
    return m_Canvas->GetNative(m_Image->ImageType);
}
//---------------------------------------------------------------------------

