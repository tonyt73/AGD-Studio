//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Assemble.h"
#include "Project/Documents/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall Assemble::Assemble(BuildMessages& buildMessages)
: ShellProcess(buildMessages, bmAssemble, "Assemble Game+Engine (Assembly File to Emulator File)")
{
}
//---------------------------------------------------------------------------
__fastcall Assemble::~Assemble()
{
}
//---------------------------------------------------------------------------
int __fastcall Assemble::Execute()
{
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    auto path = Services::Folders::Project;
    auto asmFile = Services::Folders::CleanseSeparators(Services::File::Combine(Services::Folders::Project, Services::Folders::ProjectName + ".asm"));
    auto assemblerSrc = Services::Folders::CleanseSeparators(Services::File::Resolve(Services::Folders::Application, mc.Assembler.Path));
    Services::File::Delete(Services::Folders::ProjectName + ".tap");
    auto result = brOk;
    BUILD_MSG("Assembling " + asmFile);
    if (Services::File::Exists(assemblerSrc)) {
        auto assemblerDst = Services::Folders::CleanseSeparators(Services::File::Combine(path, Services::File::NameWithExtension(assemblerSrc)));
        auto parameters = Parameter::ization(mc.Assembler.Parameters);
        Services::File::PrependText(asmFile, mc.Assembler.Prepend);
        Services::File::AppendText(asmFile, mc.Assembler.Append);
        BUILD_LINE(bmCopy, "Copying Assembler to project folder");
        Services::File::Copy(assemblerSrc, assemblerDst, true);
        BUILD_LINE(bmAssemble, "Execute Assembler");
        ShellExecute(path, Services::File::NameWithExtension(assemblerDst), parameters);
        BUILD_LINE(bmCopy, "Removing Assembler from project folder");
        Services::File::Delete(assemblerDst);
    } else {
        result = brError;
        BUILD_LINE(bmAssemble, "Assembler executable is missing: " + assemblerSrc);
    }
    return result;
}
//---------------------------------------------------------------------------

