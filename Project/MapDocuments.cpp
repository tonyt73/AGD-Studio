//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "MapDocuments.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TiledScreenDocument::TiledScreenDocument()
: Document()
{
    m_Type = "Screen";
    m_SubType = "Tiled";
    m_Folder = "Assets\\Screens";
    RegisterProperty("Name", "Details", "The name of the screen");
}
//---------------------------------------------------------------------------
//__fastcall TiledScreenDocumentSet::TiledScreenDocumentSet()
//: DocumentSet()
//{
//    m_Type = "Screens";
//    m_SubType = "Tiled";
//    m_Folder = "Assets\\Screens";
//    RegisterProperty("Name", "Details", "The name of the map");
//    RegisterProperty("Across", "Dimensions", "The width in screens accross of the map");
//    RegisterProperty("Down", "Dimensions", "The height in Screens down of the map");
//    RegisterProperty("WindowWidth", "Dimensions", "The width in character blocks of the map window");
//    RegisterProperty("WindowHeight", "Dimensions", "The height in character blocks of the map window");
//    RegisterProperty("BackgroundColor", "Visual", "The color of the background when no tile is present");
//}
//---------------------------------------------------------------------------
__fastcall TiledMapDocument::TiledMapDocument()
: Document()
{
    m_Type = "Map";
    m_SubType = "Tiled";
    m_Folder = "Assets\\Maps";
    RegisterProperty("Name", "Details", "The name of the map");
    RegisterProperty("Across", "Dimensions", "The number in screens accross for the map");
    RegisterProperty("Down", "Dimensions", "The number in Screens down for the map");
    RegisterProperty("WindowWidth", "Dimensions", "The width in character blocks for the map window");
    RegisterProperty("WindowHeight", "Dimensions", "The height in character blocks for the map window");
    RegisterProperty("BackgroundColor", "Visual", "The color of the background when no tile is present");
}
//---------------------------------------------------------------------------

