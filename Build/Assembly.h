//---------------------------------------------------------------------------
#ifndef AssemblyH
#define AssemblyH
//---------------------------------------------------------------------------
#include "DosCommand.hpp"
#include "Build/BuildProcess.h"
//---------------------------------------------------------------------------
class Assembly : public BuildProcess
{
private:
   std::unique_ptr<TDosCommand> m_Shell;

            void    __fastcall  OnNewLineEvent(System::TObject* ASender, const System::UnicodeString ANewLine, TOutputType AOutputType);
            void    __fastcall  OnErrorEvent(System::TObject* ASender, System::Sysutils::Exception* AE, bool &AHandled);
            void    __fastcall  OnTerminateProcessEvent(System::TObject* ASender, bool &ACanTerminate);

public:
                    __fastcall  Assembly(BuildMessages& buildMessages);
    virtual         __fastcall ~Assembly();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
