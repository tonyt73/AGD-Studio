//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "ShellProcess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
ShellProcess::ShellProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description)
: BuildProcess(buildMessages, type, description)
{
	m_Shell = std::make_unique<TLMDStarterExt>(nullptr);
	m_Shell->AutoStart = false;
	m_Shell->StartOperation = smOpen;
	m_Shell->StartOption = soSW_HIDE;
	m_Shell->ExtStartOptions = TLMDStarterExtendedOptions() << soxUseCreateProcess << soxRedirectOutput;
	m_Shell->Wait = true;
	m_Shell->OnOutput = OnOutputEvent;
	m_Shell->OnError = OnErrorEvent;
    m_Shell->OnFinished = OnTerminatedEvent;
}
//---------------------------------------------------------------------------
ShellProcess::~ShellProcess()
{
    m_Shell->TerminateProcess();
}
//---------------------------------------------------------------------------
bool ShellProcess::ShellExecute(const String& path, const String& cmdline, const String& parameters, bool wait, int timeOut)
{
    m_Errored = false;
    bool result = true;
    try
    {
        try
        {
			if (!m_ShellDone)
			{
				m_Shell->TerminateProcess();
            }
            ChDir(path);
			m_Shell->DefaultDir = path;
            BUILD_LINE(bmRun, cmdline + " " + parameters);
			m_Shell->Command = cmdline;
			m_Shell->Parameters = parameters;
			//m_Shell->MaxTimeAfterBeginning = timeOut;
			m_Shell->Execute();
            m_ShellDone = false;
            while (wait && !m_ShellDone)
            {
                Application->ProcessMessages();
                Sleep(100);
            }
        }
        catch(Exception&)
        {
            result = false;
        }
    }
    __finally
    {
        if (wait)
        {
			m_Shell->TerminateProcess();
            m_ShellDone = true;
        }
    }
    result = result && !m_Errored;
    BUILD_MSG(result ? bmOk : bmFailed);
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
	m_Shell->TerminateProcess();
	m_ShellDone = true;
	m_Errored = true;
	BUILD_LINE(bmFailed, "SHELL ERROR");// + m_Shell->LastError);
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnTerminatedEvent(System::TObject* ASender)
{
    m_ShellDone = true;
}
//---------------------------------------------------------------------------

