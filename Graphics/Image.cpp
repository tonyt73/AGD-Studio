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
std::unique_ptr<TBitmap> Image::m_Selection = nullptr;
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
    if (m_Selection == nullptr)
    {
        m_Selection = std::make_unique<TBitmap>();
        m_Selection->PixelFormat = pf32bit;
        m_Selection->Width = 1;
        m_Selection->Height = 1;
        ((TColor*)m_Selection->ScanLine[0])[0] = (TColor)0x7F00FF00;
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
void __fastcall Image::Draw(const TPoint& pt, TBitmap* canvas, bool selected) const
{
    BitBlt(canvas->Canvas->Handle, pt.x, pt.y, m_Image->Width, m_Image->Height, m_Bitmap->Canvas->Handle, 0, 0, SRCCOPY);
    if (selected)
    {
        BLENDFUNCTION bfn;
        bfn.BlendOp = AC_SRC_OVER;
        bfn.BlendFlags = 0;
        bfn.SourceConstantAlpha = 128;
        bfn.AlphaFormat = 0;
        AlphaBlend(canvas->Canvas->Handle, pt.x, pt.y, m_Image->Width, m_Image->Height, m_Selection->Canvas->Handle, 0, 0, 1, 1, bfn);
    }
}
//---------------------------------------------------------------------------
std::vector<unsigned char> __fastcall Image::GetExportNativeFormat() const
{
    return m_Canvas->GetNative(m_Image->ImageType);
}
//---------------------------------------------------------------------------

