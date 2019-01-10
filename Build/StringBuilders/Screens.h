//---------------------------------------------------------------------------
#ifndef ScreensH
#define ScreensH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Screens : public StringBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Screens();
    virtual __fastcall ~Screens();
};
}
//---------------------------------------------------------------------------
#endif
