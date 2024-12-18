//---------------------------------------------------------------------------
#ifndef JumpTableSectionH
#define JumpTableSectionH
//---------------------------------------------------------------------------
#include "Section.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class JumpTableSection : public Section
{
private:
    // TODO -cImprovement: Put this into an editor
    // TODO -cConfig Setup: Put this number in the machine config file (could be different for each machine)
    //int                 m_Steps[22];
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  JumpTableSection();
    virtual __fastcall ~JumpTableSection();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
