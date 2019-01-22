//---------------------------------------------------------------------------
#ifndef CompilationH
#define CompilationH
//---------------------------------------------------------------------------
#include "DosCommand.hpp"
#include "Build/BuildProcess.h"
//---------------------------------------------------------------------------
class Compilation : public BuildProcess
{
private:
   std::unique_ptr<TDosCommand> m_Shell;
            bool                m_ShellDone;

            void    __fastcall  OnNewLineEvent(System::TObject* ASender, const System::UnicodeString ANewLine, TOutputType AOutputType);
            void    __fastcall  OnErrorEvent(System::TObject* ASender, System::Sysutils::Exception* AE, bool &AHandled);
            void    __fastcall  OnTerminatedEvent(System::TObject* ASender);

public:
                    __fastcall  Compilation(BuildMessages& buildMessages);
    virtual         __fastcall ~Compilation();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
