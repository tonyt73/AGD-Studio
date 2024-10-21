//---------------------------------------------------------------------------
#ifndef SpritesBuilderBuilderH
#define SpritesBuilderBuilderH
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class SpritesBuilder : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  SpritesBuilder();
    virtual __fastcall ~SpritesBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
