//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Controls.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace StringBuilders;
//---------------------------------------------------------------------------
__fastcall StringBuilders::Controls::Controls()
{
}
//---------------------------------------------------------------------------
__fastcall StringBuilders::Controls::~Controls()
{
}
//---------------------------------------------------------------------------
void __fastcall StringBuilders::Controls::Execute()
{
    AddLine("DEFINECONTROLS  'Q' 'A' 'O' 'P' ' ' 'Z' 'I'");
    LineBreak();
    Success();
}
//---------------------------------------------------------------------------

