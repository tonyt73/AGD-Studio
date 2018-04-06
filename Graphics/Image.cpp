//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Image.h"
#include "GraphicsBuffers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Image::Image(unsigned int width, unsigned int height, const GraphicsMode& graphicsMode)
{
    GraphicsBuffer::Make(width, height, graphicsMode, m_GraphicsBuffer);
}
//---------------------------------------------------------------------------
void __fastcall Image::SetPixel(unsigned int X, unsigned int Y, unsigned char color)
{
}
//---------------------------------------------------------------------------
