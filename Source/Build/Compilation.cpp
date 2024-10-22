//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Compilation.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall Compilation::Compilation(BuildMessages& buildMessages)
: ShellProcess(buildMessages, bmBuild, "Compile Game File (AGD File to Assembly File)")
{
}
//---------------------------------------------------------------------------
__fastcall Compilation::~Compilation()
{
}
//---------------------------------------------------------------------------
bool __fastcall Compilation::Execute()
{
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    auto agdFile = Services::File::Combine(Services::Folders::Project, Services::Folders::ProjectName + ".agd");
    auto path = Services::File::PathOf(agdFile);
    BUILD_MSG("Compiling " + agdFile);
    auto compilerSrc = Services::File::Resolve(Services::Folders::Application, mc.Compiler.Path);
    auto engineSrc = Services::File::Resolve(Services::Folders::Application, mc.Engine.Path);
    auto compilerDst = Services::File::Combine(path, Services::File::NameWithExtension(compilerSrc));
    auto engineDst = Services::File::Combine(path, Services::File::NameWithExtension(engineSrc));
    BUILD_LINE(bmInfo, "Using AGD Compiler: " + compilerSrc);
    BUILD_LINE(bmInfo, "Using AGD Engine  : " + engineSrc);
    BUILD_LINE(bmCopy, "Copying AGD Compiler to project folder");
    Services::File::Copy(compilerSrc, compilerDst, true);
    BUILD_LINE(bmCopy, "Copying AGD Engine file to project folder");
    Services::File::Copy(engineSrc, engineDst, true);
    BUILD_LINE(bmBuild, "Execute AGD Compiler");
    auto parameters = Parameter::ization(mc.Compiler.Parameters);
    auto cmdLine = Services::File::NameWithExtension(compilerDst);
	auto result = ShellExecute(path, cmdLine, parameters, true, 20);
    BUILD_LINE(bmCopy, "Removing compiler from project folder");
    Services::File::Delete(compilerDst);
    BUILD_LINE(bmCopy, "Removing AGD Engine file from project folder");
    Services::File::Delete(engineDst);
    theDocumentManager.Add("Text", "Assembly", Services::Folders::ProjectName + ".asm");
    return result;
}
//---------------------------------------------------------------------------

