//---------------------------------------------------------------------------
#ifndef ObjectsBuilderBuilderH
#define ObjectsBuilderBuilderH
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class ObjectsBuilder : public SectionBuilder
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  ObjectsBuilder();
    virtual __fastcall ~ObjectsBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
