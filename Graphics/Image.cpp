//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Image.h"
#include "GraphicsBuffers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace Agdx;
//---------------------------------------------------------------------------
__fastcall Image::Image(unsigned int width, unsigned int height, const GraphicsMode& graphicsMode)
{
    GraphicsBuffer::Make(width, height, graphicsMode, m_GraphicsBuffer);
}
//---------------------------------------------------------------------------
void __fastcall Image::Set(const String& frameData)
{

}
//---------------------------------------------------------------------------
String __fastcall Image::Get() const
{
    return "";
}
//---------------------------------------------------------------------------
GraphicsBuffer& __fastcall Image::Canvas() const
{
    return *(m_GraphicsBuffer.get());
}
//---------------------------------------------------------------------------
