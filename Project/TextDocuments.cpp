//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "TextDocuments.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TextDocument::TextDocument()
: Document()
{
    m_Type = "Text";
    m_SubType = "Plain";
    m_Folder = "Assets\\Files";
    RegisterProperty("Name", "Object", "The name of the document");
    RegisterProperty("Filename", "File", "The name and path of the file");
}
//---------------------------------------------------------------------------
void __fastcall TextDocument::Save()
{
    auto file = System::File::Combine(System::Path::Projects, System::Path::ProjectName);
    file = System::File::Combine(file, m_Folder);
    file = System::File::Combine(file, m_Name);
    // TODO: Save normal text file
}
//---------------------------------------------------------------------------
__fastcall CodeDocument::CodeDocument()
: TextDocument()
{
    m_SubType = "Code";
    m_Folder = "Game\\Code";
    RegisterProperty("Name", "Object", "The name of the source code file");
}
//---------------------------------------------------------------------------
__fastcall EventDocument::EventDocument()
: TextDocument()
{
    m_SubType = "Event";
    m_Folder = "Game\\Events";
    RegisterProperty("Name", "Object", "The name of the event source code file");
}
//---------------------------------------------------------------------------
__fastcall SfxDocument::SfxDocument()
: TextDocument()
{
    m_SubType = "SoundFx";
    m_Folder = "Assets\\Sounds";
    RegisterProperty("Name", "Object", "The name of the SoundFx definitions file");
}
//---------------------------------------------------------------------------
