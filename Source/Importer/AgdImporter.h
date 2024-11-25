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
    Parser  m_Parser;

    int     GetNum(const String& var, const String& subVar, int index = 0);
    void    UpdateWindow();
    void    UpdateControls();
    void    UpdateJumpTable();
    void    UpdateFont();
    void    UpdateObjects();

public:
            AgdImporter();

    bool    Convert(const String& file);
};
//---------------------------------------------------------------------------
} // namespace Importer
//---------------------------------------------------------------------------
#endif
