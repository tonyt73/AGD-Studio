//---------------------------------------------------------------------------
#ifndef EmulationH
#define EmulationH
//---------------------------------------------------------------------------
#include "ShellProcess.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class Emulation : public ShellProcess
{
public:
                    __fastcall  Emulation(BuildMessages& buildMessages);
    virtual         __fastcall ~Emulation();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
