//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/ChkBuilder.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ChkBuilder::ChkBuilder(BuildMessages& buildMessages)
: Builder(buildMessages, bmChecking, "Checking Project Dependencies")
{
}
//---------------------------------------------------------------------------
__fastcall ChkBuilder::~ChkBuilder()
{
}
//---------------------------------------------------------------------------
bool __fastcall ChkBuilder::Execute()
{
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    auto cp = System::File::Exists(mc.Compiler.Path) || System::File::Exists(System::File::Combine(System::Path::Application, mc.Compiler.Path));
    auto ep = System::File::Exists(mc.Engine.Path) || System::File::Exists(System::File::Combine(System::Path::Application, mc.Engine.Path));
    auto ap = System::File::Exists(mc.Assembler.Path) || System::File::Exists(System::File::Combine(System::Path::Application, mc.Assembler.Path));
    auto mp = System::File::Exists(mc.Emulator.Path) || System::File::Exists(System::File::Combine(System::Path::Application, mc.Emulator.Path));
    BUILD_LINE(cp ? bmOk : bmFailed, "Checking for AGD Compiler: " + mc.Compiler.Path);
    BUILD_LINE(ep ? bmOk : bmFailed, "Checking for AGD Engine: " + mc.Engine.Path);
    BUILD_LINE(ap ? bmOk : bmFailed, "Checking for Assembler: " + mc.Assembler.Path);
    BUILD_LINE(mp ? bmOk : bmFailed, "Checking for Emulator: " + mc.Emulator.Path);
    return cp && ap && ep;
}
//---------------------------------------------------------------------------
