//---------------------------------------------------------------------------
#ifndef JumpTableH
#define JumpTableH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class JumpTable : public StringBuilder
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
