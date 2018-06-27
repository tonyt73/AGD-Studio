//---------------------------------------------------------------------------
#ifndef ImporterH
#define ImporterH
//---------------------------------------------------------------------------
#include <memory>
#include <vector>
#include "Snapshot.h"
//---------------------------------------------------------------------------
class Importer
{
public:
                __fastcall  Importer();
    bool        __fastcall  Convert(const String& file);
};
//---------------------------------------------------------------------------
#endif
