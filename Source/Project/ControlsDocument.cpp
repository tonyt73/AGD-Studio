//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "ControlsDocument.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
ControlsDocument::ControlsDocument(const String& name)
: Document(name)
{
    m_Type = "Controls";
    m_SubType = "List";
    m_Extension = "json";
    m_Folder = "Game\\Configuration";
    if (IsValid(name))
    {
        RegisterProperty("Up", "Directional", "The key for Player Up");
        RegisterProperty("Down", "Directional", "The key for Player Down");
        RegisterProperty("Left", "Directional", "The key for Player Left");
        RegisterProperty("Right", "Directional", "The key for Player Right");
        RegisterProperty("Fire1", "Fire", "The key for Fire 1");
        RegisterProperty("Fire2", "Fire", "The key for Fire 2");
        RegisterProperty("Fire3", "Fire", "The key for Fire 3");
        RegisterProperty("Option1", "Option", "The key for Option 1");
        RegisterProperty("Option2", "Option", "The key for Option 2");
        RegisterProperty("Option3", "Option", "The key for Option 3");
        RegisterProperty("Option4", "Option", "The key for Option 4");
        // json loading properties
        m_PropertyMap["Keys[]"] = &m_Key;
        m_File = GetFile();
        DefaultKeys();
    }
}
//---------------------------------------------------------------------------
void ControlsDocument::DoSave()
{
    ArrayStart("Keys");
        for (auto key : m_Keys)
        {
            Write(key);
        }
    ArrayEnd();  // Keys
}
//---------------------------------------------------------------------------
String ControlsDocument::Get(int index)
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
void ControlsDocument::OnEndObject(const String& object)
{
    if (object == "Keys[]")
    {
        m_Keys.push_back(m_Key);
    }
}
//---------------------------------------------------------------------------
void ControlsDocument::OnLoading()
{
    m_Keys.clear();
}
//---------------------------------------------------------------------------
void ControlsDocument::OnLoaded()
{
    DefaultKeys();
}
//---------------------------------------------------------------------------
unsigned char ControlsDocument::GetAsciiCode(eAgdKey key)
{
    if (0 <= key && key < m_Keys.size())
    {
        return m_Keys[key];
    }
    return 0;
}
//---------------------------------------------------------------------------
void ControlsDocument::SetAsciiCode(eAgdKey key, unsigned char keyCode)
{
    if (0 <= key && key < m_Keys.size())
    {
        m_Keys[key] = keyCode;
    }
}
//---------------------------------------------------------------------------
void ControlsDocument::DefaultKeys()
{
    while (m_Keys.size() < 11)
    {
        m_Keys.push_back(0);
    }
}
//---------------------------------------------------------------------------

