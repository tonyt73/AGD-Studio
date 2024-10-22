//---------------------------------------------------------------------------
#ifndef SpriteDocumentH
#define SpriteDocumentH
//---------------------------------------------------------------------------
#include "ImageDocument.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class SpriteDocument : public ImageDocument
{
public:
                         SpriteDocument(const String& name, const String& extra);
    static  Document*    Create(const String& name, const String& extra) { return new SpriteDocument(name, extra); };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
