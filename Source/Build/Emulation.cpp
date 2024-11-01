//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Emulation.h"
#include "Project/Documents/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
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
    auto gameFile = Services::File::Combine(Services::Folders::Project, Services::Folders::ProjectName);
    BUILD_MSG("Launching Game " + gameFile);

    auto emulator = Services::File::Resolve(Services::Folders::Application, mc.Emulator.Path);
    auto parameters = Parameter::ization(mc.Emulator.Parameters);

    auto path = Services::Folders::CleanseSeparators(Services::File::PathOf(emulator));
    auto exe = Services::File::NameWithExtension(emulator);
    return ShellExecute(path, exe, parameters, false);
}
//---------------------------------------------------------------------------

