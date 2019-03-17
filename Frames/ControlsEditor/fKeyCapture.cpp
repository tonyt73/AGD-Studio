//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
#include "fKeyCapture.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmKeyCode::TfrmKeyCode(TComponent* Owner)
: TFrame(Owner)
, m_KeyCode(0)
, m_NotSet(true)
{
    m_KeyMap[0] = "Not Set";
    m_KeyMap[32] = "Space";
    m_KeyMap[13] = "Enter";
    m_KeyMap[','] = "Comma";
    m_KeyMap['.'] = "Period";
    m_KeyMap[';'] = "Semi-Colon";
    m_KeyMap[9] = "Tab";
    m_KeyMap[27] = "Escape";
}
//---------------------------------------------------------------------------
void __fastcall TfrmKeyCode::edtKeyKeyPress(TObject *Sender, System::WideChar &Key)
{
    if (Key == VK_RETURN)
    {
        auto oldKeyCode = m_KeyCode;
        if (edtKey->Text == "")
        {
            m_NotSet = true;
            m_KeyCode = 0;
        }
        else
        {
            m_NotSet = false;
            if (edtKey->Text.Length() == 1)
            {

                m_KeyCode = edtKey->Text[1];
            }
            else
            {
                m_KeyCode = std::min(127, StrToIntDef(edtKey->Text, 0));
                edtKey->Text = IntToStr(m_KeyCode);
            }
        }
        if (FOnChanged != nullptr && oldKeyCode != m_KeyCode)
        {
            FOnChanged(this);
        }
        UpdateKeyInfo();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmKeyCode::UpdateKeyInfo()
{
    if (m_KeyMap.count(m_KeyCode) == 1)
    {
        lblKey->Caption = m_KeyMap[m_KeyCode];
    }
    else
    {
        lblKey->Caption = UnicodeString::StringOfChar(m_KeyCode, 1);
    }
    if (m_KeyCode)
    {
        lblKey->Caption +=  + " - ASCII: " + IntToStr(m_KeyCode);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmKeyCode::SetKeyCode(unsigned char keyCode)
{
    if (0 <= keyCode and keyCode < 128)
    {
        m_KeyCode = keyCode;
        m_NotSet = keyCode == 0;
        edtKey->Text = UnicodeString::StringOfChar(m_KeyCode, 1);
        UpdateKeyInfo();
        Invalidate();
        Parent->Invalidate();
    }
}
//---------------------------------------------------------------------------
const String& __fastcall TfrmKeyCode::GetCaption()
{
    return panCaption->Caption;
}
//---------------------------------------------------------------------------
void __fastcall TfrmKeyCode::SetCaption(const String& caption)
{
    panCaption->Caption = caption;
}
//---------------------------------------------------------------------------
void __fastcall TfrmKeyCode::edtKeyMouseEnter(TObject *Sender)
{
    ParentBackground = false;
    ParentColor = false;
    Color = edtKey->Focused() ? ThemeManager::Highlight : ThemeManager::Background;
}
//---------------------------------------------------------------------------
void __fastcall TfrmKeyCode::edtKeyMouseLeave(TObject *Sender)
{
    System::WideChar key = VK_RETURN;
    edtKeyKeyPress(Sender, key);
    ParentColor = !edtKey->Focused();
    ParentBackground = !edtKey->Focused();
    UpdateKeyInfo();
}
//---------------------------------------------------------------------------
void __fastcall TfrmKeyCode::edtKeyChange(TObject *Sender)
{
    edtKey->Text = edtKey->Text.UpperCase();
    String text = edtKey->Text;
    if (text.Length() > 1 && StrToIntDef(text, -1) == -1)
    {
        edtKey->Text = text[2];
        edtKey->SelStart = text.Length();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmKeyCode::FrameMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    edtKey->SetFocus();
}
//---------------------------------------------------------------------------

