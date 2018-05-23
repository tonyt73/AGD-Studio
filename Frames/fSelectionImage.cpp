//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "fSelectionImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSelectionImageFrame::TSelectionImageFrame(TComponent* Owner, const Agdx::GraphicsBuffer& image)
: TFrame(Owner)
, m_Image(image)
, m_Selected(false)
, m_Scale(4)
, FOnClick(nullptr)
{
}
//---------------------------------------------------------------------------
void __fastcall TSelectionImageFrame::Update()
{
    m_Image.Assign(imgBitmap->Picture->Bitmap);
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
    Color = m_Selected ? StyleServices()->GetStyleColor(scButtonHot) : StyleServices()->GetStyleColor(scPanel);
}
//---------------------------------------------------------------------------
void __fastcall TSelectionImageFrame::SetScale(int scale)
{
    m_Scale = scale;
    Width  = (scale * imgBitmap->Picture->Bitmap->Width ) + Padding->Left + Padding->Right;
    Height = (scale * imgBitmap->Picture->Bitmap->Height) + Padding->Top  + Padding->Bottom;
    Color = m_Selected ? StyleServices()->GetStyleColor(scButtonHot) : StyleServices()->GetStyleColor(scPanel);
}
//---------------------------------------------------------------------------
void __fastcall TSelectionImageFrame::imgBitmapClick(TObject *Sender)
{
    Selected = true;
    if (FOnClick != nullptr) FOnClick(this);
}
//---------------------------------------------------------------------------
