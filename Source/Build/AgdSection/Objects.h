//---------------------------------------------------------------------------
#ifndef ObjectsH
#define ObjectsH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Objects : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Objects();
    virtual __fastcall ~Objects();
};
}
//---------------------------------------------------------------------------
#endif
