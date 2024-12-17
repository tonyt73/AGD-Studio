//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "fPaletteBitmap.h"
#include "Project/Documents/DocumentManager.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
const auto c_box = 20;  // size of the colour picker boxes
//---------------------------------------------------------------------------
__fastcall TfrmPaletteBitmap::TfrmPaletteBitmap(TComponent* Owner)
: TFrame(Owner)
, m_Pen(1)
, m_Brush(0)
, m_CursorLogical(-1)
, m_CursorPhysical(-1)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
, m_Palette(m_GraphicsMode.Palette())
{
    m_LogicalPicker = std::make_unique<TBitmap>();
    m_LogicalPicker->PixelFormat = pf32bit;
    m_PhysicalPicker = std::make_unique<TBitmap>();
    m_PhysicalPicker->PixelFormat = pf32bit;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::Init()
{
    Update();
    panSystemColorPicker->Visible = m_GraphicsMode.SupportsLogicalColorRemapping;
    btnPaletteLoad->Enabled = m_GraphicsMode.SupportsLogicalColorRemapping;
    btnPaletteSave->Enabled = m_GraphicsMode.SupportsLogicalColorRemapping;
    btnPaletteRestore->Enabled = m_GraphicsMode.SupportsLogicalColorRemapping;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::DrawPhysicalColors() const
{
    // setup the colour pickers
    const auto totalColors = m_Palette.Colors;
    // calculate the number of rows
    auto cols = imgSystemColors->Width / c_box;
    auto rows = totalColors / cols;
    // setup the picker image
    if (m_PhysicalPicker->Width == 0)
    {
        // work out the size of the picker control
        auto hh = lblSystemColor->Height + ((rows + 1) * c_box);
        panSystemColorPicker->Height = hh;
        m_PhysicalPicker->Width = imgSystemColors->Width;
        m_PhysicalPicker->Height = hh + 1;
        imgSystemColors->Picture->Bitmap->PixelFormat = pf32bit;
        imgSystemColors->Picture->Bitmap->Width = m_PhysicalPicker->Width;
        imgSystemColors->Picture->Bitmap->Height = m_PhysicalPicker->Height;
    }
    // clear the bitmap
    m_PhysicalPicker->Canvas->Brush->Color = TColor(0xFF000000);
    m_PhysicalPicker->Canvas->FillRect(TRect(0, 0, m_PhysicalPicker->Width, m_PhysicalPicker->Height));
    // draw the physical colours
    for (auto i = 0; i < totalColors; i++)
    {
        auto c = i % cols;
        auto r = i / cols;
        auto x = c * c_box;
        auto y = r * c_box;
        m_PhysicalPicker->Canvas->Brush->Color = m_Palette.Color[i];
        m_PhysicalPicker->Canvas->FillRect(TRect(x, y, x + c_box, y + c_box));
        if (i == m_CursorPhysical)
        {
            auto xs = x;
            auto ys = y;
            auto xe = x + c_box - 1;
            auto ye = y + c_box -1;
            m_PhysicalPicker->Canvas->Pen->Color = clBlack;
            m_PhysicalPicker->Canvas->MoveTo(xs, ys);
            m_PhysicalPicker->Canvas->LineTo(xe, ys);
            m_PhysicalPicker->Canvas->LineTo(xe, ye);
            m_PhysicalPicker->Canvas->LineTo(xs, ye);
            m_PhysicalPicker->Canvas->LineTo(xs, ys);

            xs++;
            ys++;
            xe -= 2;
            ye -= 2;
            m_PhysicalPicker->Canvas->Pen->Color = clWhite;
            m_PhysicalPicker->Canvas->MoveTo(xs, ys);
            m_PhysicalPicker->Canvas->LineTo(xe, ys);
            m_PhysicalPicker->Canvas->LineTo(xe, ye);
            m_PhysicalPicker->Canvas->LineTo(xs, ye);
            m_PhysicalPicker->Canvas->LineTo(xs, ys);
        }
    }
    BitBlt(imgSystemColors->Picture->Bitmap->Canvas->Handle, 0, 0, m_PhysicalPicker->Width, m_PhysicalPicker->Height, m_PhysicalPicker->Canvas->Handle, 0, 0, SRCCOPY);
    imgSystemColors->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::DrawLogicalColors() const
{
    // draw the logical colours
    // setup the colour pickers
    const auto totalColors = m_GraphicsMode.LogicalColors;
    // calculate the number of rows
    auto cols = imgLogicalColors->Width / c_box;
    auto rows = totalColors / cols;
    // setup the picker image
    if (m_LogicalPicker->Width == 0)
    {
        auto hh = lblLogicalColor->Height + ((rows + 1) * c_box);
        panLogicalColorPicker->Height = hh;
        m_LogicalPicker->Width = imgLogicalColors->Width;
        m_LogicalPicker->Height = hh + 1;
        imgLogicalColors->Picture->Bitmap->Width = m_LogicalPicker->Width;
        imgLogicalColors->Picture->Bitmap->Height = m_LogicalPicker->Height;
        imgLogicalColors->Picture->Bitmap->PixelFormat = pf32bit;
    }
    // clear the bitmap
    m_LogicalPicker->Canvas->Brush->Color = TColor(0xFF000000);
    m_LogicalPicker->Canvas->FillRect(TRect(0, 0, m_LogicalPicker->Width, m_LogicalPicker->Height));
    // draw the physical colours
    for (auto i = 0; i < totalColors; i++)
    {
        auto c = i % cols;
        auto r = i / cols;
        auto x = c * c_box;
        auto y = r * c_box;
        m_LogicalPicker->Canvas->Brush->Color = m_GraphicsMode.LogicalColor[i];
        m_LogicalPicker->Canvas->FillRect(TRect(x, y, x + c_box, y + c_box));
        if (i == m_CursorLogical)
        {
            auto xs = x;
            auto ys = y;
            auto xe = x + c_box - 1;
            auto ye = y + c_box -1;
            m_LogicalPicker->Canvas->Pen->Color = clBlack;
            m_LogicalPicker->Canvas->MoveTo(xs, ys);
            m_LogicalPicker->Canvas->LineTo(xe, ys);
            m_LogicalPicker->Canvas->LineTo(xe, ye);
            m_LogicalPicker->Canvas->LineTo(xs, ye);
            m_LogicalPicker->Canvas->LineTo(xs, ys);

            xs++;
            ys++;
            xe -= 2;
            ye -= 2;
            m_LogicalPicker->Canvas->Pen->Color = clWhite;
            m_LogicalPicker->Canvas->MoveTo(xs, ys);
            m_LogicalPicker->Canvas->LineTo(xe, ys);
            m_LogicalPicker->Canvas->LineTo(xe, ye);
            m_LogicalPicker->Canvas->LineTo(xs, ye);
            m_LogicalPicker->Canvas->LineTo(xs, ys);
        }
        if (m_Pen == i)
        {
            // draw L
            auto size = imgLogicalColors->Picture->Bitmap->Canvas->TextExtent("L");
            auto tx = x + ((c_box - size.cx) >> 1);
            auto ty = y + ((c_box - size.cy) >> 1);
            m_LogicalPicker->Canvas->Font->Color = m_Palette.FontColorOf[m_GraphicsMode.FromLogicalColor[i]];
            m_LogicalPicker->Canvas->TextOut(tx, ty, "L");
        }
        else if (m_Brush == i)
        {
            // draw R
            auto size = imgLogicalColors->Picture->Bitmap->Canvas->TextExtent("R");
            auto tx = x + ((c_box - size.cx) >> 1);
            auto ty = y + ((c_box - size.cy) >> 1);
            m_LogicalPicker->Canvas->Font->Color = m_Palette.FontColorOf[m_GraphicsMode.FromLogicalColor[i]];
            m_LogicalPicker->Canvas->TextOut(tx, ty, "R");
        }
    }
    BitBlt(imgLogicalColors->Picture->Bitmap->Canvas->Handle, 0, 0, m_LogicalPicker->Width, m_LogicalPicker->Height, m_LogicalPicker->Canvas->Handle, 0, 0, SRCCOPY);
    imgLogicalColors->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::Update()
{
    DrawPhysicalColors();
    DrawLogicalColors();
    panColorL->Color = m_GraphicsMode.LogicalColor[m_Pen];
    panColorR->Color = m_GraphicsMode.LogicalColor[m_Brush];
    panColorL->Font->Color = m_Palette.FontColorOf[m_GraphicsMode.FromLogicalColor[m_Pen]];
    panColorR->Font->Color = m_Palette.FontColorOf[m_GraphicsMode.FromLogicalColor[m_Brush]];
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::Set(Visuals::GraphicsBuffer& canvas)
{
    canvas.Color[0] = m_Pen;
    canvas.Color[1] = m_Brush;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::imgLogicalColorsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (m_CursorLogical != -1)
    {
        if (Button == mbLeft)
        {
            m_Pen = m_CursorLogical;
        }
        else if (Button == mbRight)
        {
            m_Brush = m_CursorLogical;
        }
        Update();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::imgLogicalColorsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    auto llc = m_CursorLogical;
    // change colour selection
    m_CursorLogical = -1;
    // set colour (left)
    auto col = X / c_box;
    auto row = Y / c_box;
    auto cols = imgLogicalColors->Width / c_box;
    auto lc = (row * cols) + col;
    if (0 <= lc && lc <= m_GraphicsMode.LogicalColors)
    {
        m_CursorLogical = lc;
    }
    if (llc != m_CursorLogical)
    {
        DrawLogicalColors();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::imgLogicalColorsMouseLeave(TObject *Sender)
{
    m_CursorLogical = -1;
    DrawLogicalColors();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::imgSystemColorsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    // remap a logical colour to a new physical colour
    if (Button == mbLeft)
    {
        m_GraphicsMode.RemapColor(m_Pen, m_CursorPhysical);
    }
    else if (Button == mbRight)
    {
        m_GraphicsMode.RemapColor(m_Brush, m_CursorPhysical);
    }
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::imgSystemColorsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    auto lpc = m_CursorPhysical;
    // change colour selection
    m_CursorPhysical = -1;
    // set colour (left)
    auto col = X / c_box;
    auto row = Y / c_box;
    auto cols = imgSystemColors->Width / c_box;
    auto pc = (row * cols) + col;
    if (0 <= pc && pc <= m_Palette.Colors)
    {
        m_CursorPhysical = pc;
    }
    if (lpc != m_CursorPhysical)
    {
        DrawPhysicalColors();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::imgSystemColorsMouseLeave(TObject *Sender)
{
    m_CursorPhysical = -1;
    DrawPhysicalColors();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::btnSwapClick(TObject *Sender)
{
    auto op = m_Pen;
    m_Pen = m_Brush;
    m_Brush = op;
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::btnPaletteLoadClick(TObject *Sender)
{
    auto path = Services::File::Combine("Saved Palettes", m_GraphicsMode.Name);
    path = Services::Folders::Create(Services::Folders::lpCommon, path);
    dlgOpen->InitialDir = path;
    if (dlgOpen->Execute())
    {
        m_GraphicsMode.LoadLogicalCLUT(path, Services::File::NameWithExtension(dlgOpen->FileName));
        Update();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::btnPaletteSaveClick(TObject *Sender)
{
    auto path = Services::File::Combine("Saved Palettes", m_GraphicsMode.Name);
    path = Services::Folders::Create(Services::Folders::lpCommon, path);
    dlgSave->InitialDir = path;
    if (dlgSave->Execute())
    {
        m_GraphicsMode.SaveLogicalCLUT(path, Services::File::NameWithoutExtension(dlgSave->FileName));
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::btnPaletteRestoreClick(TObject *Sender)
{
    m_GraphicsMode.RestoreDefaultPalette();
    Update();
}
//---------------------------------------------------------------------------

