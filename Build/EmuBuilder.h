//---------------------------------------------------------------------------
#ifndef EmuBuilderH
#define EmuBuilderH
//---------------------------------------------------------------------------
#include "Build/Builder.h"
//---------------------------------------------------------------------------
class EmuBuilder : public Builder
{
private:
public:
                    __fastcall  EmuBuilder(BuildMessages& buildMessages);
    virtual         __fastcall ~EmuBuilder();

            bool    __fastcall  Execute() final;
};
//---------------------------------------------------------------------------
#endif
