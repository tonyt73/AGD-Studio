//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl.imaging.pngimage.hpp>
#include <algorithm>
#include <memory>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "fMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
: TForm(Owner)
, m_EditMode(emSelect)
, m_Scale(1.f)
, m_Keyboard(new TPngImage())
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormResize(TObject *Sender)
{
    if (actZoomFit->Checked && m_Keyboard->Width > 0)
    {
        float sW = panView->ClientWidth  / (float)m_Keyboard->Width;
        float sH = panView->ClientHeight / (float)m_Keyboard->Height;
        m_Scale = (sW < sH) ? sW : sH;
    }

    imgView->Width  = m_Keyboard->Width  * m_Scale;
    imgView->Height = m_Keyboard->Height * m_Scale;
    imgView->Left = (panView->ClientWidth  - imgView->Width ) / 2;
    imgView->Top  = (panView->ClientHeight - imgView->Height) / 2;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actFileNewExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actFileOpenAccept(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actFileSaveExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actAddKeyboardExecute(TObject *Sender)
{
    if (dlgOpen->Execute() == mrOk)
    {
        m_Keyboard->LoadFromFile(dlgOpen->FileName);
        imgView->AutoSize = true;
        imgView->Picture->Assign(m_Keyboard);
        FormResize(nullptr);
        imgView->AutoSize = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actModeSelectExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actModeRectangleExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actZoomInExecute(TObject *Sender)
{
    actZoomFit->Checked = false;
    m_Scale = std::min(5.f, m_Scale + 0.5f);
    FormResize(nullptr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actZoomOutExecute(TObject *Sender)
{
    actZoomFit->Checked = false;
    m_Scale = std::max(1.f, m_Scale - 0.5f);
    FormResize(nullptr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actZoomActualExecute(TObject *Sender)
{
    actZoomFit->Checked = false;
    m_Scale = 1.f;
    FormResize(nullptr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actZoomFitExecute(TObject *Sender)
{

    FormResize(nullptr);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::actModeTestExecute(TObject *Sender)
{
    //
}
//---------------------------------------------------------------------------
