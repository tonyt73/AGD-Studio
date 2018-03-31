//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ImageDocuments.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ImageDocument::ImageDocument()
: Document()
, m_MultiFrame(false)
{
    m_Type = "Image";
    m_SubType = "Single";
    m_Folder = "Assets\\Images";
    RegisterProperty("Name", "Details", "The name of the image");
    RegisterProperty("Width", "Dimensions", "The width in pixels of the image");
    RegisterProperty("Height", "Dimensions", "The height in pixels of the image");
    RegisterProperty("Frames", "Dimensions", "The number of frames in the image");
    // json loading properties
    m_PropertyMap[".Image.Width"] = &m_Width;
    m_PropertyMap[".Image.Height"] = &m_Height;

    // TODO: Insert the first frame
}
//---------------------------------------------------------------------------
int __fastcall ImageDocument::CountFrames() const
{
    return m_Frames.size();
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
bool __fastcall ImageDocument::AddFrame()
{
    if (m_MultiFrame)
    {
        // TODO: Add a new frame
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall ImageDocument::DeleteFrame(int index)
{
    if (m_MultiFrame && index)
    {
        // can't only delete new frames; can't delete the first frame
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
__fastcall SpriteDocument::SpriteDocument()
: ImageDocument()
{
    m_MultiFrame = true;
    m_SubType = "Sprite";
    m_Folder = "Assets\\Sprites";
    RegisterProperty("Name", "Details", "The name of the sprite");
//    RegisterProperty("Width", "Dimensions", "The width in pixels of the sprite");
//    RegisterProperty("Height", "Dimensions", "The height in pixels of the sprite");
}
//---------------------------------------------------------------------------
__fastcall ObjectDocument::ObjectDocument()
: ImageDocument()
{
    m_SubType = "Object";
    m_Folder = "Assets\\Objects";
    RegisterProperty("Name", "Details", "The name of the object");
//    RegisterProperty("Width", "Dimensions", "The width in pixels of the object");
//    RegisterProperty("Height", "Dimensions", "The height in pixels of the object");
}
//---------------------------------------------------------------------------
__fastcall TileDocument::TileDocument()
: ImageDocument()
{
    m_SubType = "Tile";
    m_Folder = "Assets\\Tiles";
    RegisterProperty("Name", "Details", "The name of the tile");
}
//---------------------------------------------------------------------------
