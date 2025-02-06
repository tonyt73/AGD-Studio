//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Compilation.h"
#include "Project/Documents/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall Compilation::Compilation(BuildMessages& buildMessages)
: ShellProcess(buildMessages, bmCompile, "Compile Game File (AGD File to Assembly File)")
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
    auto compilerSrc = Services::Folders::CleanseSeparators(Services::File::Resolve(Services::Folders::Application, mc.Compiler.Path));
    auto engineSrc = Services::Folders::CleanseSeparators(Services::File::Resolve(Services::Folders::Application, mc.Engine.Path));
    Services::File::Delete(Services::Folders::ProjectName + ".asm");
    if (Services::File::Exists(compilerSrc)) {
        if (Services::File::Exists(engineSrc)) {
            auto compilerDst = Services::Folders::CleanseSeparators(Services::File::Combine(path, Services::File::NameWithExtension(compilerSrc)));
            auto engineDst = Services::Folders::CleanseSeparators(Services::File::Combine(path, Services::File::NameWithExtension(engineSrc)));
            BUILD_LINE(bmInfo, "Using AGD Compiler: " + compilerSrc);
            BUILD_LINE(bmInfo, "Using AGD Engine  : " + engineSrc);
            BUILD_LINE(bmCopy, "Copying AGD Compiler to project folder");
            Services::File::Copy(compilerSrc, compilerDst, true);
            BUILD_LINE(bmCopy, "Copying AGD Engine file to project folder");
            Services::File::Copy(engineSrc, engineDst, true);
            auto parameters = Parameter::ization(mc.Compiler.Parameters);
            auto cmdLine = Services::File::NameWithExtension(compilerDst);
            BUILD_LINE(bmCompile, "Execute AGD Compiler");
            auto result = ShellExecute(path, cmdLine, parameters);
            BUILD_LINE(bmCopy, "Removing compiler from project folder");
            Services::File::Delete(compilerDst);
            BUILD_LINE(bmCopy, "Removing AGD Engine file from project folder");
            Services::File::Delete(engineDst);
            if (result && Services::File::Exists(Services::Folders::ProjectName + ".asm")) {
                BUILD_LINE(bmChecking, "Assembling file found");
                theDocumentManager.Add("Text", "Assembly", Services::Folders::ProjectName + ".asm");
                return true;
            } else {
                BUILD_LINE(bmFailed, "AGD Compiler failed to create the .asm file. ");
            }
        } else {
            BUILD_LINE(bmFailed, "AGD Engine source file was not found. " + engineSrc);
        }
    } else {
        BUILD_LINE(bmFailed, "AGD Compiler executable was not found. " + compilerSrc);
    }
    return false;
}
//---------------------------------------------------------------------------

