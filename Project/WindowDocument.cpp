//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Project/WindowDocument.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall WindowDocument::WindowDocument(const String& name)
: Document(name)
{
    m_Type = "Window";
    m_SubType = "Definition";
    m_Extension = "json";
    m_Folder = "Game\\Window";
    RegisterProperty("Left", "Position", "The left most character column of the window");
    RegisterProperty("Top", "Position", "The top most character row of the window");
    RegisterProperty("Right", "Position", "The right most character column of the window");
    RegisterProperty("Bottom", "Position", "The bottom most character row of the window");
    RegisterProperty("Width", "Dimensions", "The width in characters of the window");
    RegisterProperty("Height", "Dimensions", "The height in characters of the window");
    // json loading properties
    m_PropertyMap["Window.Left"] = &m_Rect.Left;
    m_PropertyMap["Window.Top"] = &m_Rect.Top;
    m_PropertyMap["Window.Right"] = &m_Rect.Right;
    m_PropertyMap["Window.Bottom"] = &m_Rect.Bottom;
    m_File = GetFile();
}
//---------------------------------------------------------------------------
void __fastcall WindowDocument::DoSave()
{
    Push("Window");
        Write("Left", m_Rect.Left);
        Write("Top", m_Rect.Top);
        Write("Right", m_Rect.Right);
        Write("Bottom", m_Rect.Bottom);
    Pop();  // window
}
//---------------------------------------------------------------------------
int __fastcall WindowDocument::Get(int index)
{
    switch (index)
    {
        case 0: return m_Rect.Left; break;
        case 1: return m_Rect.Top; break;
        case 2: return m_Rect.Right; break;
        case 3: return m_Rect.Bottom; break;
        case 4: return m_Rect.Width(); break;
        case 5: return m_Rect.Height(); break;
    }
}
//---------------------------------------------------------------------------
void __fastcall WindowDocument::Set(const TRect& rect)
{
    m_Rect = rect;
    ::Messaging::Bus::Publish<WindowChangedEvent>(WindowChangedEvent(rect));
}
//---------------------------------------------------------------------------

