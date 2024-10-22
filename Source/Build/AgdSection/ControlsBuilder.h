//---------------------------------------------------------------------------
#ifndef ControlsBuilderH
#define ControlsBuilderH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class ControlsBuilder : public SectionBuilder
{
protected:
    void     Execute() final;
public:
             ControlsBuilder();
    virtual ~ControlsBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
