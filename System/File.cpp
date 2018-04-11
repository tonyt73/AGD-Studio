//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "File.h"
#include "Path.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace System
{
//---------------------------------------------------------------------------
bool __fastcall File::Exists(const String& file)
{
    return System::Ioutils::TFile::Exists(file);
}
//---------------------------------------------------------------------------
String __fastcall File::NameWithoutExtension(const String& file)
{
    return System::Ioutils::TPath::GetFileNameWithoutExtension(file);
}
//---------------------------------------------------------------------------
String __fastcall File::NameWithExtension(const String& file)
{
    return System::Ioutils::TPath::GetFileName(file);
}
//---------------------------------------------------------------------------
String __fastcall File::Extension(const String& file)
{
    return System::Ioutils::TPath::GetExtension(file);
}
//---------------------------------------------------------------------------
String __fastcall File::PathOf(const String& file)
{
    return System::Ioutils::TPath::GetDirectoryName(file);
}
//---------------------------------------------------------------------------
String __fastcall File::ChangeExtension(const String& filename, const String& extension)
{
    return System::Ioutils::TPath::ChangeExtension(filename, extension);
}
//---------------------------------------------------------------------------
String __fastcall File::Combine(const String& path, const String& filename)
{
    return System::Ioutils::TPath::Combine(path, filename);
}
//---------------------------------------------------------------------------
void __fastcall File::WriteText(const String& file, const String& content)
{
    auto path = ExtractFilePath(file);
    System::Ioutils::TDirectory::CreateDirectory(path);
    System::Ioutils::TFile::WriteAllText(file, content);
}
//---------------------------------------------------------------------------
String __fastcall File::ReadText(const String& file)
{
    return System::Ioutils::TFile::ReadAllText(file);
}
//---------------------------------------------------------------------------
void __fastcall File::ReadBytes(const String& file, std::vector<unsigned char>& contents)
{
    auto allBytes = System::Ioutils::TFile::ReadAllText(file);
    for (auto byte : allBytes)
    {
        contents.push_back(byte);
    }
}
//---------------------------------------------------------------------------
void __fastcall File::Copy(const String& source, const String& destination)
{
    auto path = System::Ioutils::TPath::GetDirectoryName(destination);
    System::Ioutils::TDirectory::CreateDirectory(path);
    System::Ioutils::TFile::Copy(source, destination);
}
//---------------------------------------------------------------------------
void __fastcall File::Delete(const String& file)
{
    if (System::Ioutils::TFile::Exists(file))
    {
        System::Ioutils::TFile::Delete(file);
    }
}
//---------------------------------------------------------------------------
void __fastcall File::Rename(const String& source, const String& destination)
{
    if (source.LowerCase() != destination.LowerCase() && System::Ioutils::TFile::Exists(source))
    {
        System::Ioutils::TFile::Move(source, destination);
    }
}
//---------------------------------------------------------------------------
} // file namespace
//---------------------------------------------------------------------------
