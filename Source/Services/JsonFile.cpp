//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "JsonFile.h"
#include "File.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma clang diagnostic ignored "-Wswitch"
//---------------------------------------------------------------------------
using namespace Services;
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
    if (m_StringWriter != nullptr && m_JsonWriter != nullptr) {
        // finish the last section (default start object)
        m_JsonWriter->WriteEndObject();
        // also write the latest version of the file
        Services::File::WriteText(m_File, m_StringWriter->ToString());
        delete m_JsonWriter;
        m_JsonWriter = nullptr;
        delete m_StringWriter;
        m_StringWriter = nullptr;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::StartObject() const
{
    // start an unamed object
    // { ....
    m_JsonWriter->WriteStartObject();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::EndObject() const
{
    // end the unamed object
    // .. }
    m_JsonWriter->WriteEndObject();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Push(const String& section) const
{
    // create a named section
    // "<section>": { ...
    m_JsonWriter->WritePropertyName(section);
    m_JsonWriter->WriteStartObject();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Pop() const
{
    // finish the named section
    // .. }
    m_JsonWriter->WriteEndObject();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::ArrayStart(const String& property) const
{
    // start an array
    // "<array name>": [ ...
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteStartArray();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::ArrayEnd() const
{
    // finish the array
    // .. ]
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
void __fastcall JsonFile::Write(const long& value) const
{
    m_JsonWriter->WriteValue(static_cast<int>(value));
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const String& value, bool skipEmpty) const
{
    if (!skipEmpty || (skipEmpty && value.Trim() != "")) {
        m_JsonWriter->WritePropertyName(property);
        m_JsonWriter->WriteValue(value);
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const int& value) const
{
    // write an integer value
    // "<property>": <integer value>
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const unsigned int& value) const
{
    // write an unsigned int value
    // "<property>": <unsigned int value>
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const long& value) const
{
    // write a long int value
    // "<property>": <long value>
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteValue(static_cast<int>(value));
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const float& value) const
{
    // write a floating point value
    // "<property>": <float value>
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Write(const String& property, const bool& value) const
{
    // write a boolean value
    // "<property>": <true/false>
    m_JsonWriter->WritePropertyName(property);
    m_JsonWriter->WriteValue(value);
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const String& value)
{
    if (m_PropertyMap.count(property) != 0) {
        *(static_cast<String*>(m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const int& value)
{
    if (m_PropertyMap.count(property) != 0) {
        *(static_cast<int*>(m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const unsigned int& value)
{
    if (m_PropertyMap.count(property) != 0) {
        *(static_cast<unsigned int*>(m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const long& value)
{
    if (m_PropertyMap.count(property) != 0) {
        *(static_cast<long*>(m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const float& value)
{
    if (m_PropertyMap.count(property) != 0) {
        *(static_cast<float*>(m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Set(const String& property, const bool& value)
{
    if (m_PropertyMap.count(property) != 0) {
        *(static_cast<bool*>(m_PropertyMap[property])) = value;
    }
}
//---------------------------------------------------------------------------
String __fastcall JsonFile::ProcessPath(const String& path) const
{
    String newPath = "";
    auto skip = false;
    for (auto i = 1; i <= path.Length(); i++) {
        if (path[i] == '[') {
            skip = true;
            newPath += path[i];
        } else if (skip && path[i] == ']') {
            skip = false;
            newPath += path[i];
        } else if (!skip) {
            newPath += path[i];
        }
    }
    return newPath;
}
//---------------------------------------------------------------------------
bool __fastcall JsonFile::LoadFile(const String& file)
{
    if (File::File::Exists(file)) {
        OnLoading();
        String path;
        try {
            auto json = File::File::ReadText(file);
            auto sr = std::make_unique<TStringReader>(json);
            auto jr = std::make_unique<TJsonTextReader>(sr.get());
            auto inArray = false;
            while (jr->Read()) {
                path = ProcessPath(jr->Path);
                switch (jr->TokenType) {
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
                    Set(path, static_cast<float>(jr->Value.AsExtended()));
                    if (inArray) OnEndObject(path);
                    break;
                case TJsonToken::Boolean:
                    Set(path, jr->Value.AsBoolean());
                    if (inArray) OnEndObject(path);
                    break;
                case TJsonToken::Raw:
                case TJsonToken::Null:
                case TJsonToken::None:
                case TJsonToken::StartConstructor:
                case TJsonToken::EndConstructor:
                case TJsonToken::Oid:
                case TJsonToken::Bytes:
                case TJsonToken::Decimal:
                case TJsonToken::Date:
                case TJsonToken::RegEx:
                case TJsonToken::DBRef:
                case TJsonToken::MinKey:
                case TJsonToken::MaxKey:
                case TJsonToken::CodeWScope:
                case TJsonToken::Comment:
                case TJsonToken::Undefined:
                    break;
                }
            }
            OnLoaded();
            return true;
        } catch (...) {
            // Error loading the JSON file
            ErrorMessage("Error loading JSON file: " + file + ", at path: " + path);
        }
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::OnStartObject(const String&)
{
    // do nothing; should be overridden
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::OnEndObject(const String&)
{
    // do nothing; should be overridden
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::OnLoading()
{
    // do nothing; should be overridden
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::OnLoaded()
{
    // do nothing; should be overridden
}
//---------------------------------------------------------------------------

