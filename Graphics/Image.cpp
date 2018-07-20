//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Image.h"
#include "GraphicsBuffer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace Agdx;
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
}
//---------------------------------------------------------------------------
GraphicsBuffer& __fastcall Image::Canvas() const
{
    return *(m_Canvas.get());
}
//---------------------------------------------------------------------------
void __fastcall Image::ChangeFrame(int frame)
{
    Canvas().Set(m_Image->Frame[0]);
}
//---------------------------------------------------------------------------
