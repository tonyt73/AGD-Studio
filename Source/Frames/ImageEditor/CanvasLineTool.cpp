//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "CanvasLineTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
CanvasLineTool::CanvasLineTool()
: CanvasTool()
{
    Flags = usesUndo | modifies | resetOnMove;
}
//---------------------------------------------------------------------------
CanvasLineTool::~CanvasLineTool()
{
}
//---------------------------------------------------------------------------
void CanvasLineTool::Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt)
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

