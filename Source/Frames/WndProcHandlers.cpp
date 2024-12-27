//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "WndProcHandlers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TWinControlHandler::TWinControlHandler(TWinControl* winControl, bool paintOnErase)
: m_WinControl(winControl)
, m_PaintOnErase(paintOnErase)
{
    // cannot place this initialization code in the base class as the
    // vtable is not complete at that stage, and thus NewWindowProc is not valid!
    if (m_WinControl)
    {
        m_OldWindowProc = m_WinControl->WindowProc;
        m_WinControl->WindowProc = NewWindowProc;
    }
}
//---------------------------------------------------------------------------
__fastcall TWinControlHandler::~TWinControlHandler()
{
    if (m_WinControl)
    {
        m_WinControl->WindowProc = m_OldWindowProc;
    }
}
//---------------------------------------------------------------------------
void __fastcall TWinControlHandler::NewWindowProc( Messages::TMessage &Message )
{
    if (m_WinControl)
    {
        // if we aren't erasing the control
        if (WM_ERASEBKGND != Message.Msg)
        {
            // handle the message as normal
            m_OldWindowProc(Message);
        }
        else if (m_PaintOnErase)
        {
            m_OldWindowProc(Message);
            // tell the control to draw itself RIGHT AWAY!
            m_WinControl->Perform(WM_PAINT, reinterpret_cast<WPARAM>(static_cast<TControlBar*>(m_WinControl)->Canvas->Handle), nullptr);
        }
    }
}
//---------------------------------------------------------------------------

