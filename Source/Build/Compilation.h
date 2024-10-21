//---------------------------------------------------------------------------
#ifndef CompilationH
#define CompilationH
//---------------------------------------------------------------------------
#include "Build/ShellProcess.h"
//---------------------------------------------------------------------------
class Compilation : public ShellProcess
{
public:
                    __fastcall  Compilation(BuildMessages& buildMessages);
    virtual         __fastcall ~Compilation();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
