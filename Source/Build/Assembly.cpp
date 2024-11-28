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
    auto path = Services::Folders::Project;
    auto asmFile = Services::Folders::CleanseSeparators(Services::File::Combine(Services::Folders::Project, Services::Folders::ProjectName + ".asm"));
    auto assemblerSrc = Services::Folders::CleanseSeparators(Services::File::Resolve(Services::Folders::Application, mc.Assembler.Path));
    auto result = true;
    BUILD_MSG("Assembling " + asmFile);
    if (Services::File::Exists(assemblerSrc)) {
        auto assemblerDst = Services::Folders::CleanseSeparators(Services::File::Combine(path, Services::File::NameWithExtension(assemblerSrc)));
        auto parameters = Parameter::ization(mc.Assembler.Parameters);
        Services::File::PrependText(asmFile, mc.Assembler.Prepend);
        Services::File::AppendText(asmFile, mc.Assembler.Append);
        BUILD_LINE(bmCopy, "Copying Assembler to project folder");
        Services::File::Copy(assemblerSrc, assemblerDst, true);
        BUILD_LINE(bmBuild, "Execute Assembler");
        ShellExecute(path, Services::File::NameWithExtension(assemblerDst), parameters);
        BUILD_LINE(bmCopy, "Removing Assembler from project folder");
        Services::File::Delete(assemblerDst);
    } else {
        result = false;
        BUILD_LINE(bmBuild, "Assembler executable is missing: " + assemblerSrc);
    }
    return result;
}
//---------------------------------------------------------------------------

