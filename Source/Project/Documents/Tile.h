//---------------------------------------------------------------------------
#ifndef TileH
#define TileH
//---------------------------------------------------------------------------
#include "Images.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class TileDocument : public ImageDocument
{
public:
                        __fastcall  TileDocument(const String& name, const String& extra);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TileDocument(name, extra); };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
