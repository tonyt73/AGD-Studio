//---------------------------------------------------------------------------
#ifndef TilesBuilderH
#define TilesBuilderH
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class TilesBuilder : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  TilesBuilder();
    virtual __fastcall ~TilesBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
