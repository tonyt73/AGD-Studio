//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "PencilTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall PencilTool::PencilTool()
{
    m_Flags = usesUndo | modifiesImage;
}
//---------------------------------------------------------------------------
__fastcall PencilTool::~PencilTool()
{
}
//---------------------------------------------------------------------------
void __fastcall PencilTool::Apply(Agdx::GraphicsBuffer& canvas, const TPoint& pt)
{
    if (IsLeftDown())
    {
        canvas.SetPixel(pt.X, pt.Y, true);
    }
    else if (IsRightDown())
    {
        canvas.SetPixel(pt.X, pt.Y, false);
    }
}
//---------------------------------------------------------------------------

