//---------------------------------------------------------------------------
#ifndef ScreensBuilderBuilderH
#define ScreensBuilderBuilderH
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class ScreensBuilder : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  ScreensBuilder();
    virtual __fastcall ~ScreensBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
