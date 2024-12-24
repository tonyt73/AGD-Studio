//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "DocumentManager.h"
#include "Window.h"
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
            m_SizeInPixels.cx = static_cast<LONG>(mc.GraphicsMode()->Width);
            m_SizeInPixels.cy = static_cast<LONG>(mc.GraphicsMode()->Height);
            m_SizeInCharacters.cx = m_SizeInPixels.cx / mc.ImageSizing[Visuals::itTile].Minimum.cx;
            m_SizeInCharacters.cy = m_SizeInPixels.cy / mc.ImageSizing[Visuals::itTile].Minimum.cy;
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

    m_SizeInPixels.cx = static_cast<LONG>(mc.GraphicsMode()->Width);
    m_SizeInPixels.cy = static_cast<LONG>(mc.GraphicsMode()->Height);
    m_SizeInCharacters.cx = m_SizeInPixels.cx / mc.ImageSizing[Visuals::itTile].Minimum.cx;
    m_SizeInCharacters.cy = m_SizeInPixels.cx / mc.ImageSizing[Visuals::itTile].Minimum.cy;

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
    switch (index) {
    case 0: return m_Rect.Left;
    case 1: return m_Rect.Top;
    case 2: return m_Rect.Right;
    case 3: return m_Rect.Bottom;
    case 4: return m_Rect.Width() + 1;
    case 5: return m_Rect.Height() + 1;
    case 6: return m_SizeInCharacters.cx;
    case 7: return m_SizeInCharacters.cy;
    case 8: return m_SizeInPixels.cx;
    case 9: return m_SizeInPixels.cy;
    }
    return 0;
}
//---------------------------------------------------------------------------
void __fastcall WindowDocument::SetRect(const TRect& rect)
{
    if (rect.Width() > 8 && rect.Height() > 4)
    {
        m_Rect = rect;
        Bus::Publish<UpdateProperties>(UpdateProperties());
        Bus::Publish<WindowChangedEvent>(WindowChangedEvent(rect));
    }
}
//---------------------------------------------------------------------------

