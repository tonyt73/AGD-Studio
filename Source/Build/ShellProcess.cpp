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
    auto shell = std::make_unique<TLMDStarterExt>(nullptr);
    shell->Command = cmdline;
    shell->Parameters = parameters;
    shell->AutoStart = false;
    shell->DefaultDir = path;
    shell->StartOperation = smOpen;
    shell->StartOption = soSW_HIDE;
    shell->Wait = wait;
    shell->ExtStartOptions = TLMDStarterExtendedOptions() << soxRedirectOutput;
    shell->OnOutput = OnOutputEvent;
    shell->OnError = OnErrorEvent;

    m_Errored = false;
    bool result = true;

    ChDir(path);
    BUILD_MSG_PUSH(bmRun, "Shell");
    BUILD_LINE(bmRun, cmdline + " " + parameters);
    shell->Execute();
    // need a small delay to help the process starter
    Sleep(100);

    result = result && !m_Errored;
    BUILD_MSG(result ? bmOk : bmFailed);
    BUILD_MSG_POP(true);
    return result;
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnOutputEvent(System::TObject* ASender, const System::UnicodeString ANewLine)
{
    if (ANewLine.LowerCase().Pos("error"))
    {
        m_Errored = true;
        BUILD_LINE(bmFailed, "» " + ANewLine);
    }
    else if (ANewLine.LowerCase().Pos("warn"))
    {
        BUILD_LINE(bmWarning, "» " + ANewLine);
    }
    else
    {
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

