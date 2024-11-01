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
    // TODO: put this into an editor
    int                 m_Steps[22];
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
