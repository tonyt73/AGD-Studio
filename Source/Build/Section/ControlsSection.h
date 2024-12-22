//---------------------------------------------------------------------------
#ifndef ControlsSectionH
#define ControlsSectionH
//---------------------------------------------------------------------------
#include "Section.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class ControlsSection : public Section
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  ControlsSection();
    virtual __fastcall ~ControlsSection() override;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
