//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fEditorMessages.h"
#include "EditorManager.h"
#include "Project/Documents/DocumentManager.h"
#include "Messaging/Messaging.h"
#include "Settings/ThemeManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "fEditorCode"
#pragma link "fMultiImageView"
#pragma resource "*.dfm"
TfrmEditorMessages *frmEditorMessages;
//---------------------------------------------------------------------------
__fastcall TfrmEditorMessages::TfrmEditorMessages(TComponent* Owner)
: TfrmEditor(Owner)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
{
    m_Tile = std::make_unique<TImage>(nullptr);
    m_Tile->Width  = 8;
    m_Tile->Height = 8;
    m_Tile->Picture->Bitmap->Width  = 8;
    m_Tile->Picture->Bitmap->Height = 8;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::SetDocument(Project::Document* document)
{
    fFramesView->Timer1->Enabled = false;
    Color = ThemeManager::Background;
    m_Document = document;
    ecMessageEditor->SetDocument(document);

    Project::DocumentList images;
    // TODO: Should take a subtype as well
    theDocumentManager.GetAllOfType("Image", images);
    // find the character set document
    for (auto image : images)
    {
        auto charset = dynamic_cast<Project::CharacterSetDocument*>(image);
        if (charset)
        {
            m_CharacterSet = charset;
            break;
        }
    }
    RefreshCharacterSet();
    RefreshView();
    fFramesView->Select(-1);
    // set the image font to the scroll box font
    imgView->Canvas->Font = sbxView->Font;
    imgView->Canvas->Font->Size = 6;
    imgView->Canvas->Font->Color = ThemeManager::Highlight;
    imgView->Canvas->Brush->Color = clBlack;
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditorMessages::IsActive() const
{
    return theEditorManager.IsActive(ecMessageEditor);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
    theEditorManager.SetActive(ecMessageEditor);
    TfrmEditor::FrameMouseActivate(Sender, Button, Shift, X, Y, HitTest, MouseActivate);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::FrameResize(TObject *Sender)
{
    Color = ThemeManager::Background;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::OnStatusChanged(TLMDCustomEditView *AView, TLMDViewStatusChanges AChanges)
{
    ecMessageEditor->UpdateStatus();
    // refresh the view
    m_RefreshView = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::tmrRefreshViewTimer(TObject *Sender)
{
    // redraw the image view
    RefreshView();
    m_RefreshView = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::RefreshView()
{
    auto scale = 2;
    // work out the size of the view
    auto doc = ecMessageEditor->evEditor->Document;
    auto height = (doc->LinesCount * m_CharacterSet->Height) + (m_CharacterSet->Height * 2);
    auto width = m_GraphicsMode.Width + (m_CharacterSet->Width * 3);
    imgView->Picture->Bitmap->Width = width;
    imgView->Picture->Bitmap->Height = height;
    imgView->Width = width * scale;
    imgView->Height = height * scale;

    // render the view
    PatBlt(imgView->Canvas->Handle, 0, 0, imgView->Width, imgView->Height, BLACKNESS);

    auto xs = m_CharacterSet->Width * 2;
    auto x = xs;
    auto y = m_CharacterSet->Height;
    auto idx = 0;
    auto quote = true;
    for (auto line = 0; line < doc->LinesCount; line++)
    {
        for (auto col = 0; col < doc->LineSegments[line].Count; col++)
        {
            auto seg = doc->LineSegments[line];
            auto chr = seg.Source->Chars[seg.Start + col];
            if (chr == L'\"')
            {
                if (quote)
                {
                    // draw the message index
                    imgView->Canvas->TextOut(0, y - 2, IntToStr(idx++));
                }
                quote = !quote;
            }
            else if (chr >= 32 && chr < 128)
            {
                m_Frames[chr - 32]->Canvas().Assign(m_Tile->Picture->Bitmap);
                imgView->Canvas->Draw(x, y, m_Tile->Picture->Bitmap);
                x += m_CharacterSet->Width;
            }
        }
        y += m_CharacterSet->Height;
        x = xs;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::RefreshCharacterSet()
{
    fFramesView->Clear();
    const auto& gm = m_GraphicsMode;
    for (auto i = 0; i < m_CharacterSet->Frames; i++)
    {
        if (m_Frames.size() < m_CharacterSet->Frames) {
            // make an image canvas
            auto image = std::make_unique<Visuals::Image>(m_CharacterSet->Width, m_CharacterSet->Height, gm);
            // save the image
            m_Frames.push_back(std::move(image));
        }
        // set the graphic of the canvas from the image documents frame
        m_Frames[i]->Canvas().Set(m_CharacterSet->Frame[i]);
        // add the new canvas to the frame view; along with a hint (character set only)
        fFramesView->Add(m_Frames[i]->Canvas(), m_CharacterSet->Hint[i]);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorMessages::sbxViewMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
    if (WheelDelta > 0) {
        sbxView->Perform(WM_VSCROLL, SB_LINEUP, (int)0);
    } else {
        sbxView->Perform(WM_VSCROLL, SB_LINEDOWN, (int)0);
    }
}
//---------------------------------------------------------------------------

