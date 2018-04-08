//---------------------------------------------------------------------------
#pragma hdrstop
#include "MachineConfig.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MachineConfig::MachineConfig()
: JsonFile()
{
}
//---------------------------------------------------------------------------
__fastcall MachineConfig::MachineConfig(const String& name)
: JsonFile()
, m_Name(name)
{
    Load(name);
}
//---------------------------------------------------------------------------
const ImageSizing& __fastcall MachineConfig::GetImageSizing(ImageTypes type) const
{
    if (itStart <= type && type < itEnd)
    {
        return m_ImageSizing[type];
    }
    // default to the smallest image size
    return m_ImageSizing[itCharacterSet];
}
//---------------------------------------------------------------------------
void __fastcall MachineConfig::Load(const String& name)
{
    // Load our configuration
    JsonFile::Load(System::File::Combine(System::Path::Application, "Machines" + System::Path::Separator + name + ".json"));
    // Now load the graphics mode configuration; which in turn will load the palette of colors
    m_GraphicsMode.Load(m_GraphicsModeName);
}
//---------------------------------------------------------------------------
void __fastcall MachineConfig::Save()
{
    // {
    Open(System::File::Combine(System::Path::Application, "Machines" + System::Path::Separator + m_Name + ".json"));
    Write("Name", m_Name);
    Write("GraphicsMode", m_GraphicsModeName);
    Push("ImageSizing");
        Push("Object");
            Push("Minimum");
                Write("Width", (unsigned int)m_ImageSizing[itObject].Minimum.cx);
                Write("Height", (unsigned int)m_ImageSizing[itObject].Minimum.cy);
            Pop();
            Push("Maximum");
                Write("Width", (unsigned int)m_ImageSizing[itObject].Maximum.cx);
                Write("Height", (unsigned int)m_ImageSizing[itObject].Maximum.cy);
            Pop();
            Push("Step");
                Write("Width", (unsigned int)m_ImageSizing[itObject].Step.cx);
                Write("Height", (unsigned int)m_ImageSizing[itObject].Step.cy);
            Pop();
        Pop();
        Push("Sprite");
            Push("Minimum");
                Write("Width", (unsigned int)m_ImageSizing[itSprite].Minimum.cx);
                Write("Height", (unsigned int)m_ImageSizing[itSprite].Minimum.cy);
            Pop();
            Push("Maximum");
                Write("Width", (unsigned int)m_ImageSizing[itSprite].Maximum.cx);
                Write("Height", (unsigned int)m_ImageSizing[itSprite].Maximum.cy);
            Pop();
            Push("Step");
                Write("Width", (unsigned int)m_ImageSizing[itSprite].Step.cx);
                Write("Height", (unsigned int)m_ImageSizing[itSprite].Step.cy);
            Pop();
        Pop();
        Push("Tile");
            Push("Minimum");
                Write("Width", (unsigned int)m_ImageSizing[itTile].Minimum.cx);
                Write("Height", (unsigned int)m_ImageSizing[itTile].Minimum.cy);
            Pop();
            Push("Maximum");
                Write("Width", (unsigned int)m_ImageSizing[itTile].Maximum.cx);
                Write("Height", (unsigned int)m_ImageSizing[itTile].Maximum.cy);
            Pop();
            Push("Step");
                Write("Width", (unsigned int)m_ImageSizing[itTile].Step.cx);
                Write("Height", (unsigned int)m_ImageSizing[itTile].Step.cy);
            Pop();
        Pop();
        Push("CharacterSet");
            Push("Minimum");
                Write("Width", (unsigned int)m_ImageSizing[itCharacterSet].Minimum.cx);
                Write("Height", (unsigned int)m_ImageSizing[itCharacterSet].Minimum.cy);
            Pop();
            Push("Maximum");
                Write("Width", (unsigned int)m_ImageSizing[itCharacterSet].Maximum.cx);
                Write("Height", (unsigned int)m_ImageSizing[itCharacterSet].Maximum.cy);
            Pop();
            Push("Step");
                Write("Width", (unsigned int)m_ImageSizing[itCharacterSet].Step.cx);
                Write("Height", (unsigned int)m_ImageSizing[itCharacterSet].Step.cy);
            Pop();
        Pop();
    Pop();
    Push("CompilerInformation");
        Write("Path", m_CompilerInfo.Path);
        Write("Parameters", m_CompilerInfo.Parameters);
    Pop();
    // }
    Close();
}
//---------------------------------------------------------------------------


