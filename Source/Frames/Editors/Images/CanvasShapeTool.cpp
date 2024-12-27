//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "CanvasShapeTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CanvasShapeTool::CanvasShapeTool()
: CanvasTool()
{
    Flags = usesUndo | modifies | resetOnMove;
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::DrawRectangle(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt, bool Set, int Fill)
{
    switch (Fill) {
        case 0: { // outline
            DrawHLine(Canvas, StartPt.X, Pt.X, StartPt.Y, Set);
            DrawHLine(Canvas, StartPt.X, Pt.X, Pt.Y, Set);
            DrawVLine(Canvas, StartPt.X, StartPt.Y, Pt.Y, Set);
            DrawVLine(Canvas, Pt.X, StartPt.Y, Pt.Y, Set);
            break;
        }
        case 1: { // Fill
            for (int y = std::min(StartPt.Y, Pt.Y); y <= std::max(StartPt.Y, Pt.Y); y++) {
                DrawHLine(Canvas, StartPt.X, Pt.X, y, Set);
            }
            break;
        }
        case 2: { // Fill+outline
            for (int y = std::min(StartPt.Y, Pt.Y); y <= std::max(StartPt.Y, Pt.Y); y++) {
                DrawHLine(Canvas, StartPt.X, Pt.X, y, !Set);
            }
            DrawHLine(Canvas, StartPt.X, Pt.X, StartPt.Y, Set);
            DrawHLine(Canvas, StartPt.X, Pt.X, Pt.Y, Set);
            DrawVLine(Canvas, StartPt.X, StartPt.Y, Pt.Y, Set);
            DrawVLine(Canvas, Pt.X, StartPt.Y, Pt.Y, Set);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::DrawEllipse(Visuals::GraphicsBuffer& /*Canvas*/, const TPoint& /*Pt*/, bool /*Set*/, int /*Fill*/)
{
    // TODO -cDrawing: Implement Ellipse
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::DrawDiamond(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt, bool Set, int Fill)
{
    auto xs = std::min(StartPt.X, Pt.X);
    auto xe = std::max(StartPt.X, Pt.X);
    auto ys = std::min(StartPt.Y, Pt.Y);
    auto ye = std::max(StartPt.Y, Pt.Y);
    auto wx = xe - xs;
    auto wy = ye - ys;
    auto hx = xs + (wx / 2);
    auto hy = ys + (wy / 2);
    switch (Fill) {
        case 0: { // outline (primary)
            DrawLine(Canvas, TRect(hx, ys, xe, hy), Set);
            DrawLine(Canvas, TRect(xe, hy, hx, ye), Set);
            DrawLine(Canvas, TRect(hx, ye, xs, hy), Set);
            DrawLine(Canvas, TRect(xs, hy, hx, ys), Set);
            break;
        }
        case 1: { // Fill (primary)
            DrawLine(Canvas, TRect(hx, ys, xs, hy), Set, spLeft);
            DrawLine(Canvas, TRect(hx, ys, xe, hy), Set, spRight);
            for (auto pos : m_LinePositions) {
                DrawHLine(Canvas, pos.Left, pos.Right, pos.Top, Set);
            }
            DrawLine(Canvas, TRect(hx, ye, xs, hy), Set, spLeft);
            DrawLine(Canvas, TRect(hx, ye, xe, hy), Set, spRight);
            for (auto pos : m_LinePositions) {
                DrawHLine(Canvas, pos.Left, pos.Right, pos.Top, Set);
            }
            break;
        }
        case 2: { // Fill (secondary color) + outline (primary)
            DrawLine(Canvas, TRect(hx, ys, xs, hy), Set, spLeft);
            DrawLine(Canvas, TRect(hx, ys, xe, hy), Set, spRight);
            for (auto pos : m_LinePositions) {
                DrawHLine(Canvas, pos.Left, pos.Right, pos.Top, !Set);
            }
            DrawLine(Canvas, TRect(hx, ye, xs, hy), Set, spLeft);
            DrawLine(Canvas, TRect(hx, ye, xe, hy), Set, spRight);
            for (auto pos : m_LinePositions) {
                DrawHLine(Canvas, pos.Left, pos.Right, pos.Top, !Set);
            }

            DrawLine(Canvas, TRect(hx, ys, xs, hy), Set);
            DrawLine(Canvas, TRect(hx, ys, xe, hy), Set);
            DrawLine(Canvas, TRect(hx, ye, xs, hy), Set);
            DrawLine(Canvas, TRect(hx, ye, xe, hy), Set);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::DrawTriangle(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt, bool Set, int Fill)
{
    auto xs = std::min(StartPt.X, Pt.X);
    auto xe = std::max(StartPt.X, Pt.X);
    auto wx = xe - xs;
    auto hx = xs + (wx / 2);
    switch (Fill) {
        case 0: { // outline
            DrawLine(Canvas, TRect(hx, StartPt.Y, xs, Pt.Y), Set);
            DrawLine(Canvas, TRect(hx, StartPt.Y, xe, Pt.Y), Set);
            DrawHLine(Canvas, xs, xe, Pt.Y, Set);
            break;
        }
        case 1: { // Fill
            DrawLine(Canvas, TRect(hx, StartPt.Y, xs, Pt.Y), Set, spLeft);
            DrawLine(Canvas, TRect(hx, StartPt.Y, xe, Pt.Y), Set, spRight);
            for (auto pos : m_LinePositions) {
                DrawHLine(Canvas, pos.Left, pos.Right, pos.Top, Set);
            }
            break;
        }
        case 2: { // Fill + outline
            DrawLine(Canvas, TRect(hx, StartPt.Y, xs, Pt.Y), Set, spLeft);
            DrawLine(Canvas, TRect(hx, StartPt.Y, xe, Pt.Y), Set, spRight);
            for (auto pos : m_LinePositions) {
                DrawHLine(Canvas, pos.Left, pos.Right, pos.Top, !Set);
            }
            DrawLine(Canvas, TRect(hx, StartPt.Y, xs, Pt.Y), Set);
            DrawLine(Canvas, TRect(hx, StartPt.Y, xe, Pt.Y), Set);
            DrawHLine(Canvas, xs, xe, Pt.Y, Set);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::DrawRightTriangle(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt, bool Set, int Fill)
{
    switch (Fill) {
        case 0: { // outline
            DrawVLine(Canvas, StartPt.X, StartPt.Y, Pt.Y, Set);
            DrawHLine(Canvas, StartPt.X, Pt.X, Pt.Y, Set);
            DrawLine(Canvas, TRect(StartPt.X, StartPt.Y, Pt.X, Pt.Y), Set);
            break;
        }
        case 1: { // Fill
            DrawLine(Canvas, TRect(StartPt.X, StartPt.Y, Pt.X, Pt.Y), Set, spLeft);
            for (auto pos : m_LinePositions) {
                DrawHLine(Canvas, StartPt.X, pos.Left, pos.Top, Set);
            }
            break;
        }
        case 2: { // Fill + outline
            DrawLine(Canvas, TRect(StartPt.X, StartPt.Y, Pt.X, Pt.Y), Set, spLeft);
            for (auto pos : m_LinePositions) {
                DrawHLine(Canvas, StartPt.X, pos.Left, pos.Top, !Set);
            }

            DrawVLine(Canvas, StartPt.X, StartPt.Y, Pt.Y, Set);
            DrawHLine(Canvas, StartPt.X, Pt.X, Pt.Y, Set);
            DrawLine(Canvas, TRect(StartPt.X, StartPt.Y, Pt.X, Pt.Y), Set);
            break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall CanvasShapeTool::Apply(Visuals::GraphicsBuffer& Canvas, const TPoint& Pt)
{
    auto shape = Parameters.Get<int>("Shape");
    auto fill = Parameters.Get<int>("Fill");
    if (MS.Left || MS.Right) {
        switch (shape) {
            case 0: DrawRectangle    (Canvas, Pt, MS.Left, fill); break;
            case 1: DrawEllipse      (Canvas, Pt, MS.Left, fill); break;
            case 2: DrawDiamond      (Canvas, Pt, MS.Left, fill); break;
            case 3: DrawTriangle     (Canvas, Pt, MS.Left, fill); break;
            case 4: DrawRightTriangle(Canvas, Pt, MS.Left, fill); break;
        }
    }
}
//---------------------------------------------------------------------------

