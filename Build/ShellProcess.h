//---------------------------------------------------------------------------
#ifndef ShellProcessH
#define ShellProcessH
//---------------------------------------------------------------------------
#include "DosCommand.hpp"
#include "Build/BuildProcess.h"
//---------------------------------------------------------------------------
class ShellProcess : public BuildProcess
{
private:
   std::unique_ptr<TDosCommand> m_Shell;
            bool                m_ShellDone;
            bool                m_Errored;

            void    __fastcall  OnNewLineEvent(System::TObject* ASender, const System::UnicodeString ANewLine, TOutputType AOutputType);
            void    __fastcall  OnErrorEvent(System::TObject* ASender, System::Sysutils::Exception* AE, bool &AHandled);
            void    __fastcall  OnTerminatedEvent(System::TObject* ASender);

protected:
            bool    __fastcall  ShellExecute(const String& path, const String& cmdline, bool wait = true);


public:
                    __fastcall  ShellProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description);
    virtual         __fastcall ~ShellProcess();
};
//---------------------------------------------------------------------------
#endif
