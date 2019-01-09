//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
#include "MachineConfig.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall MachineConfig::MachineConfig(const String& name)
: JsonFile()
, m_Name(name)
{
    m_PropertyMap["Name"] = &m_Name;
    m_PropertyMap["Image"] = &m_Image;
    m_PropertyMap["GraphicsMode"] = &m_GraphicsModeName;
    m_PropertyMap["ImageSizing.Object.Minimum.Width"] = &m_ImageSizing[itObject].Minimum.cx;
    m_PropertyMap["ImageSizing.Object.Minimum.Height"] = &m_ImageSizing[itObject].Minimum.cy;
    m_PropertyMap["ImageSizing.Object.Maximum.Width"] = &m_ImageSizing[itObject].Maximum.cx;
    m_PropertyMap["ImageSizing.Object.Maximum.Height"] = &m_ImageSizing[itObject].Maximum.cy;
    m_PropertyMap["ImageSizing.Object.Step.Width"] = &m_ImageSizing[itObject].Step.cx;
    m_PropertyMap["ImageSizing.Object.Step.Height"] = &m_ImageSizing[itObject].Step.cy;
    m_PropertyMap["ImageSizing.Sprite.Minimum.Width"] = &m_ImageSizing[itSprite].Minimum.cx;
    m_PropertyMap["ImageSizing.Sprite.Minimum.Height"] = &m_ImageSizing[itSprite].Minimum.cy;
    m_PropertyMap["ImageSizing.Sprite.Maximum.Width"] = &m_ImageSizing[itSprite].Maximum.cx;
    m_PropertyMap["ImageSizing.Sprite.Maximum.Height"] = &m_ImageSizing[itSprite].Maximum.cy;
    m_PropertyMap["ImageSizing.Sprite.Step.Width"] = &m_ImageSizing[itSprite].Step.cx;
    m_PropertyMap["ImageSizing.Sprite.Step.Height"] = &m_ImageSizing[itSprite].Step.cy;
    m_PropertyMap["ImageSizing.Tile.Minimum.Width"] = &m_ImageSizing[itTile].Minimum.cx;
    m_PropertyMap["ImageSizing.Tile.Minimum.Height"] = &m_ImageSizing[itTile].Minimum.cy;
    m_PropertyMap["ImageSizing.Tile.Maximum.Width"] = &m_ImageSizing[itTile].Maximum.cx;
    m_PropertyMap["ImageSizing.Tile.Maximum.Height"] = &m_ImageSizing[itTile].Maximum.cy;
    m_PropertyMap["ImageSizing.Tile.Step.Width"] = &m_ImageSizing[itTile].Step.cx;
    m_PropertyMap["ImageSizing.Tile.Step.Height"] = &m_ImageSizing[itTile].Step.cy;
    m_PropertyMap["ImageSizing.CharacterSet.Minimum.Width"] = &m_ImageSizing[itCharacterSet].Minimum.cx;
    m_PropertyMap["ImageSizing.CharacterSet.Minimum.Height"] = &m_ImageSizing[itCharacterSet].Minimum.cy;
    m_PropertyMap["ImageSizing.CharacterSet.Maximum.Width"] = &m_ImageSizing[itCharacterSet].Maximum.cx;
    m_PropertyMap["ImageSizing.CharacterSet.Maximum.Height"] = &m_ImageSizing[itCharacterSet].Maximum.cy;
    m_PropertyMap["ImageSizing.CharacterSet.Step.Width"] = &m_ImageSizing[itCharacterSet].Step.cx;
    m_PropertyMap["ImageSizing.CharacterSet.Step.Height"] = &m_ImageSizing[itCharacterSet].Step.cy;
    m_PropertyMap["Tools.Compiler.Path"] = &m_Compiler.Path;
    m_PropertyMap["Tools.Compiler.Parameters"] = &m_Compiler.Parameters;
    m_PropertyMap["Tools.Assembler.Path"] = &m_Assembler.Path;
    m_PropertyMap["Tools.Assembler.Parameters"] = &m_Assembler.Parameters;
    m_PropertyMap["Tools.Assembler.Prepend"] = &m_Assembler.Prepend;
    m_PropertyMap["Tools.Assembler.Append"] = &m_Assembler.Append;
    m_PropertyMap["Tools.Emulator.Path"] = &m_Emulator.Path;
    m_PropertyMap["Tools.Emulator.Parameters"] = &m_Emulator.Parameters;

    m_GraphicsMode = std::make_unique<Agdx::GraphicsMode>();
}
//---------------------------------------------------------------------------
__fastcall MachineConfig::~MachineConfig()
{
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
    m_GraphicsMode->Load(m_GraphicsModeName);
}
//---------------------------------------------------------------------------
Agdx::GraphicsMode* __fastcall MachineConfig::GraphicsMode() const
{
    return m_GraphicsMode.get();
}
//---------------------------------------------------------------------------
void __fastcall MachineConfig::GetMachinesList(std::vector<String>& list)
{
    list.clear();
    auto files = System::Path::GetFiles(System::Path::lpApplication, "*.json", "Machines");
    for (const auto& file : files)
    {
        list.push_back(System::File::NameWithoutExtension(file));
    }
}
//---------------------------------------------------------------------------
void __fastcall MachineConfig::SetCompiler(const ToolInfo& info)
{
    m_Compiler = info;
    Save();
}
//---------------------------------------------------------------------------
void __fastcall MachineConfig::SetAssembler(const ToolInfoExt& info)
{
    m_Assembler = info;
    Save();
}
//---------------------------------------------------------------------------
void __fastcall MachineConfig::SetEmulator(const ToolInfo& info)
{
    m_Emulator = info;
    Save();
}
//---------------------------------------------------------------------------
void __fastcall MachineConfig::Save()
{
    // {
    Open(System::File::Combine(System::Path::Application, "Machines" + System::Path::Separator + m_Name + ".json"));
    Write("Name", m_Name);
    Write("Image", m_Image);
    Write("GraphicsMode", m_GraphicsModeName);
    Push("Tools");
        Push("Compiler");
            Write("Path", m_Compiler.Path);
            Write("Parameters", m_Compiler.Parameters);
        Pop();
        Push("Assembler");
            Write("Path", m_Assembler.Path);
            Write("Parameters", m_Assembler.Parameters);
            Write("Prepend", m_Assembler.Prepend);
            Write("Append", m_Assembler.Append);
        Pop();
        Push("Emulator");
            Write("Path", m_Emulator.Path);
            Write("Parameters", m_Emulator.Parameters);
        Pop();
    Pop();
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
//__fastcall MachineConfigWriter::MachineConfigWriter()
//: MachineConfig()
//{
//    m_Name = "Acorn Atom 256x192 Monochrome";
//    m_GraphicsModeName = "Acorn Atom Monochrome";
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
//    m_CompilerInfo.Path = "Compilers\\Atom-Compile.exe";
//    m_CompilerInfo.Parameters = "%file -tap -sna";
//
//    Save();
//}

