//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/Emulation.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Emulation::Emulation(BuildMessages& buildMessages)
: ShellProcess(buildMessages, bmRun, "Run Game")
{
}
//---------------------------------------------------------------------------
__fastcall Emulation::~Emulation()
{
}
//---------------------------------------------------------------------------
bool __fastcall Emulation::Execute()
{
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    auto gameFile = System::File::Combine(System::Path::Project, System::Path::ProjectName);
    BUILD_MSG("Launching Game " + gameFile);

    auto emulator = System::File::Resolve(System::Path::Application, mc.Emulator.Path);
    auto parameters = Parameter::ization(mc.Emulator.Parameters);

    auto path = System::File::PathOf(emulator);
    auto cmdline = emulator + " " + parameters;
    return ShellExecute(path, cmdline, false);
}
//---------------------------------------------------------------------------

