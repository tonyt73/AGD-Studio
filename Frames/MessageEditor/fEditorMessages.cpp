//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#include "fEditorMessages.h"
#include "Frames/EditorManager.h"
#include "Project/DocumentManager.h"
#include "Settings/ThemeManager.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "fEditorCode"
#pragma link "fMultiImageView"
#pragma resource "*.dfm"
TfrmEditorMessages *frmEditorMessages;
//---------------------------------------------------------------------------
__fastcall TfrmEditorMessages::TfrmEditorMessages(TComponent* Owner)
: TFrame(Owner)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::SetDocument(Document* document)
{
    fFramesView->Timer1->Enabled = false;
    Color = ThemeManager::Background;
    m_Document = document;
    ecMessageEditor->SetDocument(document);

    DocumentList images;
    // TODO: Should take a subtype as well
    theDocumentManager.GetAllOfType("Image", images);
    for (auto image : images)
    {
        auto charset = dynamic_cast<CharacterSetDocument*>(image);
        if (charset)
        {
            fFramesView->Clear();
            const auto& gm = m_GraphicsMode;
            for (auto i = 0; i < charset->Frames; i++)
            {
                // make an image canvas
                auto image = std::make_unique<Agdx::Image>(charset->Width, charset->Height, gm);
                // set the graphic of the canvas from the image documents frame
                image->Canvas().Set(charset->Frame[i]);
                // add the new canvas to the frame view; along with a hint (character set only)
                fFramesView->Add(image->Canvas(), charset->Hint[i]);
            }
            fFramesView->Select(-1);
            break;
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditorMessages::IsActive() const
{
    return theEditorManager.IsActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
    theEditorManager.SetActive(this);
}
//---------------------------------------------------------------------------

