//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "JumpTable.h"
#include "Project/DocumentManager.h"
#include "Project/JumpTableDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::JumpTable::JumpTable()
: SectionBuilder("Jump Table")
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::JumpTable::~JumpTable()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::JumpTable::Execute()
{
    const auto& JumpTable = (JumpTableDocument*)theDocumentManager.Get("Jump", "Table", "JumpTable");

    String def = "DEFINEJUMP ";
    for (auto i = 0; i < JumpTable->Count; i++)
    {
        def += IntToStr(JumpTable->RawStep(i));
        def += " ";
    }
    def += "99";

    AddLine(def);
    LineBreak();

    Success();
}
//---------------------------------------------------------------------------

