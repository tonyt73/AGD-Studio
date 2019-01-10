//---------------------------------------------------------------------------
#ifndef FontH
#define FontH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Font : public StringBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Font();
    virtual __fastcall ~Font();
};
}
//---------------------------------------------------------------------------
#endif
