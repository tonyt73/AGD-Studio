//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "MapRectTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
 MapRectTool::MapRectTool()
: MapTool()
{
    Flags = resetOnMove | modifies;
}
//---------------------------------------------------------------------------
 MapRectTool::~MapRectTool()
{
}
//---------------------------------------------------------------------------
void MapRectTool::Apply(Project::MapEntityList& list, Project::MapEntity entity)
{
    DrawRect(list, entity, TRect(StartPt.x, StartPt.y, LastPt.x, LastPt.y));
}
//---------------------------------------------------------------------------
void MapRectTool::DrawRect(Project::MapEntityList& list, Project::MapEntity entity, TRect Rect)
{
    SnapToTileGrid(Rect);
    if (MS.Ctrl)
    {
        auto size = max(abs(Rect.Width()), abs(Rect.Height()));
        (Rect.Left < Rect.Right ) ? (Rect.Right  = Rect.Left + size) : (Rect.Right  = Rect.Left - size);
        (Rect.Top  < Rect.Bottom) ? (Rect.Bottom = Rect.Top  + size) : (Rect.Bottom = Rect.Top  - size);
    }

    auto dx = TileSize.cx * (Rect.Width( ) >= 0 ? 1 : -1);
    auto dy = TileSize.cy * (Rect.Height() >= 0 ? 1 : -1);

    for (auto iy = 0; iy <= abs(Rect.Height() / TileSize.cy); iy += 1)
    {
        for (auto ix = 0; ix <= abs(Rect.Width() / TileSize.cx); ix += 1)
        {
            auto ne = entity;
            ne.Pt = TPoint(Rect.Left + (ix * dx), Rect.Top + (iy * dy));
            Set(list, ne);
        }
    }
}
//---------------------------------------------------------------------------
