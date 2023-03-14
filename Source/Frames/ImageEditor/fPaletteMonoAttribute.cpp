//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fPaletteMonoAttribute.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmPaletteMonoAttribute::TfrmPaletteMonoAttribute(TComponent* Owner)
: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPaletteMonoAttribute::Set(Agdx::GraphicsBuffer& canvas)
{
    // change the color set of the canvas
    canvas.Color[0] = 1;
    canvas.Color[1] = 0;
    canvas.Color[2] = 0;
    canvas.Color[3] = 0;
}
//---------------------------------------------------------------------------

