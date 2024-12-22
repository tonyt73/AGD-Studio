//---------------------------------------------------------------------------
#ifndef SpriteH
#define SpriteH
//---------------------------------------------------------------------------
#include "BaseImage.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class SpriteDocument final : public ImageDocument
{
public:
                        __fastcall  SpriteDocument(const String& name, const String& extra);
                        __fastcall ~SpriteDocument() final;
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new SpriteDocument(name, extra); }
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
