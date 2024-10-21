//---------------------------------------------------------------------------
#ifndef PreChecksH
#define PreChecksH
//---------------------------------------------------------------------------
#include "Build/BuildProcess.h"
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
#endif
