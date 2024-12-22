//---------------------------------------------------------------------------
#ifndef WindowSectionH
#define WindowSectionH
//---------------------------------------------------------------------------
#include "Section.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class WindowSection : public Section
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  WindowSection();
    virtual __fastcall ~WindowSection() override;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
