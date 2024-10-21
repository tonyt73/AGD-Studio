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

    void      NewWindowProc(Messages::TMessage &Message);

public:
              TWinControlHandler(TWinControl* winControl, bool paintOnErase = false);
    virtual  ~TWinControlHandler();
};
//---------------------------------------------------------------------------
typedef std::unique_ptr<TWinControlHandler> EraseHandler;
//---------------------------------------------------------------------------
#endif //WndProcHandlersH
