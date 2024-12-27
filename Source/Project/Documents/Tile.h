//---------------------------------------------------------------------------
#ifndef TileH
#define TileH
//---------------------------------------------------------------------------
#include "BaseImage.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class TileDocument final : public ImageDocument
{
public:

                        __fastcall  TileDocument(const String& name, const String& extra);
                        __fastcall ~TileDocument() final;

    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new TileDocument(name, extra); }
            void        __fastcall  SetType(const String& type);
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
