//---------------------------------------------------------------------------
#ifndef AssemblyH
#define AssemblyH
//---------------------------------------------------------------------------
#include "DosCommand.hpp"
#include "Build/ShellProcess.h"
//---------------------------------------------------------------------------
class Assembly : public ShellProcess
{
private:

public:
                    __fastcall  Assembly(BuildMessages& buildMessages);
    virtual         __fastcall ~Assembly();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
