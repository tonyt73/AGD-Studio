//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
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
void __fastcall CanvasTool::DrawLine(Visuals::GraphicsBuffer& canvas, const TRect& Rect, bool set, eSavePoints savePoints)
{
    if (savePoints == spLeft) {
        // we always draw the left edge and then the right edge, so clear the list of left
        m_LinePositions.clear();
    }

    // Save points are Left to Right only. Function calls MUST start with spLeft, then spRight!
    assert(!(savePoints == spRight && m_LinePositions.size() == 0));

    auto px = Rect.Left;
    auto xDiff = Rect.Right  - Rect.Left;
    auto dx = xDiff >= 0 ? 1 : -1;
    xDiff = std::abs(xDiff);

    auto py = Rect.Top;
    auto yDiff = Rect.Bottom - Rect.Top;
    auto dy = yDiff >= 0 ? 1 : -1;
    yDiff = std::abs(yDiff);

    auto error = 0;
    if (xDiff > yDiff) {
        // inc x by 1, y by dy
        for (auto i = 0; i <= xDiff; ++i) {
            auto pt = TPoint(px, py);
            if (IsPointValid(pt)) {
                if (savePoints == spLeft) {
                    m_LinePositions.push_back(TRect(px, py, px, py));
                } else if (savePoints == spRight) {
                    m_LinePositions[i].Right = px;
                }
                canvas.SetPixel(px, py, set);
            }
            px += dx;
            error += yDiff;
            if (error >= xDiff) {
                error -= xDiff;
                py += dy;
            }
        }
    } else {
        // inc y by 1, x by dx
        for (auto i = 0; i <= yDiff; ++i) {
            auto pt = TPoint(px, py);
            if (IsPointValid(pt)) {
                if (savePoints == spLeft) {
                    m_LinePositions.push_back(TRect(px, py, px, py));
                } else if (savePoints == spRight) {
                    m_LinePositions[i].Right = px;
                }
                canvas.SetPixel(px, py, set);
            }
            py += dy;
            error += xDiff;
            if (error >= yDiff) {
                error -= yDiff;
                px += dx;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasTool::DrawVLine(Visuals::GraphicsBuffer& canvas, int x, int ys, int ye, bool set)
{
    for (auto y = std::min(ys, ye); y <= std::max(ys, ye); y++) {
        canvas.SetPixel(x, y, set);
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasTool::DrawHLine(Visuals::GraphicsBuffer& canvas, int xs, int xe, int y, bool set)
{
    for (auto x = std::min(xs, xe); x <= std::max(xs, xe); x++) {
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
    if (Flags & resetOnMove) {
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
    if (pt != LastPt) {
        Apply(canvas, pt);
    }
    Tool::End(pt);
    return canvas.Get();
}
//---------------------------------------------------------------------------

