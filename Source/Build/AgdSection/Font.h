//---------------------------------------------------------------------------
#ifndef FontH
#define FontH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Font : public SectionBuilder
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
