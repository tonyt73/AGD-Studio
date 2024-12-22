//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "fLabelledImage.h"
#include "Visuals/BlockTypes.h"
#include "Project/Documents/DocumentManager.h"
#include "Settings/ThemeManager.h"
#include "Visuals/BlockTypes.h"
#include "Visuals/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
 TfrmLabelledImage::TfrmLabelledImage(TComponent* Owner)
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
void __fastcall TfrmLabelledImage::imgImageDblClick(TObject *Sender)
{
    SetSelected(true);
    if (FOnDblClick != nullptr) FOnDblClick(this);
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
void __fastcall TfrmLabelledImage::SetImage(Project::ImageDocument* document)
{
    m_Document           = document;
    lblCaption->Caption  = m_Document->Name.UpperCase();
    panTileType->Visible = false;

    if (document->ImageType == Visuals::itTile) {
        auto bt = -1;
        auto st = document->GetLayer("blocktype");
        if (st.Length() == 1) {
            // single tile, proper caption and tile color
            bt = StrToInt(st);
            panTileType->Caption  = g_BlockTypes[bt].UpperCase();
        } else {
            // tile set, caption is the most used block type
            std::map<int, int> counts;
            for (auto chr : st) {
                if (counts.count(chr-'0') == 0) {
                    counts[chr-'0'] = 0;
                }
                counts[chr-'0']++;
            }
            auto bt = 0;
            auto max = -1;
            for (const auto& [key, count] : counts) {
                if (max < count) {
                    bt = key;
                    max = count;
                }
            }
            panTileType->Caption = g_BlockTypes[bt].UpperCase();
        }
        panTileType->Color   = g_BlockColors[bt];
        panTileType->Visible = true;
    }
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmLabelledImage::Update()
{
    auto iw    = m_Document->Width;
    auto ih    = m_Document->Height;
    auto image = std::make_unique<Visuals::Image>(m_Document, m_GraphicsMode);
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