//__fastcall MachineConfigWriter::MachineConfigWriter()
//: MachineConfig()
//{
//    m_Name = "ZX Spectrum 256x192 16 Colour";
//    m_GraphicsModeName = "ZX Spectrum Colour";
//    m_ImageSizing[itObject].Minimum.cx = 16;
//    m_ImageSizing[itObject].Minimum.cy = 16;
//    m_ImageSizing[itObject].Maximum.cx = 16;
//    m_ImageSizing[itObject].Maximum.cy = 16;
//    m_ImageSizing[itObject].Step.cx = 0;
//    m_ImageSizing[itObject].Step.cy = 0;
//    m_ImageSizing[itSprite].Minimum.cx = 16;
//    m_ImageSizing[itSprite].Minimum.cy = 16;
//    m_ImageSizing[itSprite].Maximum.cx = 16;
//    m_ImageSizing[itSprite].Maximum.cy = 16;
//    m_ImageSizing[itSprite].Step.cx = 0;
//    m_ImageSizing[itSprite].Step.cy = 0;
//    m_ImageSizing[itTile].Minimum.cx = 8;
//    m_ImageSizing[itTile].Minimum.cy = 8;
//    m_ImageSizing[itTile].Maximum.cx = 128;
//    m_ImageSizing[itTile].Maximum.cy = 128;
//    m_ImageSizing[itTile].Step.cx = 8;
//    m_ImageSizing[itTile].Step.cy = 8;
//    m_ImageSizing[itCharacterSet].Minimum.cx = 8;
//    m_ImageSizing[itCharacterSet].Minimum.cy = 8;
//    m_ImageSizing[itCharacterSet].Maximum.cx = 8;
//    m_ImageSizing[itCharacterSet].Maximum.cy = 8;
//    m_ImageSizing[itCharacterSet].Step.cx = 0;
//    m_ImageSizing[itCharacterSet].Step.cy = 0;
//    m_CompilerInfo.Path = "Machines\\AGDCompile.exe";
//    m_CompilerInfo.Parameters = "%file -tap -sna";
//
//    Save();
//}
//__fastcall MachineConfigWriter::MachineConfigWriter()
//: MachineConfig()
//{
//    m_Name = "Amstrad CPC 160x200 16 Colour";
//    m_GraphicsModeName = "Amstrad CPC Mode 0";
//    m_ImageSizing[itObject].Minimum.cx = 8;
//    m_ImageSizing[itObject].Minimum.cy = 16;
//    m_ImageSizing[itObject].Maximum.cx = 8;
//    m_ImageSizing[itObject].Maximum.cy = 16;
//    m_ImageSizing[itObject].Step.cx = 0;
//    m_ImageSizing[itObject].Step.cy = 0;
//    m_ImageSizing[itSprite].Minimum.cx = 8;
//    m_ImageSizing[itSprite].Minimum.cy = 16;
//    m_ImageSizing[itSprite].Maximum.cx = 8;
//    m_ImageSizing[itSprite].Maximum.cy = 16;
//    m_ImageSizing[itSprite].Step.cx = 0;
//    m_ImageSizing[itSprite].Step.cy = 0;
//    m_ImageSizing[itTile].Minimum.cx = 4;
//    m_ImageSizing[itTile].Minimum.cy = 8;
//    m_ImageSizing[itTile].Maximum.cx = 80;
//    m_ImageSizing[itTile].Maximum.cy = 96;
//    m_ImageSizing[itTile].Step.cx = 8;
//    m_ImageSizing[itTile].Step.cy = 8;
//    m_ImageSizing[itCharacterSet].Minimum.cx = 8;
//    m_ImageSizing[itCharacterSet].Minimum.cy = 8;
//    m_ImageSizing[itCharacterSet].Maximum.cx = 8;
//    m_ImageSizing[itCharacterSet].Maximum.cy = 8;
//    m_ImageSizing[itCharacterSet].Step.cx = 0;
//    m_ImageSizing[itCharacterSet].Step.cy = 0;
//    m_CompilerInfo.Path = "Compilers\\CPC-Compile.exe";
//    m_CompilerInfo.Parameters = "%file -tap -sna";
//
//    Save();
//}
__fastcall MachineConfigWriter::MachineConfigWriter()
: MachineConfig()
{
    m_Name = "Acorn Atom 256x192 Monochrome";
    m_GraphicsModeName = "Acorn Atom Monochrome";
    m_ImageSizing[itObject].Minimum.cx = 16;
    m_ImageSizing[itObject].Minimum.cy = 16;
    m_ImageSizing[itObject].Maximum.cx = 16;
    m_ImageSizing[itObject].Maximum.cy = 16;
    m_ImageSizing[itObject].Step.cx = 0;
    m_ImageSizing[itObject].Step.cy = 0;
    m_ImageSizing[itSprite].Minimum.cx = 16;
    m_ImageSizing[itSprite].Minimum.cy = 16;
    m_ImageSizing[itSprite].Maximum.cx = 16;
    m_ImageSizing[itSprite].Maximum.cy = 16;
    m_ImageSizing[itSprite].Step.cx = 0;
    m_ImageSizing[itSprite].Step.cy = 0;
    m_ImageSizing[itTile].Minimum.cx = 8;
    m_ImageSizing[itTile].Minimum.cy = 8;
    m_ImageSizing[itTile].Maximum.cx = 128;
    m_ImageSizing[itTile].Maximum.cy = 128;
    m_ImageSizing[itTile].Step.cx = 8;
    m_ImageSizing[itTile].Step.cy = 8;
    m_ImageSizing[itCharacterSet].Minimum.cx = 8;
    m_ImageSizing[itCharacterSet].Minimum.cy = 8;
    m_ImageSizing[itCharacterSet].Maximum.cx = 8;
    m_ImageSizing[itCharacterSet].Maximum.cy = 8;
    m_ImageSizing[itCharacterSet].Step.cx = 0;
    m_ImageSizing[itCharacterSet].Step.cy = 0;
    m_CompilerInfo.Path = "Compilers\\Atom-Compile.exe";
    m_CompilerInfo.Parameters = "%file -tap -sna";

    Save();
}

