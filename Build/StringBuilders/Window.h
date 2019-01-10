//---------------------------------------------------------------------------
#ifndef WindowH
#define WindowH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Window : public StringBuilders::StringBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Window();
    virtual __fastcall ~Window();
};
}
//---------------------------------------------------------------------------
#endif
