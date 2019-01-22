//---------------------------------------------------------------------------
#ifndef EmulationH
#define EmulationH
//---------------------------------------------------------------------------
#include "Build/BuildProcess.h"
//---------------------------------------------------------------------------
class Emulation : public BuildProcess
{
private:
public:
                    __fastcall  Emulation(BuildMessages& buildMessages);
    virtual         __fastcall ~Emulation();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
