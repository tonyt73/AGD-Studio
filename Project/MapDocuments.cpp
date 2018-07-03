//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "MapDocuments.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TiledMapDocument::TiledMapDocument(const String& name)
: Document(name)
, m_Across(11)
, m_Down(5)
, m_StartLocationX(5)
, m_StartLocationY(2)
, m_Width(32)
, m_Height(24)
, m_BackgroundColor(clBlack)
{
    m_Type = "Map";
    m_SubType = "Tiled";
    m_Folder = "Game\\Map";
    RegisterProperty("RoomsAcross", "Dimensions", "The number in rooms accross for the map");
    RegisterProperty("RoomsDown", "Dimensions", "The number in rooms down for the map");
    RegisterProperty("RoomWidth", "Dimensions", "The width in character blocks for a map room");
    RegisterProperty("RoomHeight", "Dimensions", "The height in character blocks for a map room");
    RegisterProperty("StartLocationX", "Start Room", "The x position of the start room into the map");
    RegisterProperty("StartLocationY", "Start Room", "The y position of the start room into the map");
    RegisterProperty("BackgroundColor", "Visual", "The color of the background when no tile is present");
    // json loading properties
    m_PropertyMap["Map.RoomsAcross"] = &m_Across;
    m_PropertyMap["Map.RoomsDown"] = &m_Down;
    m_PropertyMap["Map.RoomWidth"] = &m_Width;
    m_PropertyMap["Map.RoomHeight"] = &m_Height;
    m_PropertyMap["Map.StartLocationX"] = &StartLocationX;
    m_PropertyMap["Map.StartLocationY"] = &StartLocationY;
    m_PropertyMap["Map.Entities[].X"] = &m_EntityLoader.x;
    m_PropertyMap["Map.Entities[].Y"] = &m_EntityLoader.y;
    m_PropertyMap["Map.Entities[].Name"] = &m_EntityLoader.name;
    m_PropertyMap["Map.Entities[].Type"] = &m_EntityLoader.type;
    m_PropertyMap["Map.Entities[].SubType"] = &m_EntityLoader.subType;
    m_File = GetFile();
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::Save()
{
    Open(m_File);
    Push("Map");
        Write("RoomsAcross", m_Across);
        Write("RoomsDown", m_Down);
        Write("RoomWidth", m_Width);
        Write("RoomHeight", m_Height);
        Write("StartLocationX", m_StartLocationX);
        Write("StartLocationY", m_StartLocationY);
        ArrayStart("Entities");
        for (const auto& entity : m_Entities)
        {
            StartObject();
                Write("X", entity.x);
                Write("Y", entity.y);
                Write("Name", entity.doc ? entity.doc->Name : entity.name);
                Write("Type", entity.doc ? entity.doc->Type : entity.type);
                Write("SubType", entity.doc ? entity.doc->SubType : entity.subType);
            EndObject();
        }
        ArrayEnd(); // entities
    Pop();  // map
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TiledMapDocument::OnEndObject(const String& object)
{
    if (object == "Map.Entities[]")
    {
        // TODO: Find document
        //       Clear the strings name, type, subtype
        m_Entities.push_back(m_EntityLoader);
    }
}
//---------------------------------------------------------------------------

