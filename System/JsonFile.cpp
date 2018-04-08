//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include <stack>
#include "JsonFile.h"
#include "System/make_unique.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace std;
namespace System
{
//---------------------------------------------------------------------------
__fastcall JsonFile::JsonFile()
: TPersistent()
, m_StringWriter(nullptr)
, m_JsonWriter(nullptr)
{
}
//---------------------------------------------------------------------------
__fastcall JsonFile::~JsonFile()
{
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Open(const String& file)
{
    m_File = file;
    m_StringWriter = new TStringWriter();
    m_JsonWriter = new TJsonTextWriter(m_StringWriter);
    m_JsonWriter->Formatting = TJsonFormatting::Indented;
    m_JsonWriter->WriteStartObject();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Close()
{
    if (m_StringWriter != nullptr && m_JsonWriter != nullptr)
    {
        m_JsonWriter->WriteEndObject();
        File::File::WriteText(m_File, m_StringWriter->ToString());
        delete m_JsonWriter;
        m_JsonWriter = nullptr;
        delete m_StringWriter;
        m_StringWriter = nullptr;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::StartObject() const
{
    m_JsonWriter->WriteStartObject();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::EndObject() const
{
    m_JsonWriter->WriteEndObject();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Push(const String& section) const
{
    m_JsonWriter->WritePropertyName(section);
    m_JsonWriter->WriteStartObject();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Pop() const
{
    m_JsonWriter->WriteEndObject();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::ArrayStart(const String& property) const
{
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteStartArray();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::ArrayEnd() const
{
    m_JsonWriter->WriteEndArray();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& value) const
{
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const int& value) const
{
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const String& value) const
{
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const int& value) const
{
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const unsigned int& value) const
{
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const float& value) const
{
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const bool& value) const
{
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const String& value)
{
    auto size = m_PropertyMap.size();
    if (m_PropertyMap.count(property) != 0)
    {
        ((*(String*)m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const int& value)
{
    if (m_PropertyMap.count(property) != 0)
    {
        ((*(int*)m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const unsigned int& value)
{
    if (m_PropertyMap.count(property) != 0)
    {
        ((*(unsigned int*)m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const float& value)
{
    if (m_PropertyMap.count(property) != 0)
    {
        ((*(float*)m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const bool& value)
{
    if (m_PropertyMap.count(property) != 0)
    {
        ((*(bool*)m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Load(const String& file)
{
    if (File::File::Exists(file))
    {
        auto json = File::File::ReadText(file);
        auto sr = make_unique<TStringReader>(json);
        auto jr = make_unique<TJsonTextReader>(sr.get());
        String property;                    // the tree dot.path or property reference eg: my.things.value
        auto depth = 0;
        auto inArray = false;
        // depth values for object, array and property
        // these help to balance the tree path
        std::stack<int> objectDepth;    // depth at which an object starts
        std::stack<int> arrayDepth;     // depth at which an array starts
        std::stack<int> propertyDepth;  // depth at which a property starts
        while (jr->Read())
        {
            switch (jr->TokenType)
            {
                case TJsonToken::StartObject:
                    objectDepth.push(depth++);
                    OnStartObject(property);
                    property += ".{}";
                    break;
                case TJsonToken::EndObject:
                {
                    OnEndObject(property);
                    auto pops = (depth - objectDepth.top()) + (inArray ? 0 : 1);
                    objectDepth.pop();
                    for (auto i = 0; i < pops; i++)
                    {
                        property = property.Delete(property.LastDelimiter("."), property.Length());
                        depth--;
                    }
                    break;
                }
                case TJsonToken::StartArray:
                    property += ".[]";
                    arrayDepth.push(++depth);
                    inArray = true;
                    break;
                case TJsonToken::EndArray:
                    property = property.Delete(property.LastDelimiter("."), property.Length());
                    if (depth == arrayDepth.top())
                    {
                        depth--;
                        // remove the last .name
                        property = property.Delete(property.LastDelimiter("."), property.Length());
                    }
                    inArray = false;
                    arrayDepth.pop();
                    break;
                case TJsonToken::PropertyName:
                    propertyDepth.push(++depth);
                    property += "." + jr->Value.AsString();
                    break;
                case TJsonToken::String:
                {
                    Set(property, jr->Value.AsString());
                    if (inArray) OnEndObject(property);
                    // are we matched to a property?
                    if (depth == propertyDepth.top())
                    {
                        // yep, so back down
                        depth--;
                        propertyDepth.pop();
                        // remove the last .name
                        property = property.Delete(property.LastDelimiter("."), property.Length());
                    }
                    break;
                }
                case TJsonToken::Integer:
                    Set(property, jr->Value.AsInteger());
                    if (inArray) OnEndObject(property);
                    if (depth == propertyDepth.top())
                    {
                        depth--;
                        propertyDepth.pop();
                        // remove the last .name
                        property = property.Delete(property.LastDelimiter("."), property.Length());
                    }
                    break;
                case TJsonToken::Float:
                    {
                        float value = jr->Value.AsExtended();
                        Set(property, value);
                        if (inArray) OnEndObject(property);
                        if (depth == propertyDepth.top())
                        {
                            depth--;
                            propertyDepth.pop();
                            // remove the last .name
                            property = property.Delete(property.LastDelimiter("."), property.Length());
                        }
                    }
                    break;
                case TJsonToken::Boolean:
                    Set(property, jr->Value.AsBoolean());
                    if (inArray) OnEndObject(property);
                    if (depth == propertyDepth.top())
                    {
                        depth--;
                        propertyDepth.pop();
                        // remove the last .name
                        property = property.Delete(property.LastDelimiter("."), property.Length());
                    }
                    break;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::OnStartObject(const String& object)
{
    // do nothing; should be overridden
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::OnEndObject(const String& object)
{
    // do nothing; should be overridden
}
//---------------------------------------------------------------------------
} // namespace File
//---------------------------------------------------------------------------

