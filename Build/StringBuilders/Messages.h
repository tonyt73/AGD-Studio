//---------------------------------------------------------------------------
#ifndef MessagesH
#define MessagesH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Messages : public StringBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Messages();
    virtual __fastcall ~Messages();
};
}
//---------------------------------------------------------------------------
#endif
