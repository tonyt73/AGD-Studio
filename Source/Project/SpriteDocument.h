//---------------------------------------------------------------------------
#ifndef SpriteDocumentH
#define SpriteDocumentH
//---------------------------------------------------------------------------
#include "ImageDocument.h"
//---------------------------------------------------------------------------
class SpriteDocument : public ImageDocument
{
public:
                        __fastcall  SpriteDocument(const String& name, const String& extra);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new SpriteDocument(name, extra); };
};
//---------------------------------------------------------------------------
#endif
