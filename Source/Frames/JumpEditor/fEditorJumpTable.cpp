//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fEditorJumpTable.h"
#include "Project/DocumentManager.h"
#include "Frames/EditorManager.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorJumpTable::TfrmEditorJumpTable(TComponent* Owner)
: TFrame(Owner)
, m_ActiveStep(0)
{
    m_View = make_unique<TBitmap>();
    m_View->PixelFormat = pf32bit;
    m_View->Width = 256;
    m_View->Height = 192;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorJumpTable::SetDocument(Project::Document* document)
{
    m_Document = dynamic_cast<Project::JumpTableDocument*>(document);
    ShowKeysHelp();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditorJumpTable::IsActive() const
{
    return theEditorManager.IsActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorJumpTable::ShowKeysHelp()
{
    const String help =
        "Left/Right Cursor Keys : Move Active Step\r\n"
        "Up/Down Cursor Keys    : Adjust Step Value\r\n";
    HelpKeysMessage(help);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorJumpTable::FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
    ShowKeysHelp();
    theEditorManager.SetActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorJumpTable::FrameResize(TObject *Sender)
{
    Color = ThemeManager::Background;
    auto s = 2;
    for (; s <= 128; s++)
    {
        auto w = m_View->Width  * s;
        auto h = m_View->Height * s;
        if (w + 32 >= Width || h + 32 > Height)
        {
            s--;
            break;
        }
    }
    // center view window
    m_Scalar = s;
    imgView->Width  = m_View->Width  * s;
    imgView->Height = m_View->Height * s;
    imgView->Left   = (Width  - imgView->Width ) / 2;
    imgView->Top    = (Height - imgView->Height) / 2;

    imgView->Picture->Bitmap->Width  = imgView->Width;
    imgView->Picture->Bitmap->Height = imgView->Height;

    DrawView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorJumpTable::DrawView()
{
    // draw the window area
    if (m_View != nullptr)
    {
        m_View->Canvas->Brush->Color = ThemeManager::Background;
        m_View->Canvas->FillRect(TRect(0, 0, m_View->Width, m_View->Height));
        auto x = 0;
        auto y = 80;
        m_View->Canvas->Pen->Color = ThemeManager::Foreground;
        m_View->Canvas->Brush->Color = ThemeManager::Highlight;
        for (auto i = -1; i < m_Document->Count; i++)
        {
            y += m_Document->GetStep(i);

            if (i == m_ActiveStep)
            {
                m_View->Canvas->FillRect(TRect(x, 0, x + 8, 192));
            }

            m_View->Canvas->MoveTo(x, y);
            m_View->Canvas->LineTo(x + 8, y);

            x += 8;
        }
        StretchBlt(imgView->Picture->Bitmap->Canvas->Handle, 0, 0, imgView->Width, imgView->Height, m_View->Canvas->Handle, 0, 0, m_View->Width, m_View->Height, SRCCOPY);
        imgView->Refresh();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorJumpTable::actLeftExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_ActiveStep = std::max(0, m_ActiveStep - 1);
        DrawView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorJumpTable::actRightExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_ActiveStep = std::min(m_Document->Count - 1, m_ActiveStep + 1);
        DrawView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorJumpTable::actUpExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_Document->SetStep(m_ActiveStep, m_Document->GetStep(m_ActiveStep) - 1);
        DrawView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorJumpTable::actDownExecute(TObject *Sender)
{
    if (IsActive())
    {
        m_Document->SetStep(m_ActiveStep, m_Document->GetStep(m_ActiveStep) + 1);
        DrawView();
    }
}
//---------------------------------------------------------------------------

