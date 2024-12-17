//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Text.h"
#include "Messaging/Messaging.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
__fastcall TextDocument::TextDocument(const String& name)
: Document(name)
{
    m_Type = "Text";
    m_SubType = "Plain";
    m_Extension = "txt";
    m_Folder = "Game\\Files";
    if (IsValid(name))
    {
        RegisterProperty("Name", "Details", "The name of the document");
        RegisterProperty("Filename", "File", "The name and path of the file");
    }
    m_File = GetFile();
}
//---------------------------------------------------------------------------
void __fastcall TextDocument::DoSave()
{
}
//---------------------------------------------------------------------------
void __fastcall TextDocument::Save()
{
}
//---------------------------------------------------------------------------
bool __fastcall TextDocument::Load()
{
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TextDocument::Add(const String& lines)
{
    if (Services::File::Exists(m_File))
    {
        // yes, load it
        auto allLines = Services::File::ReadText(m_File);
        allLines += lines;
        Services::File::WriteText(m_File, allLines);
    }
}
//---------------------------------------------------------------------------
__fastcall EventDocument::EventDocument(const String& name)
: TextDocument(name)
{
    m_SubType = "Event";
    m_Folder = "Game\\Events";
    m_Extension = "event";
    RegisterProperty("Name", "Details", "The name of the event source code file");
    auto file = GetFile();
    if (IsValid(name) && !Services::File::Exists(file))
    {
        // create the file and add an AGD header
        auto date = DateTimeToStr(Now());
        auto header = ";\r\n; " + Services::Folders::ProjectName + "\r\n; An AGD game\r\n; Created: " + date + "\r\n; Event: " + Services::File::NameWithoutExtension(file) + "\r\n;";
        Services::File::WriteText(file, header);
    }
    m_File = file;
}
//---------------------------------------------------------------------------
__fastcall MessageDocument::MessageDocument(const String& name)
: TextDocument(name)
{
    m_SubType = "Messages";
    m_Folder = "Game\\Files";
    m_Extension = "txt";
    RegisterProperty("Name", "Details", "The name of the messages text file");
    auto file = GetFile();
    if (IsValid(name) && !Services::File::Exists(file))
    {
        // create the file and add an AGD header
        auto date = DateTimeToStr(Now());
        auto header = ";\r\n; " + Services::Folders::ProjectName + "\r\n; An AGD game\r\n; Created: " + date + "\r\n; Simply place a new message per line. Comments ';' are stripped before compilation\r\n;";
        Services::File::WriteText(file, header);
    }
    m_File = file;
}
//---------------------------------------------------------------------------
__fastcall SfxDocument::SfxDocument(const String& name)
: TextDocument(name)
{
    m_SubType = "SoundFx";
    m_Folder = "Game\\Files";
    m_Extension = "sfx";
    RegisterProperty("Name", "Details", "The name of the SoundFx definitions file");
    auto file = GetFile();
    if (IsValid(name) && !Services::File::Exists(file))
    {
        // create the file and add an AGD header
        auto date = DateTimeToStr(Now());
        auto header = ";\r\n; " + Services::Folders::ProjectName + "\r\n; An AGD game\r\n; Created: " + date + "\r\n; Simply place a Sound Fx file name per line. Comments ';' are stripped before compilation\r\n;";
        Services::File::WriteText(file, header);
    }
    m_File = file;
}
//---------------------------------------------------------------------------
__fastcall AGDDocument::AGDDocument(const String& name)
: TextDocument(name)
{
    m_SubType = "AGD";
    m_Folder = "Game\\Output";
    m_Extension = "agd";
    SetShowFileExtension(true);
    m_File = GetFile();
    m_ReadOnly = true;
    if (IsValid(name))
    {
        RegisterProperty("Name", "Details", "The name of the AGD source code file");
    }
}
//---------------------------------------------------------------------------
__fastcall AssemblyDocument::AssemblyDocument(const String& name)
: TextDocument(name)
{
    m_SubType = "Assembly";
    m_Folder = "Game\\Output";
    m_Extension = "asm";
    SetShowFileExtension(true);
    m_ReadOnly = true;
    RegisterProperty("Name", "Details", "The name of the Assembly source code file");
    m_File = GetFile();
}
//---------------------------------------------------------------------------
