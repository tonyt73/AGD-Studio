//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "CanvasLineTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CanvasLineTool::CanvasLineTool()
: CanvasTool()
{
    Flags = usesUndo | modifies | resetOnMove;
}
//---------------------------------------------------------------------------
void __fastcall CanvasLineTool::Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt)
{
    if (MS.Left)
    {
        DrawLine(canvas, TRect(StartPt.X, StartPt.Y, pt.X, pt.Y), true);
    }
    else if (MS.Right)
    {
        DrawLine(canvas, TRect(StartPt.X, StartPt.Y, pt.X, pt.Y), false);
    }
}
//---------------------------------------------------------------------------

