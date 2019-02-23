//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "fEditorWindow.h"
#include "Project/DocumentManager.h"
#include "Project/EditorManager.h"
#include "Graphics/GraphicsMode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmEditorWindow::TfrmEditorWindow(TComponent* Owner)
: TFrame(Owner)
{
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    const auto& gm = *(mc.GraphicsMode());
    m_WindowView = make_unique<TBitmap>();
    m_WindowView->PixelFormat = pf32bit;
    m_WindowView->Width = gm.Width / mc.ImageSizing[itCharacterSet].Minimum.Width;
    m_WindowView->Height = gm.Height / mc.ImageSizing[itCharacterSet].Minimum.Height;

    m_Registrar.Subscribe<Event>(OnEvent);
}
//---------------------------------------------------------------------------
__fastcall TfrmEditorWindow::~TfrmEditorWindow()
{
    m_Registrar.Unsubscribe();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::FrameResize(TObject *Sender)
{
    Color = StyleServices()->GetStyleColor(scGenericGradientBase);
    auto s = 8;
    for (; s <= 128; s++)
    {
        auto w = m_WindowView->Width  * s;
        auto h = m_WindowView->Height * s;
        if (w + 32 >= Width || h + 52 > Height)
        {
            s--;
            break;
        }
    }
    // center view window
    m_Scalar = s;
    imgView->Width  = m_WindowView->Width  * s;
    imgView->Height = m_WindowView->Height * s;
    imgView->Left   = (Width  - imgView->Width ) / 2;
    imgView->Top    = (Height - imgView->Height - sbrWindow->Height) / 2;

    DrawWindow();
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::DrawWindow()
{
    // draw the window area
    if (m_WindowView != nullptr)
    {
        m_WindowView->Canvas->Brush->Color = clGray;
        m_WindowView->Canvas->FillRect(TRect(0, 0, m_WindowView->Width, m_WindowView->Height));
        for (auto y = m_WindowDocument->Top; y <= m_WindowDocument->Bottom; y++)
        {
            for (auto x = m_WindowDocument->Left; x <= m_WindowDocument->Right; x++)
            {
                m_WindowView->Canvas->Pixels[x][y] = (y + x) % 2 ? clRed : clWhite;
            }
        }

        imgView->Picture->Bitmap->Width  = imgView->Width;
        imgView->Picture->Bitmap->Height = imgView->Height;
        StretchBlt(imgView->Picture->Bitmap->Canvas->Handle, 0, 0, imgView->Width, imgView->Height, m_WindowView->Canvas->Handle, 0, 0, m_WindowView->Width, m_WindowView->Height, SRCCOPY);

        // draw the character grid
        imgView->Picture->Bitmap->Canvas->Pen->Color = (TColor)0x00004080;   // a kind of light brown/yellow
        for (auto y = 0; y < m_WindowView->Height; y++)
        {
            imgView->Picture->Bitmap->Canvas->MoveTo(0, y * m_Scalar);
            imgView->Picture->Bitmap->Canvas->LineTo(imgView->Picture->Bitmap->Width, y * m_Scalar);
        }
        for (auto x = 0; x < m_WindowView->Width; x++)
        {
            imgView->Picture->Bitmap->Canvas->MoveTo(x * m_Scalar, 0);
            imgView->Picture->Bitmap->Canvas->LineTo(x * m_Scalar, imgView->Picture->Bitmap->Height);
        }
    }
    sbrWindow->Panels->Items[0]->Text = "Left: "   + IntToStr(m_WindowDocument->Left  );
    sbrWindow->Panels->Items[1]->Text = "Top: "    + IntToStr(m_WindowDocument->Top   );
    sbrWindow->Panels->Items[2]->Text = "Right: "  + IntToStr(m_WindowDocument->Right );
    sbrWindow->Panels->Items[3]->Text = "Bottom: " + IntToStr(m_WindowDocument->Bottom);
    sbrWindow->Panels->Items[4]->Text = "Width: "  + IntToStr(m_WindowDocument->Width );
    sbrWindow->Panels->Items[5]->Text = "Height: " + IntToStr(m_WindowDocument->Height);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::SetDocument(Document* document)
{
    m_WindowDocument = dynamic_cast<WindowDocument*>(document);
    ShowKeysHelp();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmEditorWindow::IsActive() const
{
    return theEditorManager.IsActive(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::OnEvent(const Event& event)
{
    if (IsActive())
    {
        ShowKeysHelp();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::ShowKeysHelp()
{
    const String help =
        "Cursor Keys       : Move Window\r\n"
        "Shift+Cursor Keys : Resize Window\r\n";
    ::Messaging::Bus::Publish<MessageEvent>(HelpKeysMessageEvent(help));
}
//---------------------------------------------------------------------------
MESSAGE void __fastcall TfrmEditorWindow::WMGetDlgCode(TMessage& msg)
{
    TFrame::Dispatch(&msg);
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::imgViewMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    //
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actMoveLeftExecute(TObject *Sender)
{
    if (IsActive() && m_WindowDocument->Left - 1 >= 0)
    {
        m_WindowDocument->Set(TRect (m_WindowDocument->Left - 1, m_WindowDocument->Top, m_WindowDocument->Right - 1, m_WindowDocument->Bottom));
        DrawWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actMoveRightExecute(TObject *Sender)
{
    auto w = m_WindowDocument->Width;
    if (IsActive() && m_WindowDocument->Left + w + 1 < m_WindowView->Width)
    {
        m_WindowDocument->Set(TRect (m_WindowDocument->Left + 1, m_WindowDocument->Top, m_WindowDocument->Right + 1, m_WindowDocument->Bottom));
        DrawWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actMoveUpExecute(TObject *Sender)
{
    if (IsActive() && m_WindowDocument->Top - 1 >= 0)
    {
        m_WindowDocument->Set(TRect (m_WindowDocument->Left, m_WindowDocument->Top - 1, m_WindowDocument->Right, m_WindowDocument->Bottom - 1));
        DrawWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actMoveDownExecute(TObject *Sender)
{
    auto h = m_WindowDocument->Height;
    if (IsActive() && m_WindowDocument->Top + h + 1 < m_WindowView->Height)
    {
        m_WindowDocument->Set(TRect (m_WindowDocument->Left, m_WindowDocument->Top + 1, m_WindowDocument->Right, m_WindowDocument->Bottom + 1));
        DrawWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actWidthDecExecute(TObject *Sender)
{
    if (IsActive() && m_WindowDocument->Width > 8)
    {
        m_WindowDocument->Set(TRect (m_WindowDocument->Left, m_WindowDocument->Top, m_WindowDocument->Right - 1, m_WindowDocument->Bottom));
        DrawWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actWidthIncExecute(TObject *Sender)
{
    if (IsActive() && m_WindowDocument->Left + m_WindowDocument->Width + 1 < m_WindowView->Width)
    {
        m_WindowDocument->Set(TRect (m_WindowDocument->Left, m_WindowDocument->Top, m_WindowDocument->Right + 1, m_WindowDocument->Bottom));
        DrawWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actHeightDecExecute(TObject *Sender)
{
    if (IsActive() && m_WindowDocument->Height >= 8)
    {
        m_WindowDocument->Set(TRect (m_WindowDocument->Left, m_WindowDocument->Top, m_WindowDocument->Right, m_WindowDocument->Bottom - 1));
        DrawWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::actHeightIncExecute(TObject *Sender)
{
    if (IsActive() && m_WindowDocument->Top + m_WindowDocument->Height + 1 < m_WindowView->Height)
    {
        m_WindowDocument->Set(TRect (m_WindowDocument->Left, m_WindowDocument->Top, m_WindowDocument->Right, m_WindowDocument->Bottom + 1));
        DrawWindow();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmEditorWindow::FrameMouseActivate(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y, int HitTest, TMouseActivate &MouseActivate)
{
    theEditorManager.SetActive(this);
}
//---------------------------------------------------------------------------

