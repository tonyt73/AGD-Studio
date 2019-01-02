//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapRectTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MapRectTool::MapRectTool()
{
    Flags = resetOnMove | modifies;
}
//---------------------------------------------------------------------------
__fastcall MapRectTool::~MapRectTool()
{
}
//---------------------------------------------------------------------------
void __fastcall MapRectTool::Apply(EntityList& list, Entity entity, TPoint pt)
{
    DrawRect(list, entity, TRect(std::min(StartPt.x, LastPt.x), std::min(StartPt.y, LastPt.y), std::max(StartPt.x, LastPt.x), std::max(StartPt.y, LastPt.y)));
}
//---------------------------------------------------------------------------
void __fastcall MapRectTool::DrawRect(EntityList& list, Entity entity, TRect Rect)
{
    list.clear();
    SnapToTileGrid(Rect);
    for (auto y = Rect.Top; y < Rect.Bottom; y += TileSize.cy)
    {
        for (auto x = Rect.Left; x < Rect.Right; x += TileSize.cx)
        {
            auto ne = entity;
            ne.Pt = TPoint(x, y);
            Set(list, ne);
        }
    }
}
//---------------------------------------------------------------------------
