//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#include <math.h>
#include "LabelledImage.h"
#include "Project/DocumentManager.h"
#include "Settings/ThemeManager.h"
#include "Graphics/Image.h"
#include "Frames/ImageEditor/BlockColors.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmLabelledImage::TfrmLabelledImage(TComponent* Owner)
: TFrame(Owner)
, m_Document(nullptr)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
{
    panImage->Color = ThemeManager::Background;
}
//---------------------------------------------------------------------------
void __fastcall TfrmLabelledImage::imgImageClick(TObject* Sender)
{
    SetSelected(true);
    if (FOnClick != nullptr) FOnClick(this);
}
//---------------------------------------------------------------------------
//TStyleColor
//  scBorder,
//  scButtonDisabled, scButtonFocused, scButtonHot, scButtonNormal, scButtonPressed,
//  scCategoryButtons, scCategoryButtonsGradientBase, scCategoryButtonsGradientEnd, scCategoryPanelGroup,
//  scComboBox, scComboBoxDisabled,
//  scEdit, scEditDisabled, scGrid,
//  scGenericBackground, scGenericGradientBase, scGenericGradientEnd,
//  scHintGradientBase, scHintGradientEnd, scListBox, scListBoxDisabled, scListView, scPanel, scPanelDisabled, scSplitter, scToolBarGradientBase, scToolBarGradientEnd, scTreeView, scWindow
void __fastcall TfrmLabelledImage::SetSelected(bool state)
{
    m_Selected = state;

    panImage->Color = state ? ThemeManager::Highlight : ThemeManager::Background;
    if (state) {
        // change all other TfrmImage
        for (int i = 0; i < Parent->ControlCount; i++) {
            TfrmLabelledImage* image = dynamic_cast<TfrmLabelledImage*>(Parent->Controls[i]);
            if (image != nullptr && image != this) {
                image->Selected = false;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmLabelledImage::SetShowCaption(bool state)
{
    lblCaption->Visible = state;
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmLabelledImage::SetImage(ImageDocument* document)
{
    const String BlockTypes[] = { "Empty", "Platform", "Wall", "Ladder", "Fodder", "Deadly", "Custom" };
    const TColor BlockColor[] = { clGray, clBlue, (TColor)0x00006AFF, clLime, clFuchsia, clRed, clYellow };
    m_Document                = document;
    lblCaption->Caption       = m_Document->Name.UpperCase();
    panTileType->Visible      = false;

    if (document->ImageType  == itTile) {
        auto st               = document->GetLayer("blocktype");
        auto bt               = StrToInt(st);
        panTileType->Caption  = BlockTypes[bt].UpperCase();
        panTileType->Color    = BlockColor[bt];
        panTileType->Visible  = true;
    }
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmLabelledImage::Update()
{
    auto iw    = m_Document->Width;
    auto ih    = m_Document->Height;
    auto image = std::make_unique<Agdx::Image>(m_Document, m_GraphicsMode);
    auto sx    = image->Canvas().ScalarX;
    auto sy    = image->Canvas().ScalarY;

    // resize the component based on the size of the image
    for (auto i = 3; i >= 1; i--) {
        auto size = pow(2, i);
        if (size * m_Document->Width <= 32 && size * m_Document->Height <= 32) {
            iw = size * m_Document->Width * sx;
            ih = size * m_Document->Height * sy;
            break;
        }
    }

    // Draw the image
    image->Canvas().Assign(imgImage->Picture->Bitmap);
    image->Canvas().Draw(imgImage->Picture->Bitmap);

    Height = imgImage->Width + (lblCaption->Visible ? lblCaption->Height : 0) + (panTileType->Visible ? panTileType->Height : 0);
}
//---------------------------------------------------------------------------

