//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "File.h"
#include "Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Services
{
//---------------------------------------------------------------------------
bool File::Exists(const String& file)
{
    return System::Ioutils::TFile::Exists(Cleanse(file));
}
//---------------------------------------------------------------------------
String File::NameWithoutExtension(const String& file)
{
    return System::Ioutils::TPath::GetFileNameWithoutExtension(file);
}
//---------------------------------------------------------------------------
String File::NameWithExtension(const String& file)
{
    return System::Ioutils::TPath::GetFileName(file);
}
//---------------------------------------------------------------------------
String File::Extension(const String& file)
{
    return System::Ioutils::TPath::GetExtension(file);
}
//---------------------------------------------------------------------------
String File::PathOf(const String& file)
{
    return Cleanse(System::Ioutils::TPath::GetDirectoryName(file));
}
//---------------------------------------------------------------------------
String File::ChangeExtension(const String& filename, const String& extension)
{
    return System::Ioutils::TPath::ChangeExtension(filename, extension);
}
//---------------------------------------------------------------------------
String File::Cleanse(const String& file)
{
    auto lfile = file;
    auto nfile = file;
    do {
        lfile = nfile;
        nfile = StringReplace(nfile, "\\\\", "\\", TReplaceFlags());
        nfile = StringReplace(nfile, "//", "/", TReplaceFlags());
    } while (nfile != lfile);
    return nfile;
}
//---------------------------------------------------------------------------
String File::Combine(const String& path, const String& filename)
{
    return Cleanse(System::Ioutils::TPath::Combine(path, filename));
}
//---------------------------------------------------------------------------
String File::Resolve(const String& parent, const String& path)
{
    return Services::File::Exists(path) ? path : Services::File::Combine(parent, path);
}
//---------------------------------------------------------------------------
void File::WriteText(const String& file, const String& content)
{
    auto path = ExtractFilePath(file);
    System::Ioutils::TDirectory::CreateDirectory(path);
    System::Ioutils::TFile::WriteAllText(file, content);
}
//---------------------------------------------------------------------------
void File::PrependText(const String& file, const String& content)
{
    auto text = ReadText(file);
    WriteText(file, content + text);
}
//---------------------------------------------------------------------------
void File::AppendText(const String& file, const String& content)
{
    auto text = ReadText(file);
    WriteText(file, text + content);
}
//---------------------------------------------------------------------------
String File::ReadText(const String& file)
{
    return System::Ioutils::TFile::ReadAllText(file);
}
//---------------------------------------------------------------------------
void File::ReadBytes(const String& file, std::vector<unsigned char>& contents)
{
    auto allBytes = System::Ioutils::TFile::ReadAllText(file);
    for (auto byte : allBytes)
    {
        contents.push_back(byte);
    }
}
//---------------------------------------------------------------------------
File::StrLines File::ReadLines(const String& file)
{
    return System::Ioutils::TFile::ReadAllLines(file);
}
//---------------------------------------------------------------------------
void File::Copy(const String& source, const String& destination, bool overwrite)
{
    auto path = System::Ioutils::TPath::GetDirectoryName(destination);
    System::Ioutils::TDirectory::CreateDirectory(path);
    System::Ioutils::TFile::Copy(source, destination, overwrite);
}
//---------------------------------------------------------------------------
void File::Delete(const String& file)
{
    if (System::Ioutils::TFile::Exists(file))
    {
        System::Ioutils::TFile::Delete(file);
    }
}
//---------------------------------------------------------------------------
void File::Rename(const String& source, const String& destination)
{
    if (source.LowerCase() != destination.LowerCase() && System::Ioutils::TFile::Exists(source))
    {
        System::Ioutils::TFile::Move(source, destination);
    }
}
//---------------------------------------------------------------------------
} // Services namespace
//---------------------------------------------------------------------------
