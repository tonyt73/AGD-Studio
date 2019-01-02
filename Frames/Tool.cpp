//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Tool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Tool::Tool()
: m_Flags(0)
, m_StartPt(TPoint(0,0))
, m_LastPt(TPoint(-1,-1))
, m_IsDrawing(false)
, m_Width(0)
, m_Height(0)
{
}
//---------------------------------------------------------------------------
__fastcall Tool::~Tool()
{
}
//---------------------------------------------------------------------------
bool __fastcall Tool::IsLeftDown() const
{
    return m_MouseState.Contains(ssLeft);
}
//---------------------------------------------------------------------------
bool __fastcall Tool::IsRightDown() const
{
    return m_MouseState.Contains(ssRight);
}
//---------------------------------------------------------------------------
bool __fastcall Tool::IsMiddleDown() const
{
    return m_MouseState.Contains(ssMiddle);
}
//---------------------------------------------------------------------------
bool __fastcall Tool::IsPointValid(const TPoint& pt) const
{
    return (0 <= pt.x && pt.x < Width && 0 <= pt.y && pt.y < Height);
}
//---------------------------------------------------------------------------
void __fastcall Tool::Begin(const TPoint& pt, const TShiftState& buttons)
{
    m_IsDrawing = true;
    m_StartPt = pt;
    m_LastPt = pt;
    m_MouseState = buttons;
}
//---------------------------------------------------------------------------
void __fastcall Tool::Move(const TPoint& pt, const TShiftState& buttons)
{
    m_MouseState = buttons;
    m_LastPt = pt;
}
//---------------------------------------------------------------------------
void __fastcall Tool::End(const TPoint& pt)
{
    m_IsDrawing = false;
}
//---------------------------------------------------------------------------




