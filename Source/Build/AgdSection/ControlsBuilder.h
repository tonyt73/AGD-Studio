//---------------------------------------------------------------------------
#ifndef ControlsBuilderBuilderBuilderH
#define ControlsBuilderBuilderH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class ControlsBuilder : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  ControlsBuilder();
    virtual __fastcall ~ControlsBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
