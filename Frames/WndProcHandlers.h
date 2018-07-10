//---------------------------------------------------------------------------
#ifndef WndProcHandlersH
#define WndProcHandlersH
//---------------------------------------------------------------------------
class TWinControlHandler
{
protected:
    TWndMethod          m_OldWindowProc;
    TWinControl*        m_WinControl;
    bool                m_PaintOnErase;

    void    __fastcall  NewWindowProc(Messages::TMessage &Message);

public:
            __fastcall  TWinControlHandler(TWinControl* winControl, bool paintOnErase = false);
    virtual __fastcall ~TWinControlHandler();
};
//---------------------------------------------------------------------------
typedef std::unique_ptr<TWinControlHandler> WinControlEraseHandler;
//---------------------------------------------------------------------------
#endif //WndProcHandlersH
