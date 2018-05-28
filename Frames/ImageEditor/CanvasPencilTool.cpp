//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "CanvasPencilTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CanvasPencilTool::CanvasPencilTool()
{
    m_Flags = usesUndo | modifiesImage;
}
//---------------------------------------------------------------------------
__fastcall CanvasPencilTool::~CanvasPencilTool()
{
}
//---------------------------------------------------------------------------
void __fastcall CanvasPencilTool::Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt)
{
    if (IsLeftDown())
    {
        DrawLine(canvas, TRect(m_Last.X, m_Last.Y, pt.X, pt.Y), true);
    }
    else if (IsRightDown())
    {
        DrawLine(canvas, TRect(m_Last.X, m_Last.Y, pt.X, pt.Y), false);
    }
}
//---------------------------------------------------------------------------

