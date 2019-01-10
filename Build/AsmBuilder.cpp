//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/AsmBuilder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall AsmBuilder::AsmBuilder(BuildMessages& buildMessages)
: Builder(buildMessages)
{

}
//---------------------------------------------------------------------------
__fastcall AsmBuilder::~AsmBuilder()
{

}
//---------------------------------------------------------------------------
bool __fastcall AsmBuilder::Execute()
{
    auto agdFile = System::File::Combine(System::Path::Project, System::Path::ProjectName + ".agd");
    return true;
}
//---------------------------------------------------------------------------

