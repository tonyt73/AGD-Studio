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
{
    m_Type = "Image";
    m_SubType = "Single";
    m_Folder = "Assets\\Images";
    RegisterProperty("Name", "Object", "The name of the image");
    RegisterProperty("Width", "Dimensions", "The width in pixels of the image");
    RegisterProperty("Height", "Dimensions", "The height in pixels of the image");
    // json loading properties
    m_PropertyMap[".Image.Width"] = &m_Width;
    m_PropertyMap[".Image.Height"] = &m_Height;
}
//---------------------------------------------------------------------------
void __fastcall ImageDocument::Save()
{
    // Documents/{project name}
    auto file = System::File::Combine(System::Path::Projects, System::Path::ProjectName);
    // Documents/{project name}/Images/{type}
    file = System::File::Combine(file, m_Folder);
    // Documents/{project name}/Images/{type}/{image name}
    file = System::File::Combine(file, m_Name);
    Open(file);
    Push("Image");
        Write("Width", m_Width);
        Write("Height", m_Height);
        // TODO: All the other image details, palette, pixels, etc
    Pop();  // image
    Close();
}
//---------------------------------------------------------------------------
__fastcall ImageDocumentSet::ImageDocumentSet()
: DocumentSet()
{
    m_Folder = "Assets\\Images";
    m_Type = "Image";
    m_SubType = "Set";
    RegisterProperty("Name", "Object", "The name of the image set");
    RegisterProperty("Width", "Dimensions", "The width in pixels of the images in the set");
    RegisterProperty("Height", "Dimensions", "The height in pixels of the images in the set");
}
//---------------------------------------------------------------------------
__fastcall SpriteDocument::SpriteDocument()
: ImageDocumentSet()
{
    m_SubType = "Sprite";
    m_Folder = "Assets\\Sprites";
    RegisterProperty("Name", "Object", "The name of the sprite");
//    RegisterProperty("Width", "Dimensions", "The width in pixels of the sprite");
//    RegisterProperty("Height", "Dimensions", "The height in pixels of the sprite");
}
//---------------------------------------------------------------------------
__fastcall ObjectDocument::ObjectDocument()
: ImageDocument()
{
    m_SubType = "Object";
    m_Folder = "Assets\\Objects";
    RegisterProperty("Name", "Object", "The name of the object");
//    RegisterProperty("Width", "Dimensions", "The width in pixels of the object");
//    RegisterProperty("Height", "Dimensions", "The height in pixels of the object");
}
//---------------------------------------------------------------------------
__fastcall TileDocument::TileDocument()
: ImageDocument()
{
    m_SubType = "Tile";
    m_Folder = "Assets\\Tiles";
    RegisterProperty("Name", "Object", "The name of the tile");
}
//---------------------------------------------------------------------------
__fastcall TileSetDocument::TileSetDocument()
: ImageDocumentSet()
{
    m_SubType = "TileSet";
    m_Folder = "Assets\\Tile Sets";
    RegisterProperty("Name", "Object", "The name of the tile set");
    RegisterProperty("TileWidth", "Dimensions", "The width in pixels of the tiles in the set");
    RegisterProperty("TileHeight", "Dimensions", "The height in pixels of the tiles in the set");
    RegisterProperty("IsTransparent", "Visual", "Indicates if the images are transparent or not");
    RegisterProperty("TransparentColor", "Visual", "The color of transparent pixels");
}
//---------------------------------------------------------------------------
