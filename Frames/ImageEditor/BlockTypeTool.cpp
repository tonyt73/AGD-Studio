//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include <vcl.graphics.hpp>
#include "BlockTypeTool.h"
#include "BlockColors.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall BlockTypeTool::BlockTypeTool()
: m_ImageDocument(nullptr)
, m_BlockType(1)
{
    m_CanvasBitmap = std::make_unique<Graphics::TBitmap>();
    m_CanvasBitmap->PixelFormat = pf32bit;
    m_BlendedBitmap = std::make_unique<Graphics::TBitmap>();
    m_BlendedBitmap->PixelFormat = pf32bit;
}
//---------------------------------------------------------------------------
TPoint __fastcall BlockTypeTool::PtToBlock(const TPoint& pt) const
{
    TPoint bpt;
    bpt.X = pt.X / m_BlockWidth;
    bpt.Y = pt.Y / m_BlockHeight;
    return bpt;
}
//---------------------------------------------------------------------------
String __fastcall BlockTypeTool::Begin(Agdx::GraphicsBuffer& canvas)
{
    m_CanvasBitmap->Width = m_ImageDocument->Width;
    m_CanvasBitmap->Height = m_ImageDocument->Height;
    m_BlendedBitmap->Width = m_ImageDocument->Width;
    m_BlendedBitmap->Height = m_ImageDocument->Height;
    canvas.Assign(m_CanvasBitmap.get());

    m_Blocks = m_ImageDocument->GetLayer("blocktype");
    m_BlockWidth = 8 / canvas.ScalarX;
    m_BlockHeight = 8 / canvas.ScalarY;
    m_BlocksAcross = m_ImageDocument->Width / m_BlockWidth;
    m_BlocksDown = m_ImageDocument->Height / m_BlockHeight;

    if (m_Blocks.Length() != m_BlocksAcross * m_BlocksDown)
    {
        m_Blocks = String::StringOfChar('0', m_BlocksAcross * m_BlocksDown);
    }
    Apply();

    return m_Blocks;
}
//---------------------------------------------------------------------------
void __fastcall BlockTypeTool::Move(const TPoint& pt, const TShiftState& buttons)
{
    if (buttons.Contains(ssLeft) || buttons.Contains(ssRight))
    {
        auto bpt = PtToBlock(pt);
        auto offset = bpt.Y * m_BlocksAcross + bpt.X;
        m_Blocks[offset+1] = buttons.Contains(ssLeft) ? '0' + m_BlockType : '0';
        Apply();
    }
}
//---------------------------------------------------------------------------
String __fastcall BlockTypeTool::End()
{
    m_ImageDocument->SetLayer("blocktype", m_Blocks);
    return m_Blocks;
}
//---------------------------------------------------------------------------
void __fastcall BlockTypeTool::Apply()
{
    const auto maskAlpha = 0.75f;
    // copy the canvas bitmap
    m_BlendedBitmap->Assign(m_CanvasBitmap.get());
    // blend the tile types colors over the canvas bitmap
    unsigned int R = 0;
    unsigned int G = 0;
    unsigned int B = 0;
    for (auto d = 0; d < m_BlocksDown; d++)
    {
        for (auto a = 0; a < m_BlocksAcross; a++)
        {
            auto index = d * m_BlocksAcross + a;
            auto type = m_Blocks[index+1]- '0';
            if (type)
            {
                auto mC = g_BlockColors[type];       // mask color
                auto mR = (float)((mC & 0x000000FF)      ) * maskAlpha;
                auto mG = (float)((mC & 0x0000FF00) >>  8) * maskAlpha;
                auto mB = (float)((mC & 0x00FF0000) >> 16) * maskAlpha;
                auto alpha = 1.f - maskAlpha;
                auto y = d * m_BlockHeight;
                for (auto h = 0; h < m_BlockHeight; h++)
                {
                    auto x = a * m_BlockWidth;
                    for (auto w = 0; w < m_BlockWidth; w++)
                    {
                        auto cc = ColorToRGB(m_BlendedBitmap->Canvas->Pixels[x+w][y+h]);    // canvas color
                        auto pR = (float)((cc & 0x000000FF)      ) * alpha;
                        auto pG = (float)((cc & 0x0000FF00) >>  8) * alpha;
                        auto pB = (float)((cc & 0x00FF0000) >> 16) * alpha;
                        R = pR + mR;
                        G = pG + mG;
                        B = pB + mB;
                        m_BlendedBitmap->Canvas->Pixels[x+w][y+h] = (TColor)(R + (G << 8) + (B << 16));
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall BlockTypeTool::Draw(TBitmap* bitmap) const
{
    StretchBlt(bitmap->Canvas->Handle, 0, 0, bitmap->Width, bitmap->Height, m_BlendedBitmap->Canvas->Handle, 0, 0, m_BlendedBitmap->Width, m_BlendedBitmap->Height, SRCCOPY);
}
//---------------------------------------------------------------------------
