//---------------------------------------------------------------------------
#ifndef MapBuilderBuilderH
#define MapBuilderBuilderH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class MapBuilder : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  MapBuilder();
    virtual __fastcall ~MapBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif

