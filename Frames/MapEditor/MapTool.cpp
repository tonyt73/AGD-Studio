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
int __fastcall MapTool::Snap(int value, int range) const
{
    return ((int)(value / range)) * range;
}
//---------------------------------------------------------------------------
void __fastcall MapTool::SnapToTileGrid(TPoint& pt) const
{
    pt.x = Snap(pt.x, m_TileSize.cx);
    pt.y = Snap(pt.x, m_TileSize.cy);
}
//---------------------------------------------------------------------------
void __fastcall MapTool::SnapToTileGrid(TRect& rect) const
{
    rect.Left   = Snap(rect.Left  , m_TileSize.cx);
    rect.Right  = Snap(rect.Right , m_TileSize.cx);
    rect.Top    = Snap(rect.Top   , m_TileSize.cy);
    rect.Bottom = Snap(rect.Bottom, m_TileSize.cy);
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
        if (IsPointValid(entity.Pt))
        {
            auto it = std::find(list.begin(), list.end(), entity);
            if (it == list.end())
            {
                list.push_back(entity);
            }
        }
    }
}
//---------------------------------------------------------------------------
//void __fastcall MapTool::DrawLine(EntityList& list, const Entity& entity, const TRect& Rect, LinePositions* ptList)
//{
//    auto dx = 1;
//    auto dy = 1;
//    auto px = Rect.Left;
//    auto py = Rect.Top;
//
//    auto yDiff = Rect.Bottom - Rect.Top;
//    if (yDiff < 0)
//    {
//        yDiff = -yDiff;
//        dy = -1;
//    }
//
//    auto xDiff = Rect.Right - Rect.Left;
//    if (xDiff < 0)
//    {
//        xDiff = -xDiff;
//        dx = -1;
//    }
//
//    auto error = 0;
//    if (xDiff > yDiff)
//    {
//        // inc x by 1, y by dy
//        for (auto i = 0; i <= xDiff; ++i)
//        {
//            if (ptList != nullptr)
//            {
//                ptList->push_back(TPoint(px,py));
//            }
////            if (0 <= px && px < canvas.Width && 0 <= py && py < canvas.Height)
////            {
////                //canvas.SetPixel(px, py, set);
////            }
//            px += dx;
//            error += yDiff;
//            if (error >= xDiff)
//            {
//                error -= xDiff;
//                py += dy;
//            }
//        }
//    }
//    else
//    {
//        // inc y by 1, x by dx
//        for (auto i = 0; i <= yDiff; ++i)
//        {
//            if (ptList != nullptr)
//            {
//                ptList->push_back(TPoint(px,py));
//            }
////            if (0 <= px && px < canvas.Width && 0 <= py && py < canvas.Height)
////            {
////                //canvas.SetPixel(px, py, set);
////            }
//            py += dy;
//            error += xDiff;
//            if (error >= yDiff)
//            {
//                error -= yDiff;
//                px += dx;
//            }
//        }
//    }
//}
//---------------------------------------------------------------------------
String __fastcall MapTool::Begin(EntityList& list, Entity entity, const TPoint& pt, const TShiftState& buttons)
{
    Tool::Begin(pt, buttons);
    Apply(list, entity, pt);
    return String();
}
//---------------------------------------------------------------------------
void __fastcall MapTool::Move(EntityList& list, Entity entity, const TPoint& pt, const TShiftState& buttons)
{
    if (entity.Image->SubType != "Tile")
        return;
    Tool::Move(pt, buttons);
    if (!IsDrawing) return;
    Apply(list, entity, pt);
}
//---------------------------------------------------------------------------
String __fastcall MapTool::End(EntityList& list, Entity entity, const TPoint& pt)
{
    if (pt != LastPt)
    {
        Apply(list, entity, pt);
    }
    Tool::End(pt);
    return String();
}
//---------------------------------------------------------------------------

