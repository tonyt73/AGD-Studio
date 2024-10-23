//---------------------------------------------------------------------------
#ifndef MachineConfigH
#define MachineConfigH
//---------------------------------------------------------------------------
#include "Services/JsonFile.h"
#include "Visuals/GraphicsMode.h"
#include "Visuals/GraphicsTypes.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class MachineConfig : public Services::JsonFile
{
public:

    struct ToolInfo
    {
        ToolInfo() {}
        ToolInfo(const String& path, const String& params)
        : Path(path)
        , Parameters(params)
        {}
        String  Path;
        String  Parameters;
    };
    struct ToolInfoExt : public ToolInfo
    {
        ToolInfoExt() {}
        ToolInfoExt(const String& path, const String& params, const String& prepend, const String& append)
        : ToolInfo(path, params)
        , Prepend(prepend)
        , Append(append)
        {}
        String  Prepend;
        String  Append;
    };

protected:
    String                              m_Name;
    String                              m_Keyboard;             // the Keyboard layout name
    String                              m_Image;                // a png file with an image of the machine 120x56
    String                              m_GraphicsModeName;     // json loader
 std::unique_ptr<Visuals::GraphicsMode> m_GraphicsMode;
    Visuals::ImageSizing                m_ImageSizing[Visuals::itEnd];   // of each image type
    ToolInfo                            m_Compiler;
    ToolInfo                            m_Engine;
    ToolInfoExt                         m_Assembler;
    ToolInfo                            m_Emulator;

    const Visuals::ImageSizing&         GetImageSizing(Visuals::ImageTypes type) const;
    void                                SetCompiler(const ToolInfo& info);
    void                                SetEngine(const ToolInfo& info);
    void                                SetAssembler(const ToolInfoExt& info);
    void                                SetEmulator(const ToolInfo& info);

                                        MachineConfig();
    void                                Save();

public:
                                        MachineConfig(const String& name);
    virtual                            ~MachineConfig();

    Visuals::GraphicsMode*              GraphicsMode() const;
    static void                         GetMachinesList(std::vector<String>& list);

    void                                Load(const String& name);

    String                  __property  Name = { read = m_Name };
    String                  __property  Keyboard = { read = m_Keyboard };
    String                  __property  Image = { read = m_Image };
 const Visuals::ImageSizing __property  ImageSizing[Visuals::ImageTypes type] = { read = GetImageSizing };
    __property  const ToolInfo&         Compiler = { read = m_Compiler, write = SetCompiler };
    __property  const ToolInfo&         Engine = { read = m_Engine, write = SetEngine };
    __property  const ToolInfoExt&      Assembler = { read = m_Assembler, write = SetAssembler };
    __property  const ToolInfo&         Emulator = { read = m_Emulator, write = SetEmulator };
};

//---------------------------------------------------------------------------
//class MachineConfigWriter : public MachineConfig
//{
//public:
//   MachineConfigWriter();
//};
//---------------------------------------------------------------------------
} // namespace Project
//---------------------------------------------------------------------------
#endif
