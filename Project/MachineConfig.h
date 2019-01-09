//---------------------------------------------------------------------------
#ifndef MachineConfigConfigH
#define MachineConfigConfigH
//---------------------------------------------------------------------------
#include "System/JsonFile.h"
#include "Graphics/GraphicsMode.h"
#include "Graphics/GraphicsTypes.h"
//---------------------------------------------------------------------------
class MachineConfig : public System::JsonFile
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
    String                              m_Image;                // a png file with an image of the machine 120x56
    String                              m_GraphicsModeName;     // json loader
    std::unique_ptr<Agdx::GraphicsMode> m_GraphicsMode;
    ImageSizing                         m_ImageSizing[itEnd];   // of each image type
    ToolInfo                            m_Compiler;
    ToolInfoExt                         m_Assembler;
    ToolInfo                            m_Emulator;

    const ImageSizing&      __fastcall  GetImageSizing(ImageTypes type) const;
    void                    __fastcall  SetCompiler(const ToolInfo& info);
    void                    __fastcall  SetAssembler(const ToolInfoExt& info);
    void                    __fastcall  SetEmulator(const ToolInfo& info);

                            __fastcall  MachineConfig();
    void                    __fastcall  Save();

public:
                            __fastcall  MachineConfig(const String& name);
    virtual                 __fastcall ~MachineConfig();

    Agdx::GraphicsMode*     __fastcall  GraphicsMode() const;
    static void             __fastcall  GetMachinesList(std::vector<String>& list);

    void                    __fastcall  Load(const String& name);

    String                  __property  Name = { read = m_Name };
    String                  __property  Image = { read = m_Image };
    const ImageSizing       __property  ImageSizing[ImageTypes type] = { read = GetImageSizing };
    __property  const ToolInfo&         Compiler = { read = m_Compiler, write = SetCompiler };
    __property  const ToolInfoExt&      Assembler = { read = m_Assembler, write = SetAssembler };
    __property  const ToolInfo&         Emulator = { read = m_Emulator, write = SetEmulator };
};

//---------------------------------------------------------------------------
//class MachineConfigWriter : public MachineConfig
//{
//public:
//                        __fastcall MachineConfigWriter();
//};
//---------------------------------------------------------------------------
#endif
