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
    auto game = Services::Folders::Project;
    BUILD_MSG("Launching Game " + game);

    auto emulator = Services::File::Resolve(Services::Folders::Application, mc.Emulator.Path);
    auto parameters = Services::Folders::CleanseSeparators(Parameter::ization(mc.Emulator.Parameters));

    if (Services::File::Exists(parameters)) {
        auto path = Services::Folders::CleanseSeparators(Services::File::PathOf(emulator));
        auto exe = Services::File::NameWithExtension(emulator);
        return ShellExecute(path, exe, parameters, false);
    }
    BUILD_LINE(bmFailed, "Failed to find the emulator file to run: " + parameters);
    return false;
}
//---------------------------------------------------------------------------

