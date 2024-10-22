//---------------------------------------------------------------------------
#ifndef JumpTableBuilderH
#define JumpTableBuilderH
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
    void     Execute() final;
public:
             JumpTableBuilder();
    virtual ~JumpTableBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
