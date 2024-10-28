//---------------------------------------------------------------------------
#ifndef PreChecksH
#define PreChecksH
//---------------------------------------------------------------------------
#include "BuildProcess.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class PreChecks : public BuildProcess
{
private:
public:
                    __fastcall  PreChecks(BuildMessages& buildMessages);
    virtual         __fastcall ~PreChecks();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
