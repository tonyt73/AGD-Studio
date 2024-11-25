//---------------------------------------------------------------------------
#ifndef AgdImporterH
#define AgdImporterH
//---------------------------------------------------------------------------
#include "Project/Documents/MachineConfig.h"
#include "Visuals/GraphicsTypes.h"
//---------------------------------------------------------------------------
namespace Importer
{
//---------------------------------------------------------------------------
class AgdImporter
{
private:

public:
            __fastcall  AgdImporter();

    bool    __fastcall  Convert(const String& file);
    bool    __fastcall  CanConvert(const String& file);
    String  __fastcall  GetMachine(const String& file);
};
//---------------------------------------------------------------------------
} // namespace Importer
//---------------------------------------------------------------------------
#endif
