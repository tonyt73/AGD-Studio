//---------------------------------------------------------------------------
#ifndef JumpTableBuilderBuilderH
#define JumpTableBuilderBuilderH
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class JumpTableBuilder : public SectionBuilder
{
private:
    // TODO: put this into an editor
    int                 m_Steps[22];
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  JumpTableBuilder();
    virtual __fastcall ~JumpTableBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
