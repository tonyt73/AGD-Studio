//---------------------------------------------------------------------------
#ifndef ProjectH
#define ProjectH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Project : public StringBuilder
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
