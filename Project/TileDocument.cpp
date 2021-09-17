//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "TileDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TileDocument::TileDocument(const String& name, const String& extra)
    : ImageDocument(name)
{
    m_ImageType = itTile;
    m_File = GetFile();
    m_SubType = "Tile";
    m_Folder = "Images\\Tiles";
    if (name != Unnamed) {
        RegisterProperty("Name", "Details", "The name of the tile");
        ExtractSize(extra);
        AddFrame();
        AddLayer("blocktype", "0");
    }
}
//---------------------------------------------------------------------------

