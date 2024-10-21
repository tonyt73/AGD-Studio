//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "CanvasTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CanvasTool::CanvasTool()
: Tool()
{
}
//---------------------------------------------------------------------------
__fastcall CanvasTool::~CanvasTool()
{
}
//---------------------------------------------------------------------------
void __fastcall CanvasTool::DrawLine(Visuals::GraphicsBuffer& canvas, const TRect& Rect, bool set, LinePositions* list)
{
    auto dx = 1;
    auto dy = 1;
    auto px = Rect.Left;
    auto py = Rect.Top;

    auto yDiff = Rect.Bottom - Rect.Top;
    if (yDiff < 0)
    {
        yDiff = -yDiff;
        dy = -1;
    }

    auto xDiff = Rect.Right - Rect.Left;
    if (xDiff < 0)
    {
        xDiff = -xDiff;
        dx = -1;
    }

    auto error = 0;
    if (xDiff > yDiff)
    {
        // inc x by 1, y by dy
        for (auto i = 0; i <= xDiff; ++i)
        {
            auto pt = TPoint(px, py);
            if (IsPointValid(pt))
            {
                if (list != nullptr)
                {
                    list->push_back(pt);
                }
                canvas.SetPixel(px, py, set);
            }
            px += dx;
            error += yDiff;
            if (error >= xDiff)
            {
                error -= xDiff;
                py += dy;
            }
        }
    }
    else
    {
        // inc y by 1, x by dx
        for (auto i = 0; i <= yDiff; ++i)
        {
            auto pt = TPoint(px, py);
            if (IsPointValid(pt))
            {
                if (list != nullptr)
                {
                    list->push_back(pt);
                }
                canvas.SetPixel(px, py, set);
            }
            py += dy;
            error += xDiff;
            if (error >= yDiff)
            {
                error -= yDiff;
                px += dx;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasTool::DrawVLine(Visuals::GraphicsBuffer& canvas, int x, int ys, int ye, bool set)
{
    for (auto y = std::min(ys, ye); y <= std::max(ys, ye); y++)
    {
        canvas.SetPixel(x, y, set);
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasTool::DrawHLine(Visuals::GraphicsBuffer& canvas, int xs, int xe, int y, bool set)
{
    for (auto x = std::min(xs, xe); x <= std::max(xs, xe); x++)
    {
        canvas.SetPixel(x, y, set);
    }
}
//---------------------------------------------------------------------------
String __fastcall CanvasTool::Begin(Visuals::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons)
{
    Width = canvas.Width;
    Height = canvas.Height;
    Tool::Begin(pt, buttons);
    Apply(canvas, pt);
    m_Image = canvas.Get();
    return m_Image;
}
//---------------------------------------------------------------------------
void __fastcall CanvasTool::Move(Visuals::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons)
{
    if (!IsDrawing) return;
    if (Flags & resetOnMove)
    {
        // restore the canvas
        canvas.Set(m_Image);
    }
    canvas.Begin();
    Apply(canvas, pt);
    canvas.End();
    Tool::Move(pt, buttons);
}
//---------------------------------------------------------------------------
String __fastcall CanvasTool::End(Visuals::GraphicsBuffer& canvas, const TPoint& pt)
{
    if (pt != LastPt)
    {
        Apply(canvas, pt);
    }
    Tool::End(pt);
    return canvas.Get();
}
//---------------------------------------------------------------------------

