//---------------------------------------------------------------------------
#ifndef AgdImporterH
#define AgdImporterH
//---------------------------------------------------------------------------
#include "Parser.h"
#include "Project/Documents/MachineConfig.h"
#include "Visuals/GraphicsTypes.h"
//---------------------------------------------------------------------------
namespace Importer
{
//---------------------------------------------------------------------------
class AgdImporter
{
private:
    Parser m_Parser;
    TSize  m_Window;

    int    GetNum(const String& var, const String& subVar, int index = 0);
    bool   UpdateWindow();
    bool   UpdateControls();
    bool   UpdateJumpTable();
    bool   UpdateFont();
    bool   AddImages(const String& name, const String& imgType);
    bool   AddMessages();
    bool   AddEvents();
    bool   AddMap();

public:
           AgdImporter();

    bool   Convert(const String& file);
};
//---------------------------------------------------------------------------
} // namespace Importer
//---------------------------------------------------------------------------
#endif
