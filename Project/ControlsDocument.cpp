//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Project/ControlsDocument.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ControlsDocument::ControlsDocument(const String& name)
: Document(name)
{
    m_Type = "Controls";
    m_SubType = "List";
    m_Extension = "json";
    m_Folder = "Game\\Configuration";
    RegisterProperty("Up", "Directional", "");
    RegisterProperty("Down", "Directional", "");
    RegisterProperty("Left", "Directional", "");
    RegisterProperty("Right", "Directional", "");
    RegisterProperty("Fire1", "Fire", "");
    RegisterProperty("Fire2", "Fire", "");
    RegisterProperty("Fire3", "Fire", "");
    RegisterProperty("Option1", "Option", "");
    RegisterProperty("Option2", "Option", "");
    RegisterProperty("Option3", "Option", "");
    RegisterProperty("Option4", "Option", "");
    // json loading properties
    m_PropertyMap["Keys[]"] = &m_Key;
    m_File = GetFile();
}
//---------------------------------------------------------------------------
void __fastcall ControlsDocument::DoSave()
{
    ArrayStart("Keys");
        for (auto key : m_Keys)
        {
            Write(key);
        }
    ArrayEnd();  // Keys
}
//---------------------------------------------------------------------------
String __fastcall ControlsDocument::Get(int index)
{
    auto key = m_Keys[index];
    if (32 < key && key <= 127)
    {
        return UnicodeString::StringOfChar(key, 1);
    }
    if (key == 32)
    {
        return "Space";
    }
    if (key == 13)
    {
        return "Enter";
    }
    // TODO: Add a machine key codes to key names files
    if (key == '~')
    {
        return "Left Shift";
    }
    if (key == '.' || key == ',')
    {
        return "Symbol Shift";
    }
    return IntToStr(key);
}
//---------------------------------------------------------------------------
void __fastcall ControlsDocument::OnEndObject(const String& object)
{
    if (object == "Keys[]")
    {
        m_Keys.push_back(m_Key);
    }
}
//---------------------------------------------------------------------------
void __fastcall ControlsDocument::OnLoading()
{
    m_Keys.clear();
}
//---------------------------------------------------------------------------

