//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "JumpTableBuilder.h"
#include "Project/DocumentManager.h"
#include "Project/JumpTableDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
JumpTableBuilder::JumpTableBuilder()
: SectionBuilder("Jump Table")
{
}
//---------------------------------------------------------------------------
JumpTableBuilder::~JumpTableBuilder()
{
}
//---------------------------------------------------------------------------
void JumpTableBuilder::Execute()
{
    const auto& JumpTableBuilder = (Project::JumpTableDocument*)theDocumentManager.Get("Jump", "Table", "JumpTableBuilder");

    String def = "DEFINEJUMP ";
    for (auto i = 0; i < JumpTableBuilder->Count; i++)
    {
        def += IntToStr(JumpTableBuilder->RawStep(i));
        def += " ";
    }
    def += "99";

    AddLine(def);
    LineBreak();

    Success();
}
//---------------------------------------------------------------------------
}
