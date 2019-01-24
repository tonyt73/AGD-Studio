//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include <System.SysUtils.hpp>
#include "Build/Assembly.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
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
    auto asmFile = System::File::Combine(System::Path::Project, System::Path::ProjectName + ".asm");
    BUILD_MSG("Assembling " + asmFile);

    auto assembler = System::File::Resolve(System::Path::Application, mc.Assembler.Path);
    auto parameters = Parameter::ization(mc.Assembler.Parameters);
    System::File::PrependText(asmFile, mc.Assembler.Prepend);
    System::File::AppendText(asmFile, mc.Assembler.Append);

    BUILD_LINE(bmBuild, "Execute Assembler");
    auto cmdline = assembler + " " + parameters;
    return ShellExecute(System::File::PathOf(asmFile), cmdline);
}
//---------------------------------------------------------------------------

