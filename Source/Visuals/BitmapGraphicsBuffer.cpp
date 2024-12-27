//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "BitmapGraphicsBuffer.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Visuals;
//---------------------------------------------------------------------------
__fastcall BitmapGraphicsBuffer::BitmapGraphicsBuffer(unsigned int width, unsigned int height, const GraphicsMode& mode)
: GraphicsBuffer(width, height, mode)
{
    assert(mode.BitsPerPixel == 1 || mode.BitsPerPixel == 2 || mode.BitsPerPixel == 4 || mode.BitsPerPixel == 8);
    // allocate the buffer
    // m_Buffers[0] : pixels buffer
    PushBuffer(m_Stride * height);
    m_SetColors.push_back(1);
    m_SetColors.push_back(0);

    m_Registrar.Subscribe<Event>(_FnBind(BitmapGraphicsBuffer::OnEvent));
}
//---------------------------------------------------------------------------
void __fastcall BitmapGraphicsBuffer::SetPixel(unsigned int X, unsigned int Y, bool set)
{
    if (X < m_Width && Y < m_Height) {
        auto ix = X / m_PixelsPerByte;
        auto pixelOffset = (Y * m_Stride) + ix;
        auto pixelPos = X % m_PixelsPerByte;
        auto pixel = m_SetColors[set ? 0 : 1] << g_PixelShfts[m_GraphicsMode.BitsPerPixel][pixelPos];
        // reset the pixel bits
        m_Buffers[0][pixelOffset] &= ~g_PixelMasks[m_GraphicsMode.BitsPerPixel][pixelPos];
        // set the new color
        m_Buffers[0][pixelOffset] |= pixel;
        Render();
    }
}
//---------------------------------------------------------------------------
void __fastcall BitmapGraphicsBuffer::GetColor(unsigned int X, unsigned int Y, unsigned char colorIndex)
{
    if (X < m_Width && Y < m_Height) {
        auto ix = X / m_PixelsPerByte;
        auto pixelOffset = (Y * m_Stride) + ix;
        auto pixelPos = X % m_PixelsPerByte;
        // get the color index at the position in the byte
        auto color = m_Buffers[0][pixelOffset] & ~g_PixelMasks[m_GraphicsMode.BitsPerPixel][pixelPos];
        // shift down into a color index
        color >>= g_PixelShfts[m_GraphicsMode.BitsPerPixel][pixelPos];
        m_SetColors[colorIndex] = static_cast<unsigned char>(color);
    }
}
//---------------------------------------------------------------------------
void __fastcall BitmapGraphicsBuffer::Render() const
{
    if (m_Drawing) return;
    for (auto y = 0; y < m_Height; y++) {
        for (auto x = 0; x < m_Width; x += m_PixelsPerByte) {
            auto ix = x / m_PixelsPerByte;
            auto pixels = m_Buffers[0][(y * m_Stride) + ix];
            for (auto i = 0; i < m_PixelsPerByte; i++) {
                unsigned char logicalColor = (pixels & g_PixelMasks[m_GraphicsMode.BitsPerPixel][i]) >> g_PixelShfts[m_GraphicsMode.BitsPerPixel][i];
                unsigned char physicalColor = m_GraphicsMode.FromLogicalColor[logicalColor];
                m_Bitmap->Canvas->Pixels[x+i][y] = m_RenderInGreyscale ? m_GraphicsMode.Palette().Greyscale[physicalColor] : m_GraphicsMode.Palette().Color[physicalColor];
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall BitmapGraphicsBuffer::Set(const String& data)
{
    if (data.Length() / 2 == SizeOfBuffer[0]) {
        // convert hex to byte
        for (auto i = 0; i < SizeOfBuffer[0]; i++) {
            auto byte = static_cast<unsigned char>(StrToInt("0x" + data.SubString(1 + i * 2, 2)));
            m_Buffers[0][i] = byte;
        }
        Render();
    }
}
//---------------------------------------------------------------------------
void __fastcall BitmapGraphicsBuffer::OnEvent(const Event& event)
{
    if (event.Id == "palette.remapped") {
        Render();
    }
}
//---------------------------------------------------------------------------
