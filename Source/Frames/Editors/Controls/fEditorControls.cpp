//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fEditorControls.h"
#include "../EditorManager.h"
#include "Project/Documents/DocumentManager.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "fKeyCapture"
#pragma link "fEditor"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorControls::TfrmEditorControls(TComponent* Owner)
: TfrmEditor(Owner)
{
    m_KeysHelp = "Enter the character for the key or an ASCII code from 1 - 127.\r\nDelete the character to unset it.";
    m_Registrar.Subscribe<ThemeChangedEvent>(OnThemeChangedEvent);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::SetDocument(Project::Document* document)
{
    TfrmEditor::SetDocument(document);
    auto doc = dynamic_cast<Project::ControlsDocument*>(document);
    kcLeft->KeyCode = doc->GetAsciiCode(Project::keyLeft);
    kcRight->KeyCode = doc->GetAsciiCode(Project::keyRight);
    kcUp->KeyCode = doc->GetAsciiCode(Project::keyUp);
    kcDown->KeyCode = doc->GetAsciiCode(Project::keyDown);
    kcFire1->KeyCode = doc->GetAsciiCode(Project::keyFire1);
    kcFire2->KeyCode = doc->GetAsciiCode(Project::keyFire2);
    kcFire3->KeyCode = doc->GetAsciiCode(Project::keyFire3);
    kcOption1->KeyCode = doc->GetAsciiCode(Project::keyOption1);
    kcOption2->KeyCode = doc->GetAsciiCode(Project::keyOption2);
    kcOption3->KeyCode = doc->GetAsciiCode(Project::keyOption3);
    kcOption4->KeyCode = doc->GetAsciiCode(Project::keyOption4);

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

    UpdateColors();
    Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::OnKeyChanged(TObject* Sender)
{
    auto doc = dynamic_cast<Project::ControlsDocument*>(m_Document);
         if (Sender == kcLeft   ) doc->SetAsciiCode(Project::keyLeft   , kcLeft->KeyCode   );
    else if (Sender == kcRight  ) doc->SetAsciiCode(Project::keyRight  , kcRight->KeyCode  );
    else if (Sender == kcUp     ) doc->SetAsciiCode(Project::keyUp     , kcUp->KeyCode     );
    else if (Sender == kcDown   ) doc->SetAsciiCode(Project::keyDown   , kcDown->KeyCode   );
    else if (Sender == kcFire1  ) doc->SetAsciiCode(Project::keyFire1  , kcFire1->KeyCode  );
    else if (Sender == kcFire2  ) doc->SetAsciiCode(Project::keyFire2  , kcFire2->KeyCode  );
    else if (Sender == kcFire3  ) doc->SetAsciiCode(Project::keyFire3  , kcFire3->KeyCode  );
    else if (Sender == kcOption1) doc->SetAsciiCode(Project::keyOption1, kcOption1->KeyCode);
    else if (Sender == kcOption2) doc->SetAsciiCode(Project::keyOption2, kcOption2->KeyCode);
    else if (Sender == kcOption3) doc->SetAsciiCode(Project::keyOption3, kcOption3->KeyCode);
    else if (Sender == kcOption4) doc->SetAsciiCode(Project::keyOption4, kcOption4->KeyCode);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::OnThemeChangedEvent(const ThemeChangedEvent& event)
{
    UpdateColors();
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

