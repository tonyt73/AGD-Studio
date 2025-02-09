﻿//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include <System.hpp>
#include "CharacterSet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
__fastcall CharacterSetDocument::CharacterSetDocument(const String& name, const String& extra)
: ImageDocument(name)
{
    m_SaveRefId = false;
    m_ImageType = Visuals::itCharacterSet;
    m_MultiFrame = true;
    m_File = GetFile();
    m_SubType = "Character Set";
    m_Folder = "Images\\Character Set";
    if (IsValid(name)) {
        RegisterProperty("Name", "Details", "The name of the character set");
        ExtractSize(extra);
        m_CanModifyFrames = true; // yes to get the default frames in
        for (auto i = 0; i < 96; i++) {
            switch (i) {
            case 6:
                AddFrame(-1, "&&");
                break;
            case 95:
                AddFrame(-1, "©");
                break;
            default:
                AddFrame(-1, StringOfChar(static_cast<wchar_t>(32 + i), 1));
                break;
            }
        }
    }
    m_CanModifyFrames = false; // no for the editor
}
//---------------------------------------------------------------------------
__fastcall CharacterSetDocument::~CharacterSetDocument()
{
}
//---------------------------------------------------------------------------
