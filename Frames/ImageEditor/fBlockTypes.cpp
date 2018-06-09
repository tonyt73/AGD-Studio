//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "fBlockTypes.h"
#include "BlockColors.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmBlockTypes::TfrmBlockTypes(TComponent* Owner)
: TFrame(Owner)
, m_BlockType(1)
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
