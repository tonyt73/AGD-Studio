//---------------------------------------------------------------------------
#ifndef EventsH
#define EventsH
//---------------------------------------------------------------------------
#include "Build/SectionBuilders/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Events : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Events();
    virtual __fastcall ~Events();
};
}
//---------------------------------------------------------------------------
#endif
