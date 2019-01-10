//---------------------------------------------------------------------------
#ifndef AsmBuilderH
#define AsmBuilderH
//---------------------------------------------------------------------------
#include "Build/Builder.h"
//---------------------------------------------------------------------------
class AsmBuilder : public Builder
{
private:
public:
                    __fastcall  AsmBuilder(BuildMessages& buildMessages);
    virtual         __fastcall ~AsmBuilder();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
