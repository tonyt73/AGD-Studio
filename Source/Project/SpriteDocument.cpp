//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "SpriteDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SpriteDocument::SpriteDocument(const String& name, const String& extra)
: ImageDocument(name)
{
    m_ImageType = itSprite;
    m_File = GetFile();
    m_MultiFrame = true;
    m_CanModifyFrames = true;
    m_CanBeLocked = true;
    m_SubType = "Sprite";
    m_Folder = "Images\\Sprites";
    if (name != Unnamed) {
        RegisterProperty("Name", "Details", "The name of the sprite");
        ExtractSize(extra);
        AddFrame();
    }
}
//---------------------------------------------------------------------------

