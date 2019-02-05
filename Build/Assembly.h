//---------------------------------------------------------------------------
#ifndef AssemblyH
#define AssemblyH
//---------------------------------------------------------------------------
#include "Build/ShellProcess.h"
//---------------------------------------------------------------------------
class Assembly : public ShellProcess
{
public:
                    __fastcall  Assembly(BuildMessages& buildMessages);
    virtual         __fastcall ~Assembly();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
