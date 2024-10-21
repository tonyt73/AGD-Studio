//---------------------------------------------------------------------------
#ifndef WindowH
#define WindowH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Window : public SectionBuilder
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
