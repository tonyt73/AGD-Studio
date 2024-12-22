//---------------------------------------------------------------------------
#ifndef AppFrameH
#define AppFrameH
//---------------------------------------------------------------------------
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
class TAppFrame : public TFrame
{
protected:
    Registrar                   m_Registrar;
    TNotifyEvent                FOnDone;
    TNotifyEvent                FOnFormClose;

public:
                    __fastcall  TAppFrame(TComponent* Owner) override;
                    __fastcall ~TAppFrame() override;

    virtual void    __fastcall  OnActivate(TWinControl* parent);
    virtual void    __fastcall  OnClose();

    __property TNotifyEvent     OnDone      = { read = FOnDone     , write = FOnDone      };
    __property TNotifyEvent     OnFormClose = { read = FOnFormClose, write = FOnFormClose };
};
//---------------------------------------------------------------------------
#endif
