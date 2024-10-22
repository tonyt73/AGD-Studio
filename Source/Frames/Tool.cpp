//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Tool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Tool::Tool()
: m_Flags(0)
, m_StartPt(TPoint(0,0))
, m_LastPt(TPoint(-1,-1))
, m_IsDrawing(false)
, m_Width(0)
, m_Height(0)
{
}
//---------------------------------------------------------------------------
Tool::~Tool()
{
}
//---------------------------------------------------------------------------
bool Tool::IsPointValid(const TPoint& pt) const
{
    return (0 <= pt.x && pt.x < Width && 0 <= pt.y && pt.y < Height);
}
//---------------------------------------------------------------------------
void Tool::Begin(const TPoint& pt, const TShiftState& buttons)
{
    m_IsDrawing = true;
    m_StartPt = pt;
    m_LastPt = pt;
    m_MouseState = MouseState(buttons);
}
//---------------------------------------------------------------------------
void Tool::Move(const TPoint& pt, const TShiftState& buttons)
{
    m_MouseState = MouseState(buttons);
    m_LastPt = pt;
}
//---------------------------------------------------------------------------
void Tool::End(const TPoint& pt)
{
    m_IsDrawing = false;
}
//---------------------------------------------------------------------------

