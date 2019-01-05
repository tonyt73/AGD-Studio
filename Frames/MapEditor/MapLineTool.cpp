//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Frames/MapEditor/MapLineTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MapLineTool::MapLineTool()
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
    DrawLine(list, entity, TRect(std::min(StartPt.x, LastPt.x), std::min(StartPt.y, LastPt.y), std::max(StartPt.x, LastPt.x), std::max(StartPt.y, LastPt.y)));
}
//---------------------------------------------------------------------------
void __fastcall MapLineTool::DrawLine(EntityList& list, Entity entity, TRect Rect)
{
    list.clear();
    SnapToTileGrid(Rect);

}
//---------------------------------------------------------------------------



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
