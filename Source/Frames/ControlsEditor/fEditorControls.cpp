//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fEditorControls.h"
#include "Project/DocumentManager.h"
#include "Frames/EditorManager.h"
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
void TfrmEditorControls::SetDocument(Project::Document* document)
{
    m_Document = dynamic_cast<Project::ControlsDocument*>(document);
	kcLeft->KeyCode = m_Document->GetAsciiCode(Project::keyLeft);
	kcRight->KeyCode = m_Document->GetAsciiCode(Project::keyRight);
	kcUp->KeyCode = m_Document->GetAsciiCode(Project::keyUp);
	kcDown->KeyCode = m_Document->GetAsciiCode(Project::keyDown);
	kcFire1->KeyCode = m_Document->GetAsciiCode(Project::keyFire1);
	kcFire2->KeyCode = m_Document->GetAsciiCode(Project::keyFire2);
	kcFire3->KeyCode = m_Document->GetAsciiCode(Project::keyFire3);
	kcOption1->KeyCode = m_Document->GetAsciiCode(Project::keyOption1);
	kcOption2->KeyCode = m_Document->GetAsciiCode(Project::keyOption2);
	kcOption3->KeyCode = m_Document->GetAsciiCode(Project::keyOption3);
    kcOption4->KeyCode = m_Document->GetAsciiCode(Project::keyOption4);

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
		 if (Sender == kcLeft   ) m_Document->SetAsciiCode(Project::keyLeft   , kcLeft->KeyCode   );
	else if (Sender == kcRight  ) m_Document->SetAsciiCode(Project::keyRight  , kcRight->KeyCode  );
	else if (Sender == kcUp     ) m_Document->SetAsciiCode(Project::keyUp     , kcUp->KeyCode     );
	else if (Sender == kcDown   ) m_Document->SetAsciiCode(Project::keyDown   , kcDown->KeyCode   );
	else if (Sender == kcFire1  ) m_Document->SetAsciiCode(Project::keyFire1  , kcFire1->KeyCode  );
	else if (Sender == kcFire2  ) m_Document->SetAsciiCode(Project::keyFire2  , kcFire2->KeyCode  );
	else if (Sender == kcFire3  ) m_Document->SetAsciiCode(Project::keyFire3  , kcFire3->KeyCode  );
	else if (Sender == kcOption1) m_Document->SetAsciiCode(Project::keyOption1, kcOption1->KeyCode);
	else if (Sender == kcOption2) m_Document->SetAsciiCode(Project::keyOption2, kcOption2->KeyCode);
	else if (Sender == kcOption3) m_Document->SetAsciiCode(Project::keyOption3, kcOption3->KeyCode);
    else if (Sender == kcOption4) m_Document->SetAsciiCode(Project::keyOption4, kcOption4->KeyCode);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorControls::OnThemeChangedEvent(const ThemeChangedEvent& event)
{
    UpdateColors();
}
//---------------------------------------------------------------------------
bool TfrmEditorControls::IsActive() const
{
    return theEditorManager.IsActive(this);
}
//---------------------------------------------------------------------------
void TfrmEditorControls::ShowKeysHelp()
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
void TfrmEditorControls::UpdateColors()
{
    Line1->Brush->Color = ThemeManager::Highlight;
    Line1->Pen->Color = ThemeManager::Highlight;
    Line2->Brush->Color = ThemeManager::Highlight;
    Line2->Pen->Color = ThemeManager::Highlight;
    Line3->Brush->Color = ThemeManager::Highlight;
    Line3->Pen->Color = ThemeManager::Highlight;
}
//---------------------------------------------------------------------------

