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




