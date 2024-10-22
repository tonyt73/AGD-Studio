//---------------------------------------------------------------------------
#ifndef CompilationH
#define CompilationH
//---------------------------------------------------------------------------
#include "ShellProcess.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class Compilation : public ShellProcess
{
public:
                    __fastcall  Compilation(BuildMessages& buildMessages);
    virtual         __fastcall ~Compilation();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
