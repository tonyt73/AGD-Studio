//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
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
: m_StringWriter(nullptr)
, m_JsonWriter(nullptr)
{
}
//---------------------------------------------------------------------------
__fastcall JsonFile::~JsonFile()
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Open(const String& file)
{
    m_File = File::File::ChangeExtension(file, "json");
    m_StringWriter = new TStringWriter();
    m_JsonWriter = new TJsonTextWriter(m_StringWriter);
    m_JsonWriter->Formatting = TJsonFormatting::Indented;
    m_JsonWriter->WriteStartObject(); // sections
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Close()
{
    if (m_StringWriter != nullptr && m_JsonWriter != nullptr)
    {
        m_JsonWriter->WriteEndObject(); // sections
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
void __fastcall JsonFile::Write(const String& property, const double& value) const
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
void __fastcall JsonFile::Set(const String& property, const double& value)
{
	if (m_PropertyMap.count(property) != 0)
	{
		((*(double*)m_PropertyMap[property])) = value;
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
    auto filename = File::File::ChangeExtension(file, "json");
    if (File::File::Exists(filename))
    {
        auto json = File::File::ReadText(filename);
        auto sr = make_unique<TStringReader>(json);
        auto jr = make_unique<TJsonTextReader>(sr.get());
        String property;
		auto depth = 0;
        String arrayProperty;
        bool inArray = false;
        while (jr->Read())
        {
            switch (jr->TokenType)
            {
                case TJsonToken::StartObject:
                    depth++;
                    if (inArray)
                    {
                        property += ".Object";
                    }
                    OnStartObject(property);
                    break;
				case TJsonToken::EndObject:
					depth--;
					// remove the last .name
                    OnEndObject(property);
					property = property.Delete(property.LastDelimiter("."), property.Length());
					break;
				case TJsonToken::StartArray:
					property += ".Array";
                    inArray = true;
					break;
				case TJsonToken::EndArray:
					property = property.Delete(property.LastDelimiter("."), property.Length());
                    inArray = false;
					break;
				case TJsonToken::PropertyName:
                    property += "." + jr->Value.AsString();
                    break;
                case TJsonToken::String:
                {
                    Set(property, jr->Value.AsString());
                    // remove the last .name
                    property = property.Delete(property.LastDelimiter("."), property.Length());
                    break;
                }
                case TJsonToken::Integer:
                    Set(property, jr->Value.AsInteger());
                    // remove the last .name
                    property = property.Delete(property.LastDelimiter("."), property.Length());
                    break;
                case TJsonToken::Float:
                    {
                        double value = jr->Value.AsExtended();
                        Set(property, value);
                        // remove the last .name
                        property = property.Delete(property.LastDelimiter("."), property.Length());
                    }
                    break;
                case TJsonToken::Boolean:
                    Set(property, jr->Value.AsBoolean());
                    // remove the last .name
                    property = property.Delete(property.LastDelimiter("."), property.Length());
                    break;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall JsonFile::Save()
{
    // do nothing; should be overridden
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

