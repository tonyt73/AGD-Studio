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

    struct CompilerInfo
    {
        String  Path;
        String  Parameters;
    };

protected:
    String                              m_Name;
    String                              m_GraphicsModeName;     // json loader
    std::unique_ptr<Agdx::GraphicsMode> m_GraphicsMode;
    ImageSizing                         m_ImageSizing[itEnd];   // of each image type
    CompilerInfo                        m_CompilerInfo;

    const ImageSizing&      __fastcall  GetImageSizing(ImageTypes type) const;

                            __fastcall  MachineConfig();
    void                    __fastcall  Save();

public:
                            __fastcall  MachineConfig(const String& name);
    virtual                 __fastcall ~MachineConfig();

  const Agdx::GraphicsMode& __fastcall  GraphicsMode() const;
    static void             __fastcall  GetMachinesList(std::vector<String>& list);

    void                    __fastcall  Load(const String& name);

    String                  __property  Name = { read = m_Name };
    const ImageSizing       __property  ImageSizing[ImageTypes type] = { read = GetImageSizing };
    const CompilerInfo      __property  CompilerInfo = { read = m_CompilerInfo };
    // TODO:
    // Key Map
    // Sounds
    // Jump Table
    // New Project Options
};

//---------------------------------------------------------------------------
//class MachineConfigWriter : public MachineConfig
//{
//public:
//                        __fastcall MachineConfigWriter();
//};
//---------------------------------------------------------------------------
#endif
