//---------------------------------------------------------------------------
#ifndef MapH
#define MapH
//---------------------------------------------------------------------------
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
namespace StringBuilders
{
class Map : public StringBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  Map();
    virtual __fastcall ~Map();
};
}
//---------------------------------------------------------------------------
#endif

