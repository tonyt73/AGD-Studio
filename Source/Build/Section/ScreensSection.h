//---------------------------------------------------------------------------
#ifndef ScreensSectionH
#define ScreensSectionH
//---------------------------------------------------------------------------
#include "Section.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class ScreensSection : public Section
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  ScreensSection();
            __fastcall ~ScreensSection() override;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
