//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/EmuBuilder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall EmuBuilder::EmuBuilder(BuildMessages& buildMessages)
: Builder(buildMessages)
{

}
//---------------------------------------------------------------------------
__fastcall EmuBuilder::~EmuBuilder()
{

}
//---------------------------------------------------------------------------
bool __fastcall EmuBuilder::Execute()
{
    auto agdFile = System::File::Combine(System::Path::Project, System::Path::ProjectName + ".agd");
    return true;
}
//---------------------------------------------------------------------------

