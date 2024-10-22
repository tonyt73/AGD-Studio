//---------------------------------------------------------------------------
#ifndef TileDocumentH
#define TileDocumentH
//---------------------------------------------------------------------------
#include "ImageDocument.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class TileDocument : public ImageDocument
{
public:
                         TileDocument(const String& name, const String& extra);
    static  Document*    Create(const String& name, const String& extra) { return new TileDocument(name, extra); };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
