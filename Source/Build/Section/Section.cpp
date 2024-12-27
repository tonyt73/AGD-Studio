//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Section.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall Section::Section(const String& description)
: m_Description(description)
{
}
//---------------------------------------------------------------------------
__fastcall Section::~Section()
{
}
//---------------------------------------------------------------------------
void __fastcall Section::Clear()
{
    m_Result.Success = false;
    m_Result.Reason = "Not Implemented";
    m_Result.Content = "";
}
//---------------------------------------------------------------------------
void __fastcall Section::AddLine(String line)
{
    m_Result.Content += line + "\r\n";
}
//---------------------------------------------------------------------------
void __fastcall Section::LineBreak()
{
    m_Result.Content += "\r\n";
}
//---------------------------------------------------------------------------
void __fastcall Section::Success()
{
    m_Result.Success = true;
    m_Result.Reason = "Ok";
}
//---------------------------------------------------------------------------
void __fastcall Section::Failure(String reason)
{
    m_Result.Success = false;
    m_Result.Reason = reason;
}
//---------------------------------------------------------------------------
const Result& __fastcall Section::Build()
{
    Clear();
    Execute();
    return m_Result;
}
//---------------------------------------------------------------------------
