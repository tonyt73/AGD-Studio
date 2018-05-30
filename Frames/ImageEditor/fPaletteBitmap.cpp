//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "fPaletteBitmap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmPaletteBitmap::TfrmPaletteBitmap(TComponent* Owner)
: TFrame(Owner)
, m_Pen(1)
, m_Brush(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteBitmap::Set(Agdx::GraphicsBuffer& canvas)
{
    canvas.Color[0] = m_Pen;
    canvas.Color[1] = m_Brush;
}
//---------------------------------------------------------------------------
