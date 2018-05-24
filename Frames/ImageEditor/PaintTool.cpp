//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "PaintTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall PaintTool::PaintTool()
{
}
//---------------------------------------------------------------------------
__fastcall PaintTool::~PaintTool()
{
}
//---------------------------------------------------------------------------
bool __fastcall PaintTool::IsLeftDown() const
{
    return m_MouseState.Contains(ssLeft);
}
//---------------------------------------------------------------------------
bool __fastcall PaintTool::IsRightDown() const
{
    return m_MouseState.Contains(ssRight);
}
//---------------------------------------------------------------------------
bool __fastcall PaintTool::IsMiddleDown() const
{
    return m_MouseState.Contains(ssMiddle);
}
//---------------------------------------------------------------------------
String __fastcall PaintTool::Begin(Agdx::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons)
{
    m_IsDrawing = true;
    m_Start = pt;
    m_Last = pt;
    m_MouseState = buttons;
    Apply(canvas, pt);
    m_Image = canvas.Get();
    return m_Image;
}
//---------------------------------------------------------------------------
void __fastcall PaintTool::Move(Agdx::GraphicsBuffer& canvas, const TPoint& pt, const TShiftState& buttons)
{
    if (!m_IsDrawing) return;
    if (m_Flags & resetImageOnMove)
    {
        // restore the canvas
        canvas.Set(m_Image);
    }
    m_Last = pt;
    canvas.Begin();
    Apply(canvas, pt);
    canvas.End();
}
//---------------------------------------------------------------------------
String __fastcall PaintTool::End(Agdx::GraphicsBuffer& canvas, const TPoint& pt)
{
    if (pt != m_Last)
    {
        Apply(canvas, pt);
    }
    m_IsDrawing = false;
}
//---------------------------------------------------------------------------




