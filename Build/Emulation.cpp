//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/Emulation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Emulation::Emulation(BuildMessages& buildMessages)
: BuildProcess(buildMessages, bmRun, "Run Game")
{

}
//---------------------------------------------------------------------------
__fastcall Emulation::~Emulation()
{

}
//---------------------------------------------------------------------------
bool __fastcall Emulation::Execute()
{
    auto agdFile = System::File::Combine(System::Path::Project, System::Path::ProjectName + ".agd");
    return true;
}
//---------------------------------------------------------------------------

