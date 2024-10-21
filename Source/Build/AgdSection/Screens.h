//---------------------------------------------------------------------------
#ifndef ScreensH
#define ScreensH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Screens : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Screens();
    virtual __fastcall ~Screens();
};
}
//---------------------------------------------------------------------------
#endif
