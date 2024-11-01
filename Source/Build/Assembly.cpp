//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Assembly.h"
#include "Project/Documents/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall Assembly::Assembly(BuildMessages& buildMessages)
: ShellProcess(buildMessages, bmBuild, "Assemble Game+Engine (Assembly File to Emulator File)")
{
}
//---------------------------------------------------------------------------
__fastcall Assembly::~Assembly()
{
}
//---------------------------------------------------------------------------
bool __fastcall Assembly::Execute()
{
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    auto asmFile = Services::File::Combine(Services::Folders::Project, Services::Folders::ProjectName + ".asm");
    BUILD_MSG("Assembling " + asmFile);

    auto assembler = Services::File::Resolve(Services::Folders::Application, mc.Assembler.Path);
    auto parameters = Parameter::ization(mc.Assembler.Parameters);
    Services::File::PrependText(asmFile, mc.Assembler.Prepend);
    Services::File::AppendText(asmFile, mc.Assembler.Append);

    BUILD_LINE(bmBuild, "Execute Assembler");
    return ShellExecute(Services::File::PathOf(asmFile), assembler, parameters);
}
//---------------------------------------------------------------------------

