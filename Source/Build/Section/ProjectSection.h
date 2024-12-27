//---------------------------------------------------------------------------
#ifndef ProjectSectionH
#define ProjectSectionH
//---------------------------------------------------------------------------
#include "Section.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class ProjectSection : public Section
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  ProjectSection();
    virtual __fastcall ~ProjectSection() override;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
