//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "TextDocuments.h"
#include "Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TextDocument::TextDocument(const String& name)
: Document(name)
{
    m_Type = "Text";
    m_SubType = "Plain";
    m_Extension = "txt";
    m_Folder = "Game\\Files";
    RegisterProperty("Name", "Details", "The name of the document");
    RegisterProperty("Filename", "File", "The name and path of the file");
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
    if (System::File::Exists(m_File))
    {
        // yes, load it
        auto allLines = System::File::ReadText(m_File);
        allLines += lines;
        System::File::WriteText(m_File, allLines);
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
    if (m_Name != "unnamed" && !System::File::Exists(file))
    {
        // create the file and add an AGD header
        auto date = DateTimeToStr(Now());
        auto header = ";\r\n; " + System::Path::ProjectName + "\r\n; An AGDX game\r\n; Created: " + date + "\r\n; Event: " + System::File::NameWithoutExtension(file) + "\r\n;";
        System::File::WriteText(file, header);
    }
    m_File = GetFile();
}
//---------------------------------------------------------------------------
__fastcall MessageDocument::MessageDocument(const String& name)
: TextDocument(name)
{
    m_SubType = "Message";
    m_Folder = "Game\\Messages";
    m_Extension = "txt";
    RegisterProperty("Name", "Details", "The name of the messages text file");
    auto file = GetFile();
    if (m_Name != "unnamed" && !System::File::Exists(file))
    {
        // create the file and add an AGD header
        auto date = DateTimeToStr(Now());
        auto header = ";\r\n; " + System::Path::ProjectName + "\r\n; An AGDX game\r\n; Created: " + date + "\r\n; Simply place a new message per line. Comments ';' are stripped before compilation\r\n;";
        System::File::WriteText(file, header);
    }
    m_File = file;
}
//---------------------------------------------------------------------------
__fastcall SfxDocument::SfxDocument(const String& name)
: TextDocument(name)
{
    m_SubType = "SoundFx";
    m_Folder = "Game\\Sounds";
    m_Extension = "sfx";
    RegisterProperty("Name", "Details", "The name of the SoundFx definitions file");
    auto file = GetFile();
    if (m_Name != "unnamed" && !System::File::Exists(file))
    {
        // create the file and add an AGD header
        auto date = DateTimeToStr(Now());
        auto header = ";\r\n; " + System::Path::ProjectName + "\r\n; An AGDX game\r\n; Created: " + date + "\r\n; Simply place a Sound Fx file name per line. Comments ';' are stripped before compilation\r\n;";
        System::File::WriteText(file, header);
    }
    m_File = GetFile();
}
//---------------------------------------------------------------------------
__fastcall AGDDocument::AGDDocument(const String& name)
: TextDocument(name)
{
    m_SubType = "AGD";
    m_Folder = "Game\\Output";
    m_Extension = "agd";
    m_ReadOnly = true;
    RegisterProperty("Name", "Details", "The name of the AGD source code file");
    auto file = GetFile();
    if (m_Name != "unnamed" && !System::File::Exists(file))
    {
        // create the file and add an AGD header
        auto date = DateTimeToStr(Now());
        auto header = ";\r\n; " + System::Path::ProjectName + "\r\n; An AGDX game\r\n; Created: " + date + "\r\n; This file is read-only and periodically auto generated.";
        System::File::WriteText(file, header);
    }
    m_File = GetFile();
}
//---------------------------------------------------------------------------
