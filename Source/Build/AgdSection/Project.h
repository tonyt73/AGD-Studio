//---------------------------------------------------------------------------
#ifndef ProjectH
#define ProjectH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Project : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Project();
    virtual __fastcall ~Project();
};
}
//---------------------------------------------------------------------------
#endif
