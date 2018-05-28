//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "CanvasTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CanvasTool::CanvasTool()
{
}
//---------------------------------------------------------------------------
__fastcall CanvasTool::~CanvasTool()
{
}
//---------------------------------------------------------------------------
void __fastcall CanvasTool::Parameters(const Generic& parameters)
{
    m_Parameters = parameters;
}
//---------------------------------------------------------------------------
bool __fastcall CanvasTool::IsLeftDown() const
{
    return m_MouseState.Contains(ssLeft);
}
//---------------------------------------------------------------------------
bool __fastcall CanvasTool::IsRightDown() const
{
    return m_MouseState.Contains(ssRight);
}
//---------------------------------------------------------------------------
bool __fastcall CanvasTool::IsMiddleDown() const
{
    return m_MouseState.Contains(ssMiddle);
}
//---------------------------------------------------------------------------
String __fastcall CanvasTool::Begin(Agdx::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons)
{
    m_IsDrawing = true;
    m_Start = pt;
    m_Last = pt;
    m_MouseState = buttons;
    Apply(canvas, pt);
    m_Image = canvas.Get();
    return m_Image;
}
//---------------------------------------------------------------------------
void __fastcall CanvasTool::Move(Agdx::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons)
{
    if (!m_IsDrawing) return;
    if (m_Flags & resetImageOnMove)
    {
        // restore the canvas
        canvas.Set(m_Image);
    }
    canvas.Begin();
    Apply(canvas, pt);
    canvas.End();
    m_Last = pt;
}
//---------------------------------------------------------------------------
String __fastcall CanvasTool::End(Agdx::GraphicsBuffer& canvas, const TPoint& pt)
{
    if (pt != m_Last)
    {
        Apply(canvas, pt);
    }
    m_IsDrawing = false;
    return canvas.Get();
}
//---------------------------------------------------------------------------
void __fastcall CanvasTool::DrawLine(Agdx::GraphicsBuffer& canvas, const TRect& Rect, bool set, LinePositions* list)
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
            if (list != nullptr)
            {
                list->push_back(TPoint(px,py));
            }
            if (0 <= px && px < canvas.Width && 0 <= py && py < canvas.Height)
            {
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
            if (list != nullptr)
            {
                list->push_back(TPoint(px,py));
            }
            if (0 <= px && px < canvas.Width && 0 <= py && py < canvas.Height)
            {
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
void __fastcall CanvasTool::DrawVLine(Agdx::GraphicsBuffer& canvas, int x, int ys, int ye, bool set)
{
    for (auto y = std::min(ys, ye); y <= std::max(ys, ye); y++)
    {
        canvas.SetPixel(x, y, set);
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasTool::DrawHLine(Agdx::GraphicsBuffer& canvas, int xs, int xe, int y, bool set)
{
    for (auto x = std::min(xs, xe); x <= std::max(xs, xe); x++)
    {
        canvas.SetPixel(x, y, set);
    }
}
//---------------------------------------------------------------------------




