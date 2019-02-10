//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include <math.h>
#include "LabelledImage.h"
#include "DocumentManager.h"
#include "Image.h"
#include "BlockColors.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmLabelledImage::TfrmLabelledImage(TComponent* Owner)
: TFrame(Owner)
, m_Document(nullptr)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
{
    panImage->Color = StyleServices()->GetStyleColor(scGenericBackground);
}
//---------------------------------------------------------------------------
void __fastcall TfrmLabelledImage::imgImageClick(TObject *Sender)
{
    SetSelected(true);
    if (FOnClick != nullptr) FOnClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmLabelledImage::SetSelected(bool state)
{
    m_Selected = state;
    panImage->Color = StyleServices()->GetStyleColor(state ? scButtonFocused : scGenericBackground);
    if (state)
    {
        // change all other TfrmImage
        for (int i = 0; i < Parent->ControlCount; i++)
        {
            TfrmLabelledImage* image = dynamic_cast<TfrmLabelledImage*>(Parent->Controls[i]);
            if (image != nullptr && image != this)
            {
                image->Selected = false;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmLabelledImage::SetShowCaption(bool state)
{
    lblCaption->Visible = state;
    imgImage->Left = 0;
    imgImage->Top = state ? 24 : 0;
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmLabelledImage::SetImage(ImageDocument* document)
{
    const String BlockTypes[] = { "Empty", "Platform", "Wall", "Ladder", "Fodder", "Deadly", "Custom" };
    const TColor BlockColor[] = { clGray, clBlue, (TColor)0x00006AFF, clLime, clFuchsia, clRed, clYellow };
    m_Document = document;
    lblCaption->Caption = m_Document->Name;
    panTileType->Visible = false;
    if (document->ImageType == itTile)
    {
        auto st = document->GetLayer("blocktype");
        auto bt = StrToInt(st);
        panTileType->Caption = BlockTypes[bt];
        panTileType->Color = BlockColor[bt];
        panTileType->Visible = true;
    }
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmLabelledImage::Update()
{
    auto w = m_Document->Width;
    auto h = m_Document->Height;
    auto image = std::make_unique<Agdx::Image>(m_Document, m_GraphicsMode);
    auto sx = image->Canvas().ScalarX;
    auto sy = image->Canvas().ScalarY;

    // resize the component based on the size of the image
    for (auto i = 3; i >= 1; i--)
    {
        auto size = pow(2, i);
        if (size * m_Document->Width <= 64 && size * m_Document->Height <= 64)
        {
            w = size * m_Document->Width * sx;
            h = size * m_Document->Height * sy;
            break;
        }
    }

    // Draw the image
    image->Canvas().Assign(imgImage->Picture->Bitmap);
    image->Canvas().Draw(imgImage->Picture->Bitmap);

    panImage->Width = w;
    panImage->Height = h + (lblCaption->Visible ? lblCaption->Height : 0) + (panTileType->Visible ? panTileType->Height : 0);
}
//---------------------------------------------------------------------------

