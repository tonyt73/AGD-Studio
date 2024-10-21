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
    void      Execute() final;
public:
              MessagesBuilder();
    virtual  ~MessagesBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
