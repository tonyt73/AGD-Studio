//---------------------------------------------------------------------------
#ifndef MessagesSectionH
#define MessagesSectionH
//---------------------------------------------------------------------------
#include "Section.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class MessagesSection : public Section
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  MessagesSection();
    virtual __fastcall ~MessagesSection();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
