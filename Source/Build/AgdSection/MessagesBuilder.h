//---------------------------------------------------------------------------
#ifndef MessagesBuilderBuilderH
#define MessagesBuilderBuilderH
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class MessagesBuilder : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  MessagesBuilder();
    virtual __fastcall ~MessagesBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
