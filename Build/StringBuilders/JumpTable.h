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
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  JumpTable();
    virtual __fastcall ~JumpTable();
};
}
//---------------------------------------------------------------------------
#endif
