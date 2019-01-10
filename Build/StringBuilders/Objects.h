//---------------------------------------------------------------------------
#ifndef ObjectsH
#define ObjectsH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Objects : public StringBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Objects();
    virtual __fastcall ~Objects();
};
}
//---------------------------------------------------------------------------
#endif
