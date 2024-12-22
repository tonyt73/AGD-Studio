//---------------------------------------------------------------------------
#ifndef CharacterSetH
#define CharacterSetH
//---------------------------------------------------------------------------
#include "BaseImage.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class CharacterSetDocument final : public ImageDocument
{
private:
public:
                        __fastcall  CharacterSetDocument(const String& name, const String& extra);
                        __fastcall ~CharacterSetDocument() final;
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new CharacterSetDocument(name, extra); }
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
