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
    void      Execute() final;
public:
              ObjectsBuilder();
    virtual  ~ObjectsBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
