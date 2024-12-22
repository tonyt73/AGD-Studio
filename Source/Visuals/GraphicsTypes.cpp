//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "GraphicsTypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
String __fastcall Visuals::ImageTypeName(ImageTypes type)
{
    switch (type) {
        case itCharacterSet:
            return "CharacterSet";
        case itObject:
            return "Object";
        case itSprite:
            return "Sprite";
        case itTile:
            return "Tile";
        default:
            return "Invalid";
    }
}
//---------------------------------------------------------------------------
String __fastcall Visuals::BufferTypeName(BufferType type)
{
    switch (type) {
        case btBitmap:
            return "btBitmap";
        case btAttribute:
            return "btAttribute";
        case btULAplus:
            return "btULAplus";
        case btCharacterMap:
            return "btCharacterMap";
        default:
            return "btInvalid";
    }
}
//---------------------------------------------------------------------------
Visuals::BufferType __fastcall Visuals::BufferTypeByName(String name)
{
    if (name.LowerCase() == "btbitmap"       ) return btBitmap;
    if (name.LowerCase() == "btattribute"    ) return btAttribute;
    if (name.LowerCase() == "btulaplus"      ) return btULAplus;
    if (name.LowerCase() == "btcharactermmap") return btCharacterMap;
    return btInvalid;
}
//---------------------------------------------------------------------------

