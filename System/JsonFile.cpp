//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include <stack>
#include "JsonFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
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
String __fastcall JsonFile::ProcessPath(const String& path) const
{
    String newPath = "";
    auto skip = false;
    for (auto i = 1; i <= path.Length(); i++)
    {
        if (path[i] == '[')
        {
            skip = true;
            newPath += path[i];
        }
        else if (skip && path[i] == ']')
        {
            skip = false;
            newPath += path[i];
        }
        else if (!skip)
        {
            newPath += path[i];
        }
    }
    return newPath;
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Load(const String& file)
{
    if (File::File::Exists(file))
    {
        auto json = File::File::ReadText(file);
        auto sr = std::make_unique<TStringReader>(json);
        auto jr = std::make_unique<TJsonTextReader>(sr.get());
        auto inArray = false;
        while (jr->Read())
        {
            auto path = ProcessPath(jr->Path);
            switch (jr->TokenType)
            {
                case TJsonToken::StartObject:
                    OnStartObject(path);
                    break;
                case TJsonToken::EndObject:
                    OnEndObject(path);
                    break;
                case TJsonToken::StartArray:
                    inArray = true;
                    break;
                case TJsonToken::EndArray:
                    inArray = false;
                    break;
                case TJsonToken::PropertyName:
                    break;
                case TJsonToken::String:
                    Set(path, jr->Value.AsString());
                    if (inArray) OnEndObject(path);
                    break;
                case TJsonToken::Integer:
                    Set(path, jr->Value.AsInteger());
                    if (inArray) OnEndObject(path);
                    break;
                case TJsonToken::Float:
                    Set(path, (float)jr->Value.AsExtended());
                    if (inArray) OnEndObject(path);
                    break;
                case TJsonToken::Boolean:
                    Set(path, jr->Value.AsBoolean());
                    if (inArray) OnEndObject(path);
                    break;
            }
        }
        OnLoaded();
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
void __fastcall JsonFile::OnLoaded()
{
    // do nothing; should be overridden
}
//---------------------------------------------------------------------------
} // namespace File
//---------------------------------------------------------------------------

