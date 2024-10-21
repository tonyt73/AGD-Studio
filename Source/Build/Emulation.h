//---------------------------------------------------------------------------
#ifndef EmulationH
#define EmulationH
//---------------------------------------------------------------------------
#include "Build/ShellProcess.h"
//---------------------------------------------------------------------------
class Emulation : public ShellProcess
{
public:
                    __fastcall  Emulation(BuildMessages& buildMessages);
    virtual         __fastcall ~Emulation();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
