//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "JumpTableSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/JumpTable.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
__fastcall JumpTableSection::JumpTableSection()
: Section("Jump Table")
{
}
//---------------------------------------------------------------------------
__fastcall JumpTableSection::~JumpTableSection()
{
}
//---------------------------------------------------------------------------
void __fastcall JumpTableSection::Execute()
{
    const auto& JumpTable = (Project::JumpTableDocument*)theDocumentManager.Get("Jump", "Table", "JumpTable");

    String def = "DEFINEJUMP ";
    for (auto i = 0; i < JumpTable->Count; i++) {
        def += IntToStr(JumpTable->RawStep(i));
        def += " ";
    }
    def += "99";

    AddLine(def);
    LineBreak();

    Success();
}
//---------------------------------------------------------------------------
}
