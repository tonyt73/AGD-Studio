//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ImageDocuments.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ImageDocument::ImageDocument(const String& name)
: Document(name)
, m_MultiFrame(false)
, m_Width(16)
, m_Height(16)
{
    m_Type = "Image";
    m_SubType = "Single";
    m_Folder = "Images\\Images";
    RegisterProperty("Name", "Details", "The name of the image");
    RegisterProperty("Width", "Dimensions", "The width in pixels of the image");
    RegisterProperty("Height", "Dimensions", "The height in pixels of the image");
    RegisterProperty("Frames", "Dimensions", "The number of frames in the image");
    // json loading properties
    m_PropertyMap[".Image.Width"] = &m_Width;
    m_PropertyMap[".Image.Height"] = &m_Height;
    m_File = GetFile();
    AddFrame();
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::Save()
{
    Open(m_File);
    Push("Image");
        Write("Width", m_Width);
        Write("Height", m_Height);
        // TODO: All the other image details, palette, pixels, etc
    Pop();  // image
    Close();
}
//---------------------------------------------------------------------------
int __fastcall ImageDocument::CountFrames() const
{
    return m_Frames.size();
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::SetFrames(int frames)
{
    if (frames > 1 && frames != m_Frames.size())
    {
        while (frames != m_Frames.size())
        {
            frames > m_Frames.size() ? AddFrame() : DeleteFrame(m_Frames.size() - 1);
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall ImageDocument::AddFrame()
{
    if (m_Frames.size() == 0 || m_MultiFrame)
    {
        m_Frames.push_back("");
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ImageDocument::DeleteFrame(int index)
{
    if (m_MultiFrame && 0 < index && index < m_Frames.size())
    {
        // can't only delete new frames; can't delete the first frame
        m_Frames.erase(m_Frames.begin() + index);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
__fastcall SpriteDocument::SpriteDocument(const String& name)
: ImageDocument(name)
{
    m_MultiFrame = true;
    m_SubType = "Sprite";
    m_Folder = "Images\\Sprites";
    RegisterProperty("Name", "Details", "The name of the sprite");
    m_File = GetFile();
}
//---------------------------------------------------------------------------
__fastcall ObjectDocument::ObjectDocument(const String& name)
: ImageDocument(name)
{
    m_SubType = "Object";
    m_Folder = "Images\\Objects";
    RegisterProperty("Name", "Details", "The name of the object");
    m_File = GetFile();
}
//---------------------------------------------------------------------------
__fastcall TileDocument::TileDocument(const String& name, const String& extra)
: ImageDocument(name)
{
    m_File = GetFile();
    m_SubType = "Tile";
    m_Folder = "Images\\Tiles";
    RegisterProperty("Name", "Details", "The name of the tile");
    if (extra != "")
    {
        // extract the size from the string
        auto pos = extra.Pos("x");
        if (pos > 0)
        {
            m_Width = StrToInt(extra.SubString(1, pos - 1));
            m_Height = StrToInt(extra.SubString(pos + 1, extra.Length()));
        }
    }
}
//---------------------------------------------------------------------------
