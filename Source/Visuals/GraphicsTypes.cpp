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

