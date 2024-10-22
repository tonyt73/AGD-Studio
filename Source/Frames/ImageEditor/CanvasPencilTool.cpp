//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "CanvasPencilTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
CanvasPencilTool::CanvasPencilTool()
: CanvasTool()
{
    Flags = usesUndo | modifies;
}
//---------------------------------------------------------------------------
CanvasPencilTool::~CanvasPencilTool()
{
}
//---------------------------------------------------------------------------
void CanvasPencilTool::Apply(Visuals::GraphicsBuffer& canvas, const TPoint& pt)
{
    if (MS.Left)
    {
        DrawLine(canvas, TRect(LastPt.X, LastPt.Y, pt.X, pt.Y), true);
    }
    else if (MS.Right)
    {
        DrawLine(canvas, TRect(LastPt.X, LastPt.Y, pt.X, pt.Y), false);
    }
}
//---------------------------------------------------------------------------

