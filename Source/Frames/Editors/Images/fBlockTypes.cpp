//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "fBlockTypes.h"
#include "Visuals/BlockTypes.h"
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
        panBlock->Color = g_BlockColors[button->Tag];
        m_BlockType = '0' + button->Tag;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBlockTypes::SetBlockType(char type)
{
    btnPlatform->Down = type == '1';
    btnWall->Down     = type == '2';
    btnLadder->Down   = type == '3';
    btnFodder->Down   = type == '4';
    btnDeadly->Down   = type == '5';
    btnCustom->Down   = type == '6';
}
//---------------------------------------------------------------------------

