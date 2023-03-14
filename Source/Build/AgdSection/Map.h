//---------------------------------------------------------------------------
#ifndef MapH
#define MapH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Map : public SectionBuilder
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

