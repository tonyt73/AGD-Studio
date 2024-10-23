//---------------------------------------------------------------------------
#ifndef CharacterSetDocumentH
#define CharacterSetDocumentH
//---------------------------------------------------------------------------
#include "ImageDocument.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class CharacterSetDocument : public ImageDocument
{
private:
public:
                        CharacterSetDocument(const String& name, const String& extra);
    static  Document*   Create(const String& name, const String& extra) { return new CharacterSetDocument(name, extra); };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
