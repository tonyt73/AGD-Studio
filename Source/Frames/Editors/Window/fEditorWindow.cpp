//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "fEditorWindow.h"
#include "EditorManager.h"
#include "Project/Documents/DocumentManager.h"
#include "Settings/ThemeManager.h"
#include "Visuals/GraphicsMode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorWindow::TfrmEditorWindow(TComponent* Owner)
: TfrmEditor(Owner, "Window Editor")
{
    m_KeysHelp =
        "Cursor Keys       : Move Window\r\n"
        "Shift+Cursor Keys : Resize Window\r\n";

    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    const auto& gm = *(mc.GraphicsMode());
    m_View = std::make_unique<TBitmap>();
    m_View->PixelFormat = pf32bit;
    m_View->Width  = static_cast<LONG>(gm.Width ) / mc.ImageSizing[Visuals::itCharacterSet].Minimum.Width;
    m_View->Height = static_cast<LONG>(gm.Height) / mc.ImageSizing[Visuals::itCharacterSet].Minimum.Height;
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::FrameResize(TObject *Sender)
{
    Color = ThemeManager::Background;
    auto s = 8;
    for (; s <= 128; s++)
    {
        auto w = m_View->Width  * s;
        auto h = m_View->Height * s;
        if (w + 32 >= Width || h + 52 > Height)
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
    imgView->Top    = (Height - imgView->Height - sbrWindow->Height) / 2;

    DrawView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::DrawView()
{
    // draw the window area
    auto doc = dynamic_cast<Project::WindowDocument*>(Document);
    if (doc != nullptr && m_View != nullptr)
    {
        m_View->Canvas->Brush->Color = ThemeManager::Background;
        m_View->Canvas->FillRect(TRect(0, 0, m_View->Width, m_View->Height));
        for (auto y = doc->Top; y <= doc->Bottom; y++)
        {
            for (auto x = doc->Left; x <= doc->Right; x++)
            {
                m_View->Canvas->Pixels[x][y] = (y + x) % 2 ? ThemeManager::Highlight : ThemeManager::Foreground;
            }
        }

        imgView->Picture->Bitmap->Width  = imgView->Width;
        imgView->Picture->Bitmap->Height = imgView->Height;
        StretchBlt(imgView->Picture->Bitmap->Canvas->Handle, 0, 0, imgView->Width, imgView->Height, m_View->Canvas->Handle, 0, 0, m_View->Width, m_View->Height, SRCCOPY);

        // draw the character grid
        imgView->Picture->Bitmap->Canvas->Pen->Color = ThemeManager::Shadow;
        for (auto y = 0; y < m_View->Height; y++)
        {
            imgView->Picture->Bitmap->Canvas->MoveTo(0, y * m_Scalar);
            imgView->Picture->Bitmap->Canvas->LineTo(imgView->Picture->Bitmap->Width, y * m_Scalar);
        }
        imgView->Picture->Bitmap->Canvas->MoveTo(0, m_View->Height * m_Scalar - 1);
        imgView->Picture->Bitmap->Canvas->LineTo(imgView->Picture->Bitmap->Width, m_View->Height * m_Scalar - 1);
        for (auto x = 0; x < m_View->Width; x++)
        {
            imgView->Picture->Bitmap->Canvas->MoveTo(x * m_Scalar, 0);
            imgView->Picture->Bitmap->Canvas->LineTo(x * m_Scalar, imgView->Picture->Bitmap->Height);
        }
        imgView->Picture->Bitmap->Canvas->MoveTo(m_View->Width * m_Scalar - 1, 0);
        imgView->Picture->Bitmap->Canvas->LineTo(m_View->Width * m_Scalar - 1, imgView->Picture->Bitmap->Height);
    }
    sbrWindow->Panels->Items[0]->Text = "Left: "   + IntToStr(doc->Left  );
    sbrWindow->Panels->Items[1]->Text = "Top: "    + IntToStr(doc->Top   );
    sbrWindow->Panels->Items[2]->Text = "Right: "  + IntToStr(doc->Right );
    sbrWindow->Panels->Items[3]->Text = "Bottom: " + IntToStr(doc->Bottom);
    sbrWindow->Panels->Items[4]->Text = "Width: "  + IntToStr(doc->Width );
    sbrWindow->Panels->Items[5]->Text = "Height: " + IntToStr(doc->Height);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::imgViewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actMoveLeftExecute(TObject *Sender)
{
    auto doc = dynamic_cast<Project::WindowDocument*>(Document);
    if (doc != nullptr && IsActive() && doc->Left - 1 >= 0)
    {
        doc->SetRect(TRect (doc->Left - 1, doc->Top, doc->Right - 1, doc->Bottom));
        DrawView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actMoveRightExecute(TObject *Sender)
{
    auto doc = dynamic_cast<Project::WindowDocument*>(Document);
    if (doc != nullptr)
    {
        if (IsActive() && doc->Left + doc->Width + 1 <= m_View->Width)
        {
            doc->SetRect(TRect (doc->Left + 1, doc->Top, doc->Right + 1, doc->Bottom));
            DrawView();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actMoveUpExecute(TObject *Sender)
{
    auto doc = dynamic_cast<Project::WindowDocument*>(Document);
    if (doc != nullptr && IsActive() && doc->Top - 1 >= 0)
    {
        doc->SetRect(TRect (doc->Left, doc->Top - 1, doc->Right, doc->Bottom - 1));
        DrawView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actMoveDownExecute(TObject *Sender)
{
    auto doc = dynamic_cast<Project::WindowDocument*>(Document);
    if (doc != nullptr && IsActive() && doc->Top + doc->Height + 1 <= m_View->Height)
    {
        doc->SetRect(TRect (doc->Left, doc->Top + 1, doc->Right, doc->Bottom + 1));
        DrawView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actWidthDecExecute(TObject *Sender)
{
    auto doc = dynamic_cast<Project::WindowDocument*>(Document);
    if (doc != nullptr && IsActive() && doc->Width > 8)
    {
        doc->SetRect(TRect (doc->Left, doc->Top, doc->Right - 1, doc->Bottom));
        DrawView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actWidthIncExecute(TObject *Sender)
{
    auto doc = dynamic_cast<Project::WindowDocument*>(Document);
    if (doc != nullptr && IsActive() && doc->Left + doc->Width + 1 <= m_View->Width)
    {
        doc->SetRect(TRect (doc->Left, doc->Top, doc->Right + 1, doc->Bottom));
        DrawView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actHeightDecExecute(TObject *Sender)
{
    auto doc = dynamic_cast<Project::WindowDocument*>(Document);
    if (doc != nullptr && IsActive() && doc->Height >= 8)
    {
        doc->SetRect(TRect (doc->Left, doc->Top, doc->Right, doc->Bottom - 1));
        DrawView();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actHeightIncExecute(TObject *Sender)
{
    auto doc = dynamic_cast<Project::WindowDocument*>(Document);
    if (doc != nullptr && IsActive() && doc->Top + doc->Height + 1 <= m_View->Height)
    {
        doc->SetRect(TRect (doc->Left, doc->Top, doc->Right, doc->Bottom + 1));
        DrawView();
    }
}
//---------------------------------------------------------------------------

