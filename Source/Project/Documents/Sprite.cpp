//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Sprite.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
__fastcall SpriteDocument::SpriteDocument(const String& name, const String& extra)
: ImageDocument(name)
{
    m_ImageType = Visuals::itSprite;
    m_File = GetFile();
    m_MultiFrame = true;
    m_CanModifyFrames = true;
    m_CanBeLocked = true;
    m_SubType = "Sprite";
    m_Folder = "Images\\Sprites";
    if (IsValid(name))
    {
        RegisterProperty("Name", "Details", "The name of the sprite");
        ExtractSize(extra);
        AddFrame();
    }
}
//---------------------------------------------------------------------------
__fastcall SpriteDocument::~SpriteDocument()
{
}
//---------------------------------------------------------------------------

