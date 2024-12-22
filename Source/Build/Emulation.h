//---------------------------------------------------------------------------
#ifndef EmulationH
#define EmulationH
//---------------------------------------------------------------------------
#include "ShellProcess.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class Emulation final : public ShellProcess
{
public:
            __fastcall  Emulation(BuildMessages& buildMessages);
            __fastcall ~Emulation() final;

    bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
