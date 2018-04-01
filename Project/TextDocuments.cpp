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
    m_Extension = "txt";
    m_Folder = "Assets\\Files";
    RegisterProperty("Name", "Details", "The name of the document");
    RegisterProperty("Filename", "File", "The name and path of the file");
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
__fastcall EventDocument::EventDocument()
: TextDocument()
{
    m_SubType = "Event";
    m_Folder = "Game\\Events";
    m_Extension = "event";
    RegisterProperty("Name", "Details", "The name of the event source code file");
}
//---------------------------------------------------------------------------
__fastcall SfxDocument::SfxDocument()
: TextDocument()
{
    m_SubType = "SoundFx";
    m_Folder = "Assets\\Sounds";
    m_Extension = "sfx";
    RegisterProperty("Name", "Details", "The name of the SoundFx definitions file");
}
//---------------------------------------------------------------------------