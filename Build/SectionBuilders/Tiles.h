//---------------------------------------------------------------------------
#ifndef TilesH
#define TilesH
//---------------------------------------------------------------------------
#include "Build/SectionBuilders/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Tiles : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Tiles();
    virtual __fastcall ~Tiles();
};
}
//---------------------------------------------------------------------------
#endif
