//---------------------------------------------------------------------------
#ifndef TfrmAppFrameH
#define TfrmAppFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "LMDDckSite.hpp"
//---------------------------------------------------------------------------
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
class TfrmAppFrame : public TFrame
{
__published:    // IDE-managed Components
private:        // User declarations
protected:
    Registrar                   m_Registrar;
    TNotifyEvent                FOnDone;
    TNotifyEvent                FOnFormClose;

public:         // User declarations
                    __fastcall  TfrmAppFrame(TComponent* Owner) override;
                    __fastcall ~TfrmAppFrame() override;

    virtual void    __fastcall  OnActivate(TWinControl* parent);
    virtual void    __fastcall  OnClose();
    virtual void    __fastcall  OnCreate();

    __property TNotifyEvent     OnDone      = { read = FOnDone     , write = FOnDone      };
    __property TNotifyEvent     OnFormClose = { read = FOnFormClose, write = FOnFormClose };
};
//---------------------------------------------------------------------------
#endif
