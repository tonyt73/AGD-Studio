//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "fSelectionImage.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSelectionImageFrame::TSelectionImageFrame(TComponent* Owner, const Visuals::GraphicsBuffer& image, const String& hint)
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
    m_Image.Assign(imgBitmap->Picture->Bitmap);
    panHint->Caption = m_Hint;
    panHint->Visible = m_Hint != "";
    ShowHint = false;
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
                static_cast<TSelectionImageFrame*>(control)->Selected = false;
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
    auto hh = panHint->Visible ? Padding->Bottom + panHint->Height : 0;
    Width  = static_cast<int>(m_ScalarX * static_cast<float>(scale) * static_cast<float>(imgBitmap->Picture->Bitmap->Width )) + Padding->Left + Padding->Right;
    Height = static_cast<int>(m_ScalarY * static_cast<float>(scale) * static_cast<float>(imgBitmap->Picture->Bitmap->Height)) + Padding->Top  + Padding->Bottom + hh;
    Color = m_Selected ? ThemeManager::Highlight : ThemeManager::Background;
}
//---------------------------------------------------------------------------
void __fastcall TSelectionImageFrame::imgBitmapClick(TObject* /*Sender*/)
{
    Selected = true;
    if (FOnClick != nullptr) FOnClick(this);
}
//---------------------------------------------------------------------------
