//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include <System.StrUtils.hpp>
#include <System.SysUtils.hpp>
#include <typeinfo>
#include "Generic.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const String tokenObj = "|";
const String tokenSep = "^";
//---------------------------------------------------------------------------
__fastcall Generic::Generic()
{
}
//---------------------------------------------------------------------------
__fastcall Generic::Generic(const String& object)
: m_Object(object)
{
}
//---------------------------------------------------------------------------
__fastcall Generic::Generic(const Generic& other)
: m_Object(other.m_Object)
{
}
//---------------------------------------------------------------------------
void __fastcall Generic::Process()
{
	if (m_Objects.size() == 0 && m_Object.Length() > 0)
	{
		// split the string by the token obj
		auto objects = System::Strutils::SplitString(m_Object, tokenObj);
		for (auto object : objects)
		{
			auto tokens = System::Strutils::SplitString(object, tokenSep);
            if (tokens.Length == 2)
            {
    			m_Objects[tokens[0]] = tokens[1];
            }
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Generic::Add(const String& name, const String& value)
{
	m_Object += tokenObj + name + tokenSep + "string:"  + value;
}
//---------------------------------------------------------------------------
void __fastcall Generic::Add(const String& name, const bool& value)
{
	m_Object += tokenObj + name + tokenSep + "bool:" + String(value ? "true" : "false");
}
//---------------------------------------------------------------------------
void __fastcall Generic::Add(const String& name, const int& value)
{
	m_Object += tokenObj + name + tokenSep + "int:" + IntToStr(value);
}
//---------------------------------------------------------------------------
void __fastcall Generic::Add(const String& name, const float& value)
{
	m_Object += tokenObj + name + tokenSep + "float:" + FloatToStrF(value, ffFixed, 6, 2);
}
//---------------------------------------------------------------------------
bool __fastcall Generic::Get(const String& name, String& value)
{
	Process();
	if (m_Objects.count(name) == 1)
	{
		// parse string to string
		auto def = m_Objects[name];
		auto tokens = System::Strutils::SplitString(def, ":");
		value = tokens[1];
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall Generic::Get(const String& name, bool& value)
{
	Process();
	if (m_Objects.count(name) == 1)
	{
		// parse string to bool
		auto def = m_Objects[name];
		auto tokens = System::Strutils::SplitString(def, ":");
		value = tokens[1] == "true";
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall Generic::Get(const String& name, int& value)
{
	Process();
	if (m_Objects.count(name) == 1)
	{
		// parse string to int
		auto def = m_Objects[name];
		auto tokens = System::Strutils::SplitString(def, ":");
		value = StrToInt(tokens[1]);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall Generic::Get(const String& name, float& value)
{
	Process();
	if (m_Objects.count(name) == 1)
	{
		// parse string to float
		auto def = m_Objects[name];
		auto tokens = System::Strutils::SplitString(def, ":");
		value = StrToFloat(tokens[1]);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------

