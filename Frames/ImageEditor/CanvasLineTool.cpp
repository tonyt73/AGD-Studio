//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "CanvasLineTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CanvasLineTool::CanvasLineTool()
{
    Flags = usesUndo | modifies | resetOnMove;
}
//---------------------------------------------------------------------------
__fastcall CanvasLineTool::~CanvasLineTool()
{
}
//---------------------------------------------------------------------------
void __fastcall CanvasLineTool::Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt)
{
    if (IsLeftDown())
    {
        DrawLine(canvas, TRect(StartPt.X, StartPt.Y, pt.X, pt.Y), true);
    }
    else if (IsRightDown())
    {
        DrawLine(canvas, TRect(StartPt.X, StartPt.Y, pt.X, pt.Y), false);
    }
}
//---------------------------------------------------------------------------

