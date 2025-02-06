//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "ShellProcess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall ShellProcess::ShellProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description)
: BuildProcess(buildMessages, type, description)
{
}
//---------------------------------------------------------------------------
__fastcall ShellProcess::~ShellProcess()
{
}
//---------------------------------------------------------------------------
bool __fastcall ShellProcess::ShellExecute(const String& path, const String& cmdline, const String& parameters, bool wait)
{
    auto shell = std::make_unique<TLMDStarterExt>(Application);
    shell->Command = cmdline;
    shell->Parameters = parameters;
    shell->AutoStart = false;
    shell->DefaultDir = path;
    shell->StartOperation = smOpen;
    shell->StartOption = soSW_HIDE;
    shell->ExtStartOptions = TLMDStarterExtendedOptions() << soxUseCreateProcess;
    shell->Wait = wait;
    shell->OnOutput = OnOutputEvent;
    shell->OnFinished = OnFinishedEvent;
    shell->OnError = OnErrorEvent;

    m_Errored = false;

    ChDir(path);
    BUILD_MSG_PUSH(bmShell, "Shell");
    BUILD_LINE(bmShell, cmdline + " " + parameters);
    shell->Execute();
    Sleep(100);

    BUILD_MSG(!m_Errored ? bmOk : bmFailed);
    BUILD_MSG_POP(!m_Errored);

    return !m_Errored;
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnOutputEvent(System::TObject* /*Sender*/, const System::UnicodeString ANewLine)
{
    if (ANewLine.LowerCase().Pos("error")) {
        m_Errored = true;
        BUILD_LINE(bmFailed, "» " + ANewLine);
    } else if (ANewLine.LowerCase().Pos("warn")) {
        BUILD_LINE(bmWarning, "» " + ANewLine);
    } else {
        BUILD_LINE(bmOutput, ANewLine);
    }
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnErrorEvent(System::TObject* ASender)
{
    m_Errored = true;
    auto shell = dynamic_cast<TLMDStarterExt*>(ASender);
    BUILD_LINE(bmFailed, "SHELL ERROR: 0x" + IntToHex(shell->LastError, 8));
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnFinishedEvent(System::TObject* ASender)
{
    BUILD_LINE(bmOk, "Shell finished");
}
//---------------------------------------------------------------------------

