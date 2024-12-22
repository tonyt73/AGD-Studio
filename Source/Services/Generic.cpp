//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Generic.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Services;
//---------------------------------------------------------------------------
const String g_TokenObj = "|";
const String g_TokenSep = "^";
//---------------------------------------------------------------------------
Generic::Generic()
{
}
//---------------------------------------------------------------------------
Generic::Generic(const String& object)
: m_Object(object)
{
}
//---------------------------------------------------------------------------
void Generic::Process()
{
    if (m_Objects.size() == 0 && m_Object.Length() > 0) {
        // split the string by the object token
        auto objects = SplitString(m_Object, g_TokenObj);
        for (auto object : objects) {
            // split the objects by the separator token
            auto tokens = SplitString(object, g_TokenSep);
            if (tokens.Length == 2) {
                m_Objects[tokens[0]] = tokens[1];
            }
        }
    }
}
//---------------------------------------------------------------------------
void Generic::Add(const String& name, const String& value)
{
    m_Object += g_TokenObj + name + g_TokenSep + "string:"  + value;
}
//---------------------------------------------------------------------------
void Generic::Add(const String& name, const bool& value)
{
    // |<name>^bool:<value>
    m_Object += g_TokenObj + name + g_TokenSep + "bool:" + String(value ? "true" : "false");
}
//---------------------------------------------------------------------------
void Generic::Add(const String& name, const int& value)
{
    m_Object += g_TokenObj + name + g_TokenSep + "int:" + IntToStr(value);
}
//---------------------------------------------------------------------------
void Generic::Add(const String& name, const float& value)
{
    m_Object += g_TokenObj + name + g_TokenSep + "float:" + FloatToStrF(static_cast<System::Extended>(value), ffFixed, 6, 2);
}
//---------------------------------------------------------------------------
bool Generic::Get(const String& name, String& value)
{
    Process();
    if (m_Objects.count(name) == 1) {
        // parse string to string
        auto def = m_Objects[name];
        auto tokens = SplitString(def, ":");
        value = tokens[1];
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool Generic::Get(const String& name, bool& value)
{
    Process();
    if (m_Objects.count(name) == 1) {
        // parse string to bool
        auto def = m_Objects[name];
        auto tokens = SplitString(def, ":");
        value = tokens[1] == "true";
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool Generic::Get(const String& name, int& value)
{
    Process();
    if (m_Objects.count(name) == 1) {
        // parse string to int
        auto def = m_Objects[name];
        auto tokens = SplitString(def, ":");
        value = StrToInt(tokens[1]);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool Generic::Get(const String& name, float& value)
{
    Process();
    if (m_Objects.count(name) == 1) {
        // parse string to float
        auto def = m_Objects[name];
        auto tokens = SplitString(def, ":");
        value = static_cast<float>(StrToFloat(tokens[1]));
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------

