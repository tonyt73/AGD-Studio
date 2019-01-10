//---------------------------------------------------------------------------
#ifndef EventsH
#define EventsH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Events : public StringBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Events();
    virtual __fastcall ~Events();
};
}
//---------------------------------------------------------------------------
#endif
