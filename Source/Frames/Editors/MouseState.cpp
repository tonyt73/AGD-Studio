//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "MouseState.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MouseState::MouseState()
{
}
//---------------------------------------------------------------------------
__fastcall MouseState::MouseState(TMouseButton button, const TShiftState& shiftState)
: MouseState(shiftState)
{
    m_Left   |= button == mbLeft;
    m_Middle |= button == mbMiddle;
    m_Right  |= button == mbRight;
}
//---------------------------------------------------------------------------
__fastcall MouseState::MouseState(const TShiftState& shiftState)
: m_ShiftState(shiftState)
{
    auto altState = (GetKeyState(VK_MENU) & 0x8000) != 0;
    m_Shift       =  shiftState.Contains(ssShift) && !shiftState.Contains(ssCtrl  ) &&  !shiftState.Contains(ssAlt  );
    m_Ctrl        = !shiftState.Contains(ssShift) &&  shiftState.Contains(ssCtrl  ) &&  !shiftState.Contains(ssAlt  );
    m_Alt         = !shiftState.Contains(ssShift) && !shiftState.Contains(ssCtrl  ) &&  (shiftState.Contains(ssAlt  ) || altState);
    m_AltShift    =  shiftState.Contains(ssShift) && !shiftState.Contains(ssCtrl  ) &&  (shiftState.Contains(ssAlt  ) || altState);
    m_AltCtrl     = !shiftState.Contains(ssShift) &&  shiftState.Contains(ssCtrl  ) &&  (shiftState.Contains(ssAlt  ) || altState);
    m_CtrlShift   =  shiftState.Contains(ssShift) &&  shiftState.Contains(ssCtrl  ) && !(shiftState.Contains(ssAlt  ));
    m_Left        =  shiftState.Contains(ssLeft ) && !shiftState.Contains(ssMiddle) &&  !shiftState.Contains(ssRight);
    m_Middle      = !shiftState.Contains(ssLeft ) &&  shiftState.Contains(ssMiddle) &&  !shiftState.Contains(ssRight);
    m_Right       = !shiftState.Contains(ssLeft ) && !shiftState.Contains(ssMiddle) &&   shiftState.Contains(ssRight);

    m_NoModifiers = !m_Shift && !m_Ctrl && !m_Alt && !m_AltShift && !m_AltCtrl && !m_CtrlShift;
}
//---------------------------------------------------------------------------
bool __fastcall MouseState::Has(TShiftState ss) const
{
    return m_ShiftState == ss;
}
//---------------------------------------------------------------------------
