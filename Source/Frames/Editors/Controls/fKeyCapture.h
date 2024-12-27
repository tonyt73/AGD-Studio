//---------------------------------------------------------------------------
#ifndef fKeyCaptureH
#define fKeyCaptureH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <map>
//---------------------------------------------------------------------------
class TfrmKeyCode : public TFrame
{
__published:    // IDE-managed Components
    TLabel *lblKey;
    TPanel *panCaption;
    TEdit *edtKey;
    void __fastcall edtKeyKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall edtKeyMouseEnter(TObject *Sender);
    void __fastcall edtKeyMouseLeave(TObject *Sender);
    void __fastcall edtKeyChange(TObject *Sender);
    void __fastcall FrameMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
private:    // User declarations
    std::map<wchar_t, String>   m_KeyMap;

    wchar_t                     m_KeyCode;
    bool                        m_NotSet;

    void            __fastcall  UpdateKeyInfo();
    void            __fastcall  SetKeyCode(wchar_t keyCode);
    const String    __fastcall  GetCaption();
    void            __fastcall  SetCaption(const String& caption);
    TNotifyEvent                FOnChanged;

public:        // User declarations
                    __fastcall  TfrmKeyCode(TComponent* Owner) override;
__published:
    String          __property  Caption = { read = GetCaption, write = SetCaption };
    wchar_t         __property  KeyCode = { read = m_KeyCode, write = SetKeyCode };

            // events
    __property  TNotifyEvent    OnChanged = { read = FOnChanged, write = FOnChanged };
};
//---------------------------------------------------------------------------
#endif
