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
#include "Project/ControlsDocument.h"
#include "Messaging/Messaging.h"
#include "Messaging/Event.h"
#include "fKeyCapture.h"
//---------------------------------------------------------------------------
class TfrmEditorControls : public TFrame
{
__published:// IDE-managed Components
    TfrmKeyCode *kcOption1;
    TfrmKeyCode *kcOption2;
    TfrmKeyCode *kcOption3;
    TfrmKeyCode *kcOption4;
    TfrmKeyCode *kcFire1;
    TfrmKeyCode *kcFire2;
    TfrmKeyCode *kcFire3;
    TfrmKeyCode *kcLeft;
    TfrmKeyCode *kcRight;
    TfrmKeyCode *kcUp;
    TfrmKeyCode *kcDown;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TShape *Line1;
    TShape *Line2;
    TShape *Line3;
    void __fastcall FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate);
private:    // User declarations
    ::Messaging::Registrar      m_Registrar;
    ControlsDocument*           m_Document;
    std::unique_ptr<TBitmap>    m_View;

    void            __fastcall  OnKeyChanged(TObject* Sender);
    bool            __fastcall  IsActive() const;
    void            __fastcall  SetDocument(Document* document);
    void            __fastcall  ShowKeysHelp();
    void            __fastcall  UpdateColors();
    void            __fastcall  OnThemeChangedEvent(const ThemeChangedEvent& event);

public:        // User declarations
                    __fastcall  TfrmEditorControls(TComponent* Owner);
    static  TFrame* __fastcall  Create(Document* document, TComponent* owner)
                                {
                                    auto editor = new TfrmEditorControls(owner);
                                    editor->SetDocument(document);
                                    document->DockPanel = dynamic_cast<TLMDDockPanel*>(owner);
                                    return editor;
                                }
};
//---------------------------------------------------------------------------
#endif
