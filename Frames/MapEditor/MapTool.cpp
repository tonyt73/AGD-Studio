//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapTool.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MapTool::MapTool()
: m_TileSize(theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itTile].Minimum)
{
}
//---------------------------------------------------------------------------
__fastcall MapTool::~MapTool()
{
}
//---------------------------------------------------------------------------
void __fastcall MapTool::Set(EntityList& list, const Entity& entity)
{
    if (Flags & allowOnlyOne)
    {
        list.clear();
        list.push_back(entity);
    }
    else
    {
        auto exists = std::find(list.begin(), list.end(), entity);
        if (exists == list.end())
        {
            list.push_back(entity);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall MapTool::DrawLine(EntityList& list, const Entity& entity, const TRect& Rect, LinePositions* ptList)
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
void __fastcall MapTool::DrawRect(EntityList& list, const Entity& entity, const TRect& Rect)
{
    for (auto y = Rect.Top; y <= Rect.Bottom; y += m_TileSize.cy)
    {
        for (auto x = Rect.Left; x <= Rect.Right; x += m_TileSize.cx)
        {
            auto ne = entity;
            ne.Pt = TPoint(x, y);
            Set(list, ne);
        }
    }
}
//---------------------------------------------------------------------------




