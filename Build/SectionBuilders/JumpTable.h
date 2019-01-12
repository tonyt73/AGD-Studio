//---------------------------------------------------------------------------
#ifndef JumpTableH
#define JumpTableH
//---------------------------------------------------------------------------
#include "Build/SectionBuilders/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class JumpTable : public SectionBuilder
{
private:
    // TODO: put this into an editor
    int                 m_Steps[22];
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  JumpTable();
    virtual __fastcall ~JumpTable();
};
}
//---------------------------------------------------------------------------
#endif
