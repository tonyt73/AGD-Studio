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
int __fastcall ShellProcess::ShellExecute(const String& path, const String& cmdline, const String& parameters, bool wait)
{
    auto shell = std::make_unique<TLMDStarterExt>(Application);
    shell->Command = cmdline;
    shell->Parameters = parameters;
    shell->AutoStart = false;
    shell->DefaultDir = path;
    shell->StartOperation = smOpen;
    shell->StartOption = soSW_HIDE;
    shell->ExtStartOptions = TLMDStarterExtendedOptions() << soxUseCreateProcess << soxRedirectOutput << soxRedirectError << soxRedirectInput;
    shell->Wait = wait;
    shell->OnOutput = OnOutputEvent;
    shell->OnFinished = OnFinishedEvent;
    shell->OnError = OnErrorEvent;

    m_BuildResult = brOk;

    ChDir(path);
    BUILD_MSG_PUSH(bmShell, "Shell");
    BUILD_LINE(bmShell, cmdline + " " + parameters);
    shell->Execute();
    Sleep(100);

    BUILD_MSG(m_BuildResult);
    BUILD_MSG_POP(m_BuildResult != brOk);

    return m_BuildResult;
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnOutputEvent(System::TObject* /*Sender*/, const System::UnicodeString ANewLine)
{
    auto lines = SplitString(ANewLine, "\n");
    for (auto line : lines) {
        if (line.LowerCase().Pos("error")) {
            m_BuildResult = m_BuildResult | brError;
            BUILD_LINE(bmFailed, line);
        } else if (line.LowerCase().Pos("warn") || line.LowerCase().Pos(" on line ")) {
            m_BuildResult |= brWarning;
            BUILD_LINE(bmWarning, line);
        } else {
            BUILD_LINE(bmOutput, line);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnErrorEvent(System::TObject* ASender)
{
    m_BuildResult |= brError;
    auto shell = dynamic_cast<TLMDStarterExt*>(ASender);
    BUILD_LINE(bmFailed, "SHELL ERROR: 0x" + IntToHex(shell->LastError, 8));
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnFinishedEvent(System::TObject* ASender)
{
    BUILD_LINE(bmOk, "Shell finished");
}
//---------------------------------------------------------------------------

