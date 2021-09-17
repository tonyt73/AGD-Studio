//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "CharacterSetDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CharacterSetDocument::CharacterSetDocument(const String& name, const String& extra)
    : ImageDocument(name)
{
    m_SaveRefId = false;
    m_ImageType = itCharacterSet;
    m_MultiFrame = true;
    m_File = GetFile();
    m_SubType = "Character Set";
    m_Folder = "Images\\Character Set";
    if (name != Unnamed) {
        RegisterProperty("Name", "Details", "The name of the character set");
        ExtractSize(extra);
        m_CanModifyFrames = true; // yes to get the default frames in
        for (auto i = 0; i < 96; i++) {
            switch (i) {
            case 0:
                AddFrame(-1, "Space");
                break;
            case 95:
                AddFrame(-1, "©");
                break;
            case 92:
                AddFrame(-1, "Vert.Line");
                break;
            default:
                AddFrame(-1, UnicodeString().StringOfChar(32 + i, 1));
                break;
            }
        }
    }
    m_CanModifyFrames = false; // no for the editor
}
//---------------------------------------------------------------------------
