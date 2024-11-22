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
    int                 m_Blocks;
    int                 m_Objects;
    int                 m_Sprites;
    int                 m_Screens;
    int                 m_FontCharacter;

    String  __fastcall  PreProcess(const String& data) const;
    void    __fastcall  ConvertToImage(const Project::MachineConfig& machineConfig, const String& data, Visuals::ImageTypes type, int instance, int frames);
    void    __fastcall  ConvertData(const Project::MachineConfig& machineConfig, const String& data);
    void    __fastcall  ConvertScreen(const Project::MachineConfig& machineConfig, const String& data);
    void    __fastcall  ConvertControls(const Project::MachineConfig& machineConfig, const String& data);
    void    __fastcall  ConvertJumpTable(const Project::MachineConfig& machineConfig, const String& data);
    void    __fastcall  ConvertMap(const Project::MachineConfig& machineConfig, const String& data);
    void    __fastcall  ConvertEventCode();
    void    __fastcall  ConvertWindow(const Project::MachineConfig& machineConfig, const String& data);
    void    __fastcall  ConvertBlock(const Project::MachineConfig& machineConfig, const String& data);
    void    __fastcall  ConvertObject(const Project::MachineConfig& machineConfig, const String& data);
    void    __fastcall  ConvertSprite(const Project::MachineConfig& machineConfig, const String& data, unsigned int spriteHeight);
    void    __fastcall  ConvertFont(const Project::MachineConfig& machineConfig, const String& data);
    void    __fastcall  ConvertMessages(const String& data);

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
