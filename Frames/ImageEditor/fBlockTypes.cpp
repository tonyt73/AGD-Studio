//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "fBlockTypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfrmBlockTypes *frmBlockTypes;
const unsigned int g_BlockColors[7] = {
    0x00000000, // black    empty
    0x00FF0000, // blue     platform
    0x00006AFF, // orange   wall
    0x0000FF00, // green    ladder
    0x00DC00FF, // magenta  fodder
    0x000000FF, // red      deadly
    0x00FFFFFF, // white    custom
};
//---------------------------------------------------------------------------
__fastcall TfrmBlockTypes::TfrmBlockTypes(TComponent* Owner)
: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmBlockTypes::btnPlatformClick(TObject *Sender)
{
    auto button = dynamic_cast<TSpeedButton*>(Sender);
    if (button)
    {
        panBlock->Caption = button->Caption[1];
        panBlock->Color = (TColor)(g_BlockColors[button->Tag]);
        m_BlockType = button->Tag;
    }
}
//---------------------------------------------------------------------------
