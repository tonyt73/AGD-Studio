//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fSelectionImage.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSelectionImageFrame::TSelectionImageFrame(TComponent* Owner, const Agdx::GraphicsBuffer& image, const String& hint)
: TFrame(Owner)
, m_Image(image)
, m_Hint(hint)
, m_Selected(false)
, m_Scale(4)
, m_ScalarX(image.ScalarX)
, m_ScalarY(image.ScalarY)
, FOnClick(nullptr)
{
}
//---------------------------------------------------------------------------
void __fastcall TSelectionImageFrame::Update()
{
    Hint = m_Hint;
    m_Image.Assign(imgBitmap->Picture->Bitmap);
    imgBitmap->Hint = Hint;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionImageFrame::SetSelected(bool state)
{
    if (state)
    {
        // turn all the selections off
        for (auto i = 0; i < Parent->ControlCount; i++)
        {
            auto control = Parent->Controls[i];
            if (control != this && control->ClassNameIs("TSelectionImageFrame"))
            {
                ((TSelectionImageFrame*)control)->Selected = false;
            }
        }
    }
    m_Selected = state;
    Color = m_Selected ? ThemeManager::Highlight : ThemeManager::Background;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionImageFrame::SetScale(int scale)
{
    m_Scale = scale;
    Width  = (m_ScalarX * scale * imgBitmap->Picture->Bitmap->Width ) + Padding->Left + Padding->Right;
    Height = (m_ScalarY * scale * imgBitmap->Picture->Bitmap->Height) + Padding->Top  + Padding->Bottom;
    Color = m_Selected ? ThemeManager::Highlight : ThemeManager::Background;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionImageFrame::imgBitmapClick(TObject *Sender)
{
    Selected = true;
    if (FOnClick != nullptr) FOnClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TSelectionImageFrame::imgBitmapMouseEnter(TObject *Sender)
{
    for (int index = 0; index < Application->ComponentCount; ++index)
    {
        THintWindow *HintWindow = dynamic_cast<THintWindow *>(Application->Components[index]);
        if (HintWindow)
        {
            HintWindow->Canvas->Font->Name = Font->Name;
            HintWindow->Canvas->Font->Size = Font->Size;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TSelectionImageFrame::imgBitmapMouseLeave(TObject *Sender)
{
    for (int index = 0; index < Application->ComponentCount; ++index)
    {
        THintWindow *HintWindow = dynamic_cast<THintWindow *>(Application->Components[index]);
        if (HintWindow)
        {
            HintWindow->Canvas->Font->Name = "Tahoma";
            HintWindow->Canvas->Font->Size = 8;
        }
    }
}
//---------------------------------------------------------------------------
