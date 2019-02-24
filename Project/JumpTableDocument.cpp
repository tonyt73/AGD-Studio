//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Project/JumpTableDocument.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall JumpTableDocument::JumpTableDocument(const String& name)
: Document(name)
{
    m_Type = "Jump";
    m_SubType = "Table";
    m_Extension = "json";
    m_Folder = "Game\\Configuration";
    // json loading properties
//    m_PropertyMap["JumpTable.Left"] = &m_Rect.Left;
//    m_PropertyMap["JumpTable.Top"] = &m_Rect.Top;
//    m_PropertyMap["JumpTable.Right"] = &m_Rect.Right;
//    m_PropertyMap["JumpTable.Bottom"] = &m_Rect.Bottom;
    m_File = GetFile();
}
//---------------------------------------------------------------------------
void __fastcall JumpTableDocument::DoSave()
{
//    Push("JumpTable");
//        Write("Left", m_Rect.Left);
//        Write("Top", m_Rect.Top);
//        Write("Right", m_Rect.Right);
//        Write("Bottom", m_Rect.Bottom);
//    Pop();  // JumpTable
}
//---------------------------------------------------------------------------

