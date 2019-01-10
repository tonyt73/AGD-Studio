//---------------------------------------------------------------------------
#ifndef ControlsH
#define ControlsH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Controls : public StringBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Controls();
    virtual __fastcall ~Controls();
};
}
//---------------------------------------------------------------------------
#endif
