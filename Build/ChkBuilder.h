//---------------------------------------------------------------------------
#ifndef ChkBuilderH
#define ChkBuilderH
//---------------------------------------------------------------------------
#include "Build/Builder.h"
//---------------------------------------------------------------------------
class ChkBuilder : public Builder
{
private:
public:
                    __fastcall  ChkBuilder(BuildMessages& buildMessages);
    virtual         __fastcall ~ChkBuilder();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
