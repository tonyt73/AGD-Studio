//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "MapTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MapTool::MapTool()
{
}
//---------------------------------------------------------------------------
__fastcall MapTool::~MapTool()
{
}
//---------------------------------------------------------------------------
void __fastcall MapTool::DrawLine(EntityList& list, const TRect& Rect, LinePositions* ptList)
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
            if (ptList != nullptr)
            {
                ptList->push_back(TPoint(px,py));
            }
//            if (0 <= px && px < canvas.Width && 0 <= py && py < canvas.Height)
//            {
//                //canvas.SetPixel(px, py, set);
//            }
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
            if (ptList != nullptr)
            {
                ptList->push_back(TPoint(px,py));
            }
//            if (0 <= px && px < canvas.Width && 0 <= py && py < canvas.Height)
//            {
//                //canvas.SetPixel(px, py, set);
//            }
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
void __fastcall MapTool::DrawHLine(EntityList& list, int xs, int xe, int y)
{
    for (auto x = std::min(xs, xe); x <= std::max(xs, xe); x++)
    {
        //canvas.SetPixel(x, y, set);
    }
}
//---------------------------------------------------------------------------




