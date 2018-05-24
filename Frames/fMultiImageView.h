//---------------------------------------------------------------------------
#ifndef fMultiImageViewH
#define fMultiImageViewH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "Graphics/GraphicsBuffers.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMultiImageViewFrame : public TFrame
{
__published:	// IDE-managed Components
    TPanel *panImages;
    TTimer *Timer1;
    void __fastcall FrameMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
    int                 m_Scale;
    TNotifyEvent        FOnClick;

    void    __fastcall  SetScale(int scale);
    void    __fastcall  OnFrameClicked(TObject *Sender);
public:		// User declarations
            __fastcall  TMultiImageViewFrame(TComponent* Owner);

    void    __fastcall  Clear();
    void    __fastcall  Add(const  Agdx::GraphicsBuffer& image, const String& hint);
    void    __fastcall  Select(int index);

    int     __property  Scale = { read = m_Scale, write = SetScale };
            __property  TNotifyEvent OnSelectedClick = { read = FOnClick, write = FOnClick };
};
//---------------------------------------------------------------------------
#endif
