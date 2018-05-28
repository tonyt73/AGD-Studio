//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "CanvasLineTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CanvasLineTool::CanvasLineTool()
{
    m_Flags = usesUndo | modifiesImage | resetImageOnMove;
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
        DrawLine(canvas, TRect(m_Start.X, m_Start.Y, pt.X, pt.Y), true);
    }
    else if (IsRightDown())
    {
        DrawLine(canvas, TRect(m_Start.X, m_Start.Y, pt.X, pt.Y), false);
    }
}
//---------------------------------------------------------------------------

