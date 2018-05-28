//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "CanvasShapeTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CanvasShapeTool::CanvasShapeTool()
{
    m_Flags = usesUndo | modifiesImage | resetImageOnMove;
}
//---------------------------------------------------------------------------
__fastcall CanvasShapeTool::~CanvasShapeTool()
{
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::DrawRectangle(Agdx::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill)
{
    switch (fill)
    {
        case 0: // outline
            DrawHLine(canvas, m_Start.X, pt.X, m_Start.Y, set);
            DrawHLine(canvas, m_Start.X, pt.X, pt.Y, set);
            DrawVLine(canvas, m_Start.X, m_Start.Y, pt.Y, set);
            DrawVLine(canvas, pt.X, m_Start.Y, pt.Y, set);
            break;
        case 1: // fill
            for (int y = std::min(m_Start.Y, pt.Y); y <= std::max(m_Start.Y, pt.Y); y++)
            {
                DrawHLine(canvas, m_Start.X, pt.X, y, set);
            }
            break;
        case 2: // fill+outline
            for (int y = std::min(m_Start.Y, pt.Y); y <= std::max(m_Start.Y, pt.Y); y++)
            {
                DrawHLine(canvas, m_Start.X, pt.X, y, !set);
            }
            DrawHLine(canvas, m_Start.X, pt.X, m_Start.Y, set);
            DrawHLine(canvas, m_Start.X, pt.X, pt.Y, set);
            DrawVLine(canvas, m_Start.X, m_Start.Y, pt.Y, set);
            DrawVLine(canvas, pt.X, m_Start.Y, pt.Y, set);
            break;
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::DrawEllipse(Agdx::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill)
{
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::DrawDiamond(Agdx::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill)
{
    auto xs = std::min(m_Start.X, pt.X);
    auto xe = std::max(m_Start.X, pt.X);
    auto ys = std::min(m_Start.Y, pt.Y);
    auto ye = std::max(m_Start.Y, pt.Y);
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
void __fastcall CanvasShapeTool::DrawTriangle(Agdx::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill)
{
    auto xs = std::min(m_Start.X, pt.X);
    auto xe = std::max(m_Start.X, pt.X);
    auto wx = xe - xs;
    auto hx = xs + (wx / 2);
    switch (fill)
    {
        case 0: // outline
            DrawLine(canvas, TRect(hx, m_Start.Y, xs, pt.Y), set);
            DrawLine(canvas, TRect(hx, m_Start.Y, xe, pt.Y), set);
            DrawHLine(canvas, xs, xe, pt.Y, set);
            break;
        case 1: // fill
        {
            auto left = std::make_unique<LinePositions>();
            auto right = std::make_unique<LinePositions>();
            DrawLine(canvas, TRect(hx, m_Start.Y, xs, pt.Y), set, left.get());
            DrawLine(canvas, TRect(hx, m_Start.Y, xe, pt.Y), set, right.get());
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
            DrawLine(canvas, TRect(hx, m_Start.Y, xs, pt.Y), set, left.get());
            DrawLine(canvas, TRect(hx, m_Start.Y, xe, pt.Y), set, right.get());
            for (auto i = 0; i < left->size(); i++)
            {
                DrawHLine(canvas, (*left)[i].x, (*right)[i].x, (*left)[i].y, !set);
            }

            DrawLine(canvas, TRect(hx, m_Start.Y, xs, pt.Y), set);
            DrawLine(canvas, TRect(hx, m_Start.Y, xe, pt.Y), set);
            DrawHLine(canvas, xs, xe, pt.Y, set);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::DrawRightTriangle(Agdx::GraphicsBuffer& canvas, const TPoint& pt, bool set, int fill)
{
    switch (fill)
    {
        case 0: // outline
            DrawVLine(canvas, m_Start.X, m_Start.Y, pt.Y, set);
            DrawHLine(canvas, m_Start.X, pt.X, pt.Y, set);
            DrawLine(canvas, TRect(m_Start.X, m_Start.Y, pt.X, pt.Y), set);
            break;
        case 1: // fill
        {
            auto edge = std::make_unique<LinePositions>();
            DrawLine(canvas, TRect(m_Start.X, m_Start.Y, pt.X, pt.Y), set, edge.get());
            for (auto i = 0; i < edge->size(); i++)
            {
                DrawHLine(canvas, m_Start.X, (*edge)[i].x, (*edge)[i].y, set);
            }
            break;
        }
        case 2:
        {
            // fill + outline
            auto edge = std::make_unique<LinePositions>();
            DrawLine(canvas, TRect(m_Start.X, m_Start.Y, pt.X, pt.Y), set, edge.get());
            for (auto i = 0; i < edge->size(); i++)
            {
                DrawHLine(canvas, m_Start.X, (*edge)[i].x, (*edge)[i].y, !set);
            }

            DrawVLine(canvas, m_Start.X, m_Start.Y, pt.Y, set);
            DrawHLine(canvas, m_Start.X, pt.X, pt.Y, set);
            DrawLine(canvas, TRect(m_Start.X, m_Start.Y, pt.X, pt.Y), set);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt)
{
    int shape = 0;
    m_Parameters.Get("Shape", shape);
    int fill = 0;
    m_Parameters.Get("Fill", fill);
    if (IsLeftDown() || IsRightDown())
    {
        switch (shape)
        {
            case 0: DrawRectangle(canvas, pt, IsLeftDown(), fill); break;
            case 1: DrawEllipse(canvas, pt, IsLeftDown(), fill); break;
            case 2: DrawDiamond(canvas, pt, IsLeftDown(), fill); break;
            case 3: DrawTriangle(canvas, pt, IsLeftDown(), fill); break;
            case 4: DrawRightTriangle(canvas, pt, IsLeftDown(), fill); break;
        }
    }
}
//---------------------------------------------------------------------------

