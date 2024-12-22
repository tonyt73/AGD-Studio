//---------------------------------------------------------------------------
#ifndef CompilationH
#define CompilationH
//---------------------------------------------------------------------------
#include "ShellProcess.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class Compilation final : public ShellProcess
{
public:
                    __fastcall  Compilation(BuildMessages& buildMessages);
                    __fastcall ~Compilation() final;

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
