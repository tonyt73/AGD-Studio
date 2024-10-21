//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Project/DocumentManager.h"
#include "Project/WindowDocument.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
__fastcall WindowDocument::WindowDocument(const String& name)
: Document(name)
{
    m_Type = "Window";
    m_SubType = "Definition";
    m_Extension = "json";
    m_Folder = "Game\\Configuration";
    if (IsValid(name))
    {
        RegisterProperty("Left", "Position", "The left most character column of the window");
        RegisterProperty("Top", "Position", "The top most character row of the window");
        RegisterProperty("Right", "Position", "The right most character column of the window");
        RegisterProperty("Bottom", "Position", "The bottom most character row of the window");
        RegisterProperty("Width", "Dimensions", "The width in characters of the window");
        RegisterProperty("Height", "Dimensions", "The height in characters of the window");
        RegisterProperty("Columns", "Screen Resolution", "The width in characters of the graphics mode");
        RegisterProperty("Rows", "Screen Resolution", "The height in characters of the graphics mode");
        RegisterProperty("PixelsWidth", "Screen Resolution", "The width in pixels of the screens graphics mode");
        RegisterProperty("PixelsHeight", "Screen Resolution", "The height in pixels of the screens graphics mode");
        // json loading properties
        m_PropertyMap["Window.Left"] = &m_Rect.Left;
        m_PropertyMap["Window.Top"] = &m_Rect.Top;
        m_PropertyMap["Window.Right"] = &m_Rect.Right;
        m_PropertyMap["Window.Bottom"] = &m_Rect.Bottom;

        m_File = GetFile();

        if (theDocumentManager.ProjectConfig() != nullptr)
        {
            const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
            m_SizeInCharacters.cx = mc.GraphicsMode()->Width  / mc.ImageSizing[Visuals::itTile].Minimum.cx;
            m_SizeInCharacters.cy = mc.GraphicsMode()->Height / mc.ImageSizing[Visuals::itTile].Minimum.cy;
            m_SizeInPixels.cx = mc.GraphicsMode()->Width;
            m_SizeInPixels.cy = mc.GraphicsMode()->Height;
            m_Rect.Left = 0;
            m_Rect.Top = 0;
            m_Rect.Right = m_SizeInCharacters.cx - 1;
            m_Rect.Bottom = m_SizeInCharacters.cy - 1;
        }
    }
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
void __fastcall WindowDocument::OnLoaded()
{
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();

    m_SizeInCharacters.cx = mc.GraphicsMode()->Width  / mc.ImageSizing[Visuals::itTile].Minimum.cx;
    m_SizeInCharacters.cy = mc.GraphicsMode()->Height / mc.ImageSizing[Visuals::itTile].Minimum.cy;
    m_SizeInPixels.cx = mc.GraphicsMode()->Width;
    m_SizeInPixels.cy = mc.GraphicsMode()->Height;

    if (m_Rect.Width() <= 1)
    {
        m_Rect.Left = 0;
        m_Rect.Right = m_SizeInCharacters.cx - 1;
    }
    if (m_Rect.Height() <= 1)
    {
        m_Rect.Top = 0;
        m_Rect.Bottom = m_SizeInCharacters.cy - 1;
    }
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
        case 4: return m_Rect.Width() + 1; break;
        case 5: return m_Rect.Height() + 1; break;
        case 6: return m_SizeInCharacters.cx; break;
        case 7: return m_SizeInCharacters.cy; break;
        case 8: return m_SizeInPixels.cx; break;
        case 9: return m_SizeInPixels.cy; break;
    }
}
//---------------------------------------------------------------------------
void __fastcall WindowDocument::Set(const TRect& rect)
{
    if (rect.Width() > 8 && rect.Height() > 4)
    {
        m_Rect = rect;
        ::Messaging::Bus::Publish<::Messaging::UpdateProperties>(::Messaging::UpdateProperties());
        ::Messaging::Bus::Publish<::Messaging::WindowChangedEvent>(::Messaging::WindowChangedEvent(rect));
    }
}
//---------------------------------------------------------------------------

