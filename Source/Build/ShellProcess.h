//---------------------------------------------------------------------------
#ifndef ShellProcessH
#define ShellProcessH
//---------------------------------------------------------------------------
#include "LMDCustomComponent.hpp"
#include "LMDShBase.hpp"
#include "LMDStarter.hpp"
#include "BuildProcess.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class ShellProcess : public BuildProcess
{
private:
std::unique_ptr<TLMDStarterExt> m_Shell;
            bool                m_ShellDone;
            bool                m_Errored;

			void     __fastcall OnOutputEvent(System::TObject* ASender, const System::UnicodeString ANewLine);
			void     __fastcall OnErrorEvent(System::TObject* ASender);
            void     __fastcall OnTerminatedEvent(System::TObject* ASender);

protected:
            bool                ShellExecute(const String& path, const String& cmdline, const String& parameters, bool wait = true, int timeOut = 0);


public:
                                ShellProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description);
    virtual                    ~ShellProcess();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
