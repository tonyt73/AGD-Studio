//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "fULAplusBitmap.h"
#include "DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
const auto p_box = 10;  // size of the physical colour picker boxes
//---------------------------------------------------------------------------
__fastcall TfrmULAplusBitmap::TfrmULAplusBitmap(TComponent* Owner)
: TFrame(Owner)
, m_Ink(1)
, m_Paper(0)
, m_Index(0)
, m_Cursor(-1)
, m_CursorIndex(-1)
, m_GraphicsMode(*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()))
, m_Palette(m_GraphicsMode.Palette())
{
    m_PalettePicker = std::make_unique<TBitmap>();
    m_PalettePicker->PixelFormat = pf32bit;
    m_PhysicalPicker = std::make_unique<TBitmap>();
    m_PhysicalPicker->PixelFormat = pf32bit;
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::Init()
{
    Update();
    panSystemColorPicker->Visible = m_GraphicsMode.SupportsLogicalColorRemapping;
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::DrawSelectionBox(int xs, int ys, int xe, int ye) const
{
    m_PalettePicker->Canvas->Brush->Color = clBlack;
    m_PalettePicker->Canvas->FrameRect(TRect(xs, ys, xe, ye));
    m_PalettePicker->Canvas->Brush->Color = clWhite;
    m_PalettePicker->Canvas->FrameRect(TRect(xs + 1, ys + 1, xe - 1, ye - 1));
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::DrawPhysicalColors() const
{
    // setup the colour pickers
    const auto totalColors = m_Palette.Colors;
    // calculate the number of rows
    auto cols = imgSystemColors->Width / p_box;
    auto rows = totalColors / cols;
    // setup the picker image
    if (m_PhysicalPicker->Width == 0)
    {
        // work out the size of the picker control
        auto hh = lblSystemColor->Height + ((rows + 1) * p_box);
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
        auto x = c * p_box;
        auto y = r * p_box;
        m_PhysicalPicker->Canvas->Brush->Color = m_Palette.Color[i];
        m_PhysicalPicker->Canvas->FillRect(TRect(x, y, x + p_box, y + p_box));
        if (i == m_CursorPhysical)
        {
            auto xs = x;
            auto ys = y;
            auto xe = x + p_box;
            auto ye = y + p_box;
            DrawSelectionBox(xs, ys, xe, ye);
        }
    }
    BitBlt(imgSystemColors->Picture->Bitmap->Canvas->Handle, 0, 0, m_PhysicalPicker->Width, m_PhysicalPicker->Height, m_PhysicalPicker->Canvas->Handle, 0, 0, SRCCOPY);
    imgSystemColors->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::DrawPalettesColors() const
{
    // draw the logical colours
    // setup the colour pickers
    const auto totalColors = m_GraphicsMode.LogicalColors;
    // calculate the number of rows
    const auto bx = 20;  // width of the logical colour picker boxes
    const auto by = 20;  // width of the logical colour picker boxes
    // setup the picker image
    if (m_PalettePicker->Width == 0)
    {
        auto hh = 8 + (4 * ((by * 2) + 2));
        panPalettePicker->Height = hh + lblLogicalColor->Height;
        m_PalettePicker->Width = imgLogicalColors->Width;
        m_PalettePicker->Height = hh;
        imgLogicalColors->Picture->Bitmap->Width = m_PalettePicker->Width;
        imgLogicalColors->Picture->Bitmap->Height = m_PalettePicker->Height;
        imgLogicalColors->Picture->Bitmap->PixelFormat = pf32bit;
    }
    // clear the bitmap
    m_PalettePicker->Canvas->Brush->Color = TColor(0x00000000);
    m_PalettePicker->Canvas->FillRect(TRect(0, 0, m_PalettePicker->Width, m_PalettePicker->Height));
    // draw the physical colours
    for (auto pi = 0; pi < 4; pi++)
    {
        for (auto ci = 0; ci < 8; ci++)
        {
            // draw ink
            auto ink = (pi * 16) + ci;
            auto paper = (pi * 16) + 8 + ci;
            auto x = 2 + (ci * bx);
            auto y = 2 + (pi * ((by + 2) * 2));
            auto xs = x;
            auto ys = y;
            auto xe = x + bx;
            auto ye = y + by;
            m_PalettePicker->Canvas->Brush->Color = m_GraphicsMode.LogicalColor[ink];
            m_PalettePicker->Canvas->FillRect(TRect(xs, ys , xe, ye));
            // draw paper
            m_PalettePicker->Canvas->Brush->Color = m_GraphicsMode.LogicalColor[paper];
            m_PalettePicker->Canvas->FillRect(TRect(xs, ys + by, xe, ye + by));
            if (m_Index == pi)
            {
                if (m_Ink == ci)
                {
                    // draw L
                    auto size = imgLogicalColors->Picture->Bitmap->Canvas->TextExtent("L");
                    auto tx = xs + ((bx - size.cx) >> 1);
                    auto ty = ys + ((by - size.cy) >> 1);
                    m_PalettePicker->Canvas->Font->Color = m_Palette.FontColorOf[m_GraphicsMode.FromLogicalColor[ink]];
                    m_PalettePicker->Canvas->Brush->Color = m_GraphicsMode.LogicalColor[ink];
                    m_PalettePicker->Canvas->TextOut(tx, ty, "L");
                }
                if (m_Paper == ci)
                {
                    // draw R
                    auto size = imgLogicalColors->Picture->Bitmap->Canvas->TextExtent("R");
                    auto tx = xs + ((bx - size.cx) >> 1);
                    auto ty = ys + ((by - size.cy) >> 1) + by;
                    m_PalettePicker->Canvas->Font->Color = m_Palette.FontColorOf[m_GraphicsMode.FromLogicalColor[paper]];
                    m_PalettePicker->Canvas->Brush->Color = m_GraphicsMode.LogicalColor[paper];
                    m_PalettePicker->Canvas->TextOut(tx, ty, "R");
                }
            }
            if (pi == m_CursorIndex)
            {
                if (ci == m_Cursor)
                {
                    // draw a double height cursor for selecting ink(L) or paper(R)
                    DrawSelectionBox(xs, ys, xe, ye + by);
                }
            }
        }
    }
    // draw the index cursor
    auto xs = 0;
    auto ys = (m_Index * ((by + 2) * 2));
    auto xe = m_PalettePicker->Width;
    auto ye = ys + (by * 2) + 4;
    DrawSelectionBox(xs, ys, xe, ye);
    BitBlt(imgLogicalColors->Picture->Bitmap->Canvas->Handle, 0, 0, m_PalettePicker->Width, m_PalettePicker->Height, m_PalettePicker->Canvas->Handle, 0, 0, SRCCOPY);
    imgLogicalColors->Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::Update()
{
    DrawPhysicalColors();
    DrawPalettesColors();
    panColorL->Color = m_GraphicsMode.LogicalColor[(m_Index * 16) + m_Ink];
    panColorR->Color = m_GraphicsMode.LogicalColor[(m_Index * 16) + 8 + m_Paper];
    panColorL->Font->Color = m_Palette.FontColorOf[m_GraphicsMode.FromLogicalColor[(m_Index * 16) + m_Ink]];
    panColorR->Font->Color = m_Palette.FontColorOf[m_GraphicsMode.FromLogicalColor[(m_Index * 16) + 8 + m_Paper]];
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::Set(Agdx::GraphicsBuffer& canvas)
{
    canvas.Color[0] = m_Ink;
    canvas.Color[1] = m_Paper;
    canvas.Color[2] = m_Index;
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::imgLogicalColorsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    m_Index = m_CursorIndex;
    if (Button == mbLeft)
    {
        m_Ink = m_Cursor;
    }
    else if (Button == mbRight)
    {
        m_Paper = m_Cursor;
    }
    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::imgLogicalColorsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    const auto bx = 20;  // width of the logical colour picker boxes
    const auto by = 40;  // height of the logical colour picker boxes
    Y -= 2;
    if (Y < 0) return;

    auto lc = m_Cursor;
    auto li = m_CursorIndex;
    // set colour (left)
    m_Cursor = X / bx;
    m_CursorIndex = Y / by;
    if (lc != m_Cursor || li != m_CursorIndex)
    {
        DrawPalettesColors();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::imgLogicalColorsMouseLeave(TObject *Sender)
{
    m_Cursor = -1;
    m_CursorIndex = -1;
    DrawPalettesColors();
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::imgSystemColorsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    // remap a logical colour to a new physical colour
//    if (Button == mbLeft)
//    {
//        m_GraphicsMode.RemapColor(m_Pen, m_CursorPhysical);
//    }
//    else if (Button == mbRight)
//    {
//        m_GraphicsMode.RemapColor(m_Brush, m_CursorPhysical);
//    }
//    Update();
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::imgSystemColorsMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
    auto lpc = m_CursorPhysical;
    // change colour selection
    m_CursorPhysical = -1;
    // set colour (left)
    auto col = X / p_box;
    auto row = Y / p_box;
    auto cols = imgSystemColors->Width / p_box;
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
void __fastcall TfrmULAplusBitmap::imgSystemColorsMouseLeave(TObject *Sender)
{
    m_CursorPhysical = -1;
    DrawPhysicalColors();
}
//---------------------------------------------------------------------------
void __fastcall TfrmULAplusBitmap::btnPaletteRestoreClick(TObject *Sender)
{
    m_GraphicsMode.RestoreDefaultPalette();
    Update();
}
//---------------------------------------------------------------------------

