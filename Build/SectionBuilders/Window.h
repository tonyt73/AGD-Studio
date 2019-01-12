//---------------------------------------------------------------------------
#ifndef WindowH
#define WindowH
//---------------------------------------------------------------------------
#include "Build/SectionBuilders/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Window : public SectionBuilders::SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Window();
    virtual __fastcall ~Window();
};
}
//---------------------------------------------------------------------------
#endif
