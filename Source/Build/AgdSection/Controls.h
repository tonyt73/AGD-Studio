//---------------------------------------------------------------------------
#ifndef ControlsH
#define ControlsH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Controls : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Controls();
    virtual __fastcall ~Controls();
};
}
//---------------------------------------------------------------------------
#endif
