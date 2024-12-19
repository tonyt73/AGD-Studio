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
    struct AgdControls {
        int Directions;
        int Fires;
        int Options;
        String Defaults;

        int NumKeys() const { return Directions + Fires + Options; }
    };

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
                String                  m_Name;
                String                  m_Keyboard;                     // the Keyboard layout name
                String                  m_Image;                        // a png file with an image of the machine 120x56
                String                  m_GraphicsModeName;             // json loader
std::unique_ptr<Visuals::GraphicsMode>  m_GraphicsMode;
                Visuals::ImageSizing    m_ImageSizing[Visuals::itEnd];  // of each image type
                ToolInfo                m_Compiler;
                ToolInfo                m_Engine;
                ToolInfoExt             m_Assembler;
                ToolInfo                m_Emulator;
                TSize                   m_Window;
                AgdControls             m_Controls;

const Visuals::ImageSizing& __fastcall  GetImageSizing(Visuals::ImageTypes type) const;
    void                    __fastcall  SetControls(const AgdControls& controls);
    void                    __fastcall  SetCompiler(const ToolInfo& info);
    void                    __fastcall  SetEngine(const ToolInfo& info);
    void                    __fastcall  SetAssembler(const ToolInfoExt& info);
    void                    __fastcall  SetEmulator(const ToolInfo& info);

                            __fastcall  MachineConfig();
    void                    __fastcall  Save();

public:
                            __fastcall  MachineConfig(const String& name);

    Visuals::GraphicsMode*  __fastcall  GraphicsMode() const;
    static void             __fastcall  GetMachinesList(std::vector<String>& list);

    bool                    __fastcall  Load(const String& name);

    String                  __property  Name      = { read = m_Name                            };
    String                  __property  Keyboard  = { read = m_Keyboard                        };
    String                  __property  Image     = { read = m_Image                           };
    TSize                   __property  Window    = { read = m_Window                          };
    __property  const AgdControls&      Controls  = { read = m_Controls , write = SetControls  };
    __property  const ToolInfo&         Compiler  = { read = m_Compiler , write = SetCompiler  };
    __property  const ToolInfo&         Engine    = { read = m_Engine   , write = SetEngine    };
    __property  const ToolInfoExt&      Assembler = { read = m_Assembler, write = SetAssembler };
    __property  const ToolInfo&         Emulator  = { read = m_Emulator , write = SetEmulator  };

 const Visuals::ImageSizing __property  ImageSizing[Visuals::ImageTypes type] = { read = GetImageSizing };
};

//---------------------------------------------------------------------------
//class MachineConfigWriter : public MachineConfig
//{
//public:
//                        __fastcall MachineConfigWriter();
//};
//---------------------------------------------------------------------------
} // namespace Project
//---------------------------------------------------------------------------
#endif
