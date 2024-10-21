//---------------------------------------------------------------------------
#ifndef WindowBuilderBuilderH
#define WindowBuilderBuilderH
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class WindowBuilder : public SectionBuilder
{
protected:
    void      Execute() final;
public:
              WindowBuilder();
    virtual  ~WindowBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
