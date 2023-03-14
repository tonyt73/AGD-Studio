//---------------------------------------------------------------------------
#ifndef MessagesH
#define MessagesH
//---------------------------------------------------------------------------
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
namespace SectionBuilders
{
class Messages : public SectionBuilder
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
