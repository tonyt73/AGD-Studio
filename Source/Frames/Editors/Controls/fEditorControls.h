//---------------------------------------------------------------------------
#ifndef fEditorControlsH
#define fEditorControlsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "LMDDckSite.hpp"
#include "Project/Documents/Controls.h"
#include "Messaging/Messaging.h"
#include "Messaging/Event.h"
#include "fKeyCapture.h"
#include "fEditor.h"
//---------------------------------------------------------------------------
class TfrmEditorControls : public TfrmEditor
{
__published:// IDE-managed Components
    TfrmKeyCode *kcDown;
    TfrmKeyCode *kcFire1;
    TfrmKeyCode *kcFire2;
    TfrmKeyCode *kcFire3;
    TfrmKeyCode *kcLeft;
    TfrmKeyCode *kcOption1;
    TfrmKeyCode *kcOption2;
    TfrmKeyCode *kcOption3;
    TfrmKeyCode *kcOption4;
    TfrmKeyCode *kcRight;
    TfrmKeyCode *kcUp;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TShape *Line1;
    TShape *Line2;
    TShape *Line3;

private:    // User declarations
    std::unique_ptr<TBitmap>    m_View;

    void            __fastcall  OnKeyChanged(TObject* Sender);
    void            __fastcall  OnThemeChangedEvent(const ThemeChangedEvent& event);
    void            __fastcall  UpdateColors();
    void            __fastcall  OnDocumentSet() override;

public:     // User declarations
                    __fastcall  TfrmEditorControls(TComponent* Owner) override;
};
//---------------------------------------------------------------------------
#endif
