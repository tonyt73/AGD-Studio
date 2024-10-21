//---------------------------------------------------------------------------
#ifndef SpritesBuilderBuilderH
#define SpritesBuilderBuilderH
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class SpritesBuilder : public SectionBuilder
{
protected:
    void      Execute() final;
public:
              SpritesBuilder();
    virtual  ~SpritesBuilder();
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
