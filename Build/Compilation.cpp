//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/Compilation.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DosCommand"
//---------------------------------------------------------------------------
__fastcall Compilation::Compilation(BuildMessages& buildMessages)
: BuildProcess(buildMessages, bmBuild, "Compile Game File (AGD File to Assembly File)")
{
    m_Shell = std::make_unique<TDosCommand>(nullptr);

    m_Shell->OnNewLine = OnNewLineEvent;
    m_Shell->OnExecuteError = OnErrorEvent;
    m_Shell->OnTerminated = OnTerminatedEvent;
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
    m_Shell->CurrentDir = path;
    ChDir(path);
    BUILD_MSG("Compiling " + agdFile);
    try
    {
        auto compilerSrc = System::File::Exists(mc.Compiler.Path) ? mc.Compiler.Path : System::File::Combine(System::Path::Application, mc.Compiler.Path);
        auto engineSrc = System::File::Exists(mc.Engine.Path) ? mc.Engine.Path : System::File::Combine(System::Path::Application, mc.Engine.Path);
        auto compilerDst = System::File::Combine(path, System::File::NameWithExtension(compilerSrc));
        auto engineDst = System::File::Combine(path, System::File::NameWithExtension(engineSrc));
        BUILD_LINE(bmCopy, "Copying AGD Compiler to project folder");
        System::File::Copy(compilerSrc, compilerDst, true);
        BUILD_LINE(bmCopy, "Copying AGD Engine file to project folder");
        System::File::Copy(engineSrc, engineDst, true);
        BUILD_LINE(bmBuild, "Execute AGD Compiler");
        auto file = System::File::NameWithoutExtension(agdFile);
        auto cmdLine = System::File::NameWithExtension(compilerDst) + " " + file;
        BUILD_LINE(bmOutput, "» " + cmdLine);
        m_Shell->CommandLine = cmdLine;
        m_Shell->Execute();
        m_ShellDone = false;
        while (!m_ShellDone)
        {
            Application->ProcessMessages();
            Sleep(100);
        }
        BUILD_LINE(bmCopy, "Removing compiler from project folder");
        System::File::Delete(compilerDst);
        BUILD_LINE(bmCopy, "Removing AGD Engine file from project folder");
        System::File::Delete(engineDst);
        BUILD_MSG(bmOk);
    }
    catch(...)
    {
        BUILD_MSG(bmFailed);
        return false;
    }

    return true;
}
//---------------------------------------------------------------------------
void __fastcall Compilation::OnNewLineEvent(System::TObject* ASender, const System::UnicodeString ANewLine, TOutputType AOutputType)
{
    BUILD_LINE(bmOutput, "» " + ANewLine);
}
//---------------------------------------------------------------------------
void __fastcall Compilation::OnErrorEvent(System::TObject* ASender, System::Sysutils::Exception* AE, bool &AHandled)
{
    BUILD_LINE(bmFailed, "exception: " + AE->ToString());
    AHandled = true;
}
//---------------------------------------------------------------------------
void __fastcall Compilation::OnTerminatedEvent(System::TObject* ASender)
{
    m_ShellDone = true;
}
//---------------------------------------------------------------------------

