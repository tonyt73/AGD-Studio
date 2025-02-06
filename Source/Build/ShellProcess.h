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
            bool                m_Errored;

            void    __fastcall  OnOutputEvent(System::TObject* ASender, const System::UnicodeString ANewLine);
            void    __fastcall  OnErrorEvent(System::TObject* ASender);
            void    __fastcall  OnFinishedEvent(System::TObject* ASender);

protected:
            bool    __fastcall  ShellExecute(const String& path, const String& cmdline, const String& parameters, bool wait = true);

public:
                    __fastcall  ShellProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description);
    virtual         __fastcall ~ShellProcess() override;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
