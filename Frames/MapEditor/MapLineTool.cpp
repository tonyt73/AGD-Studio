//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapLineTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MapLineTool::MapLineTool()
: MapTool()
{
    Flags = resetOnMove | modifies;
}
//---------------------------------------------------------------------------
__fastcall MapLineTool::~MapLineTool()
{
}
//---------------------------------------------------------------------------
void __fastcall MapLineTool::Apply(EntityList& list, Entity entity, TPoint pt)
{
    list.clear();
    auto rect = TRect(StartPt.x, StartPt.y, LastPt.x, LastPt.y);
    SnapToTileGrid(rect);
    // change from tile space to unit space
    rect.Left   /= TileSize.cx;
    rect.Right  /= TileSize.cx;
    rect.Top    /= TileSize.cy;
    rect.Bottom /= TileSize.cy;

    if (!MS.Ctrl)
    {
        DrawLine(list, entity, rect);
    }
    else
    {
        if (abs(rect.Width()) >= abs(rect.Height()))
        {
            DrawLine(list, entity, rect, rect.Left < rect.Right ? 1 : -1, 0);
        }
        else
        {
            DrawLine(list, entity, rect, 0, rect.Top < rect.Bottom ? 1 : -1);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall MapLineTool::DrawLine(EntityList& list, Entity entity, TRect Rect)
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
            auto ne = entity;
            ne.Pt = TPoint(px * TileSize.cx, py * TileSize.cy);
            Set(list, ne);
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
            auto ne = entity;
            ne.Pt = TPoint(px * TileSize.cx, py * TileSize.cy);
            Set(list, ne);
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
void __fastcall MapLineTool::DrawLine(EntityList& list, Entity entity, TRect Rect, int dx, int dy)
{
    auto pt = TPoint(Rect.Left, Rect.Top);
    auto l = dx != 0 ? abs(Rect.Width()) : abs(Rect.Height());
    for (auto i = 0; i <= l; i++)
    {
        auto ne = entity;
        ne.Pt = TPoint(pt.x * TileSize.cx, pt.y * TileSize.cy);
        Set(list, ne);
        pt.x += dx;
        pt.y += dy;
    }
}
//---------------------------------------------------------------------------

