//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/Compilation.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
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
    auto agdFile = System::File::Combine(System::Path::Project, System::Path::ProjectName + ".agd");
    auto path = System::File::PathOf(agdFile);
    BUILD_MSG("Compiling " + agdFile);
    auto compilerSrc = System::File::Resolve(System::Path::Application, mc.Compiler.Path);
    auto engineSrc = System::File::Resolve(System::Path::Application, mc.Engine.Path);
    auto compilerDst = System::File::Combine(path, System::File::NameWithExtension(compilerSrc));
    auto engineDst = System::File::Combine(path, System::File::NameWithExtension(engineSrc));
    BUILD_LINE(bmInfo, "Using AGD Compiler: " + compilerSrc);
    BUILD_LINE(bmInfo, "Using AGD Engine  : " + engineSrc);
    BUILD_LINE(bmCopy, "Copying AGD Compiler to project folder");
    System::File::Copy(compilerSrc, compilerDst, true);
    BUILD_LINE(bmCopy, "Copying AGD Engine file to project folder");
    System::File::Copy(engineSrc, engineDst, true);
    BUILD_LINE(bmBuild, "Execute AGD Compiler");
    auto parameters = Parameter::ization(mc.Compiler.Parameters);
    auto cmdLine = System::File::NameWithExtension(compilerDst) + " " + parameters;
    auto result = ShellExecute(path, cmdLine, true, 20);
    BUILD_LINE(bmCopy, "Removing compiler from project folder");
    System::File::Delete(compilerDst);
    BUILD_LINE(bmCopy, "Removing AGD Engine file from project folder");
    System::File::Delete(engineDst);

    return result;
}
//---------------------------------------------------------------------------

