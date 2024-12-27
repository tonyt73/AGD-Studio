//---------------------------------------------------------------------------
#ifndef SpritesSectionH
#define SpritesSectionH
//---------------------------------------------------------------------------
#include "Section.h"
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
class SpritesSection : public Section
{
protected:
    void    __fastcall  Execute() final;
public:
            __fastcall  SpritesSection();
    virtual __fastcall ~SpritesSection() override;
};
//---------------------------------------------------------------------------
} // Build namespace
//---------------------------------------------------------------------------
#endif
