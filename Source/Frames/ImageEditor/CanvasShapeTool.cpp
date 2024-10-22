//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "CanvasShapeTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
CanvasShapeTool::CanvasShapeTool()
: CanvasTool()
{
    Flags = usesUndo | modifies | resetOnMove;
}
//---------------------------------------------------------------------------
CanvasShapeTool::~CanvasShapeTool()
{
}
//---------------------------------------------------------------------------
void CanvasShapeTool::DrawRectangle(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill)
{
    switch (fill)
    {
        case 0: // outline
            DrawHLine(canvas, StartPt.X, pt.X, StartPt.Y, set);
            DrawHLine(canvas, StartPt.X, pt.X, pt.Y, set);
            DrawVLine(canvas, StartPt.X, StartPt.Y, pt.Y, set);
            DrawVLine(canvas, pt.X, StartPt.Y, pt.Y, set);
            break;
        case 1: // fill
            for (int y = std::min(StartPt.Y, pt.Y); y <= std::max(StartPt.Y, pt.Y); y++)
            {
                DrawHLine(canvas, StartPt.X, pt.X, y, set);
            }
            break;
        case 2: // fill+outline
            for (int y = std::min(StartPt.Y, pt.Y); y <= std::max(StartPt.Y, pt.Y); y++)
            {
                DrawHLine(canvas, StartPt.X, pt.X, y, !set);
            }
            DrawHLine(canvas, StartPt.X, pt.X, StartPt.Y, set);
            DrawHLine(canvas, StartPt.X, pt.X, pt.Y, set);
            DrawVLine(canvas, StartPt.X, StartPt.Y, pt.Y, set);
            DrawVLine(canvas, pt.X, StartPt.Y, pt.Y, set);
            break;
    }
}
//---------------------------------------------------------------------------
void CanvasShapeTool::DrawEllipse(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill)
{
    // TODO: Implement Ellipse
}
//---------------------------------------------------------------------------
void CanvasShapeTool::DrawDiamond(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill)
{
    auto xs = std::min(StartPt.X, pt.X);
    auto xe = std::max(StartPt.X, pt.X);
    auto ys = std::min(StartPt.Y, pt.Y);
    auto ye = std::max(StartPt.Y, pt.Y);
    auto wx = xe - xs;
    auto wy = ye - ys;
    auto hx = xs + (wx / 2);
    auto hy = ys + (wy / 2);
    switch (fill)
    {
        case 0: // outline (primary)
            DrawLine(canvas, TRect(hx, ys, xe, hy), set);
            DrawLine(canvas, TRect(xe, hy, hx, ye), set);
            DrawLine(canvas, TRect(hx, ye, xs, hy), set);
            DrawLine(canvas, TRect(xs, hy, hx, ys), set);
            break;
        case 1: // fill (primary)
        {
            auto left = std::make_unique<LinePositions>();
            auto right = std::make_unique<LinePositions>();
            DrawLine(canvas, TRect(hx, ys, xs, hy), set, left.get());
            DrawLine(canvas, TRect(hx, ys, xe, hy), set, right.get());
            for (auto i = 0; i < left->size(); i++)
            {
                DrawHLine(canvas, (*left)[i].x, (*right)[i].x, (*left)[i].y, set);
            }
            left->clear();
            right->clear();
            DrawLine(canvas, TRect(hx, ye, xs, hy), set, left.get());
            DrawLine(canvas, TRect(hx, ye, xe, hy), set, right.get());
            for (auto i = 0; i < left->size(); i++)
            {
                DrawHLine(canvas, (*left)[i].x, (*right)[i].x, (*left)[i].y, set);
            }
            break;
        }
        case 2:
        {
            // fill (secondary color) + outline (primary)
            auto left = std::make_unique<LinePositions>();
            auto right = std::make_unique<LinePositions>();
            DrawLine(canvas, TRect(hx, ys, xs, hy), set, left.get());
            DrawLine(canvas, TRect(hx, ys, xe, hy), set, right.get());
            for (auto i = 0; i < left->size(); i++)
            {
                DrawHLine(canvas, (*left)[i].x, (*right)[i].x, (*left)[i].y, !set);
            }
            left->clear();
            right->clear();
            DrawLine(canvas, TRect(hx, ye, xs, hy), set, left.get());
            DrawLine(canvas, TRect(hx, ye, xe, hy), set, right.get());
            for (auto i = 0; i < left->size(); i++)
            {
                DrawHLine(canvas, (*left)[i].x, (*right)[i].x, (*left)[i].y, !set);
            }

            DrawLine(canvas, TRect(hx, ys, xs, hy), set);
            DrawLine(canvas, TRect(hx, ys, xe, hy), set);
            DrawLine(canvas, TRect(hx, ye, xs, hy), set);
            DrawLine(canvas, TRect(hx, ye, xe, hy), set);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void CanvasShapeTool::DrawTriangle(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill)
{
    auto xs = std::min(StartPt.X, pt.X);
    auto xe = std::max(StartPt.X, pt.X);
    auto wx = xe - xs;
    auto hx = xs + (wx / 2);
    switch (fill)
    {
        case 0: // outline
            DrawLine(canvas, TRect(hx, StartPt.Y, xs, pt.Y), set);
            DrawLine(canvas, TRect(hx, StartPt.Y, xe, pt.Y), set);
            DrawHLine(canvas, xs, xe, pt.Y, set);
            break;
        case 1: // fill
        {
            auto left = std::make_unique<LinePositions>();
            auto right = std::make_unique<LinePositions>();
            DrawLine(canvas, TRect(hx, StartPt.Y, xs, pt.Y), set, left.get());
            DrawLine(canvas, TRect(hx, StartPt.Y, xe, pt.Y), set, right.get());
            for (auto i = 0; i < left->size(); i++)
            {
                DrawHLine(canvas, (*left)[i].x, (*right)[i].x, (*left)[i].y, set);
            }
            break;
        }
        case 2:
        {
            // fill + outline
            auto left = std::make_unique<LinePositions>();
            auto right = std::make_unique<LinePositions>();
            DrawLine(canvas, TRect(hx, StartPt.Y, xs, pt.Y), set, left.get());
            DrawLine(canvas, TRect(hx, StartPt.Y, xe, pt.Y), set, right.get());
            for (auto i = 0; i < left->size(); i++)
            {
                DrawHLine(canvas, (*left)[i].x, (*right)[i].x, (*left)[i].y, !set);
            }

            DrawLine(canvas, TRect(hx, StartPt.Y, xs, pt.Y), set);
            DrawLine(canvas, TRect(hx, StartPt.Y, xe, pt.Y), set);
            DrawHLine(canvas, xs, xe, pt.Y, set);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void CanvasShapeTool::DrawRightTriangle(Visuals::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill)
{
    switch (fill)
    {
        case 0: // outline
            DrawVLine(canvas, StartPt.X, StartPt.Y, pt.Y, set);
            DrawHLine(canvas, StartPt.X, pt.X, pt.Y, set);
            DrawLine(canvas, TRect(StartPt.X, StartPt.Y, pt.X, pt.Y), set);
            break;
        case 1: // fill
        {
            auto edge = std::make_unique<LinePositions>();
            DrawLine(canvas, TRect(StartPt.X, StartPt.Y, pt.X, pt.Y), set, edge.get());
            for (auto i = 0; i < edge->size(); i++)
            {
                DrawHLine(canvas, StartPt.X, (*edge)[i].x, (*edge)[i].y, set);
            }
            break;
        }
        case 2:
        {
            // fill + outline
            auto edge = std::make_unique<LinePositions>();
            DrawLine(canvas, TRect(StartPt.X, StartPt.Y, pt.X, pt.Y), set, edge.get());
            for (auto i = 0; i < edge->size(); i++)
            {
                DrawHLine(canvas, StartPt.X, (*edge)[i].x, (*edge)[i].y, !set);
            }

            DrawVLine(canvas, StartPt.X, StartPt.Y, pt.Y, set);
            DrawHLine(canvas, StartPt.X, pt.X, pt.Y, set);
            DrawLine(canvas, TRect(StartPt.X, StartPt.Y, pt.X, pt.Y), set);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void CanvasShapeTool::Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt)
{
    auto shape = Parameters.Get<int>("Shape");
    auto fill = Parameters.Get<int>("Fill");
    if (MS.Left || MS.Right)
    {
        switch (shape)
        {
            case 0: DrawRectangle(canvas, pt, MS.Left, fill); break;
            case 1: DrawEllipse(canvas, pt, MS.Left, fill); break;
            case 2: DrawDiamond(canvas, pt, MS.Left, fill); break;
            case 3: DrawTriangle(canvas, pt, MS.Left, fill); break;
            case 4: DrawRightTriangle(canvas, pt, MS.Left, fill); break;
        }
    }
}
//---------------------------------------------------------------------------

