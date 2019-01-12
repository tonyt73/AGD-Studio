//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Controls.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace SectionBuilders;
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Controls::Controls()
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Controls::~Controls()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Controls::Execute()
{
    AddLine("DEFINECONTROLS  'Q' 'A' 'O' 'P' ' ' 'Z' 'I'");
    LineBreak();
    Success();
}
//---------------------------------------------------------------------------

