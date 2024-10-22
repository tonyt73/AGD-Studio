//---------------------------------------------------------------------------
#ifndef AssemblyH
#define AssemblyH
//---------------------------------------------------------------------------
#include "Build/ShellProcess.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class Assembly : public ShellProcess
{
public:
                    __fastcall  Assembly(BuildMessages& buildMessages);
    virtual         __fastcall ~Assembly();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
