//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fEditorControls.h"
#include "Project/DocumentManager.h"
#include "Project/EditorManager.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "fKeyCapture"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorControls::TfrmEditorControls(TComponent* Owner)
: TFrame(Owner)
{
    m_Registrar.Subscribe<ThemeChangedEvent>(OnThemeChangedEvent);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::SetDocument(Document* document)
{
    m_Document = dynamic_cast<ControlsDocument*>(document);
    kcLeft->KeyCode = m_Document->GetAsciiCode(keyLeft);
    kcRight->KeyCode = m_Document->GetAsciiCode(keyRight);
    kcUp->KeyCode = m_Document->GetAsciiCode(keyUp);
    kcDown->KeyCode = m_Document->GetAsciiCode(keyDown);
    kcFire1->KeyCode = m_Document->GetAsciiCode(keyFire1);
    kcFire2->KeyCode = m_Document->GetAsciiCode(keyFire2);
    kcFire3->KeyCode = m_Document->GetAsciiCode(keyFire3);
    kcOption1->KeyCode = m_Document->GetAsciiCode(keyOption1);
    kcOption2->KeyCode = m_Document->GetAsciiCode(keyOption2);
    kcOption3->KeyCode = m_Document->GetAsciiCode(keyOption3);
    kcOption4->KeyCode = m_Document->GetAsciiCode(keyOption4);

    kcLeft->OnChanged = OnKeyChanged;
    kcRight->OnChanged = OnKeyChanged;
    kcUp->OnChanged = OnKeyChanged;
    kcDown->OnChanged = OnKeyChanged;
    kcFire1->OnChanged = OnKeyChanged;
    kcFire2->OnChanged = OnKeyChanged;
    kcFire3->OnChanged = OnKeyChanged;
    kcOption1->OnChanged = OnKeyChanged;
    kcOption2->OnChanged = OnKeyChanged;
    kcOption3->OnChanged = OnKeyChanged;
    kcOption4->OnChanged = OnKeyChanged;

    ShowKeysHelp();
    UpdateColors();
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::OnKeyChanged(TObject* Sender)
{
         if (Sender == kcLeft   ) m_Document->SetAsciiCode(keyLeft   , kcLeft->KeyCode   );
    else if (Sender == kcRight  ) m_Document->SetAsciiCode(keyRight  , kcRight->KeyCode  );
    else if (Sender == kcUp     ) m_Document->SetAsciiCode(keyUp     , kcUp->KeyCode     );
    else if (Sender == kcDown   ) m_Document->SetAsciiCode(keyDown   , kcDown->KeyCode   );
    else if (Sender == kcFire1  ) m_Document->SetAsciiCode(keyFire1  , kcFire1->KeyCode  );
    else if (Sender == kcFire2  ) m_Document->SetAsciiCode(keyFire2  , kcFire2->KeyCode  );
    else if (Sender == kcFire3  ) m_Document->SetAsciiCode(keyFire3  , kcFire3->KeyCode  );
    else if (Sender == kcOption1) m_Document->SetAsciiCode(keyOption1, kcOption1->KeyCode);
    else if (Sender == kcOption2) m_Document->SetAsciiCode(keyOption2, kcOption2->KeyCode);
    else if (Sender == kcOption3) m_Document->SetAsciiCode(keyOption3, kcOption3->KeyCode);
    else if (Sender == kcOption4) m_Document->SetAsciiCode(keyOption4, kcOption4->KeyCode);
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditorControls::IsActive() const
{
    return theEditorManager.IsActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::ShowKeysHelp()
{
    const String help = "Enter the character for the key or an ASCII code from 1 - 127.\r\nDelete the character to unset it.";
    HelpKeysMessage(help);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
    ShowKeysHelp();
    UpdateColors();
    theEditorManager.SetActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::UpdateColors()
{
    Line1->Brush->Color = ThemeManager::Highlight;
    Line1->Pen->Color = ThemeManager::Highlight;
    Line2->Brush->Color = ThemeManager::Highlight;
    Line2->Pen->Color = ThemeManager::Highlight;
    Line3->Brush->Color = ThemeManager::Highlight;
    Line3->Pen->Color = ThemeManager::Highlight;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::OnThemeChangedEvent(const ThemeChangedEvent& event)
{
    UpdateColors();
}
//---------------------------------------------------------------------------

