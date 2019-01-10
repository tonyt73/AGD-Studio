//---------------------------------------------------------------------------
#ifndef TilesH
#define TilesH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Tiles : public StringBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Tiles();
    virtual __fastcall ~Tiles();
};
}
//---------------------------------------------------------------------------
#endif
