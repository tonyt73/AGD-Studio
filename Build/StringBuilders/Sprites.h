//---------------------------------------------------------------------------
#ifndef SpritesH
#define SpritesH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Sprites : public StringBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Sprites();
    virtual __fastcall ~Sprites();
};
}
//---------------------------------------------------------------------------
#endif
