//---------------------------------------------------------------------------
#ifndef CharacterSetH
#define CharacterSetH
//---------------------------------------------------------------------------
#include "BaseImage.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class CharacterSetDocument : public ImageDocument
{
private:
public:
                        __fastcall  CharacterSetDocument(const String& name, const String& extra);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new CharacterSetDocument(name, extra); };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
