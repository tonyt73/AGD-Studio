//---------------------------------------------------------------------------
#ifndef ProjectBuilderH
#define ProjectBuilderH
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class ProjectBuilder : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  ProjectBuilder();
    virtual __fastcall ~ProjectBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
