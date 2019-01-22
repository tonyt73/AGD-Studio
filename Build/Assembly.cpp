//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/Assembly.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DosCommand"
//---------------------------------------------------------------------------
__fastcall Assembly::Assembly(BuildMessages& buildMessages)
: BuildProcess(buildMessages, bmBuild, "Assemble Game+Engine (Assembly File to Emulator File)")
{
    m_Shell = std::make_unique<TDosCommand>(nullptr);

    m_Shell->OnNewLine = OnNewLineEvent;
    m_Shell->OnExecuteError = OnErrorEvent;
    m_Shell->OnTerminateProcess = OnTerminateProcessEvent;
}
//---------------------------------------------------------------------------
__fastcall Assembly::~Assembly()
{
}
//---------------------------------------------------------------------------
bool __fastcall Assembly::Execute()
{
    auto agdFile = System::File::Combine(System::Path::Project, System::Path::ProjectName + ".agd");
    m_Shell->CurrentDir = System::File::PathOf(agdFile);
    BUILD_MSG("Compiling " + agdFile);

    return true;
}
//---------------------------------------------------------------------------
void __fastcall Assembly::OnNewLineEvent(System::TObject* ASender, const System::UnicodeString ANewLine, TOutputType AOutputType)
{

}
//---------------------------------------------------------------------------
void __fastcall Assembly::OnErrorEvent(System::TObject* ASender, System::Sysutils::Exception* AE, bool &AHandled)
{

}
//---------------------------------------------------------------------------
void __fastcall Assembly::OnTerminateProcessEvent(System::TObject* ASender, bool &ACanTerminate)
{

}
//---------------------------------------------------------------------------

