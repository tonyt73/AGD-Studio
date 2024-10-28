//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall SectionBuilder::SectionBuilder(const String& description)
: m_Description(description)
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilder::~SectionBuilder()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilder::Clear()
{
    m_Result.Success = false;
    m_Result.Reason = "Not Implemented";
    m_Result.Content = "";
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilder::AddLine(String line)
{
    m_Result.Content += line + "\r\n";
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilder::LineBreak()
{
    m_Result.Content += "\r\n";
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilder::Success()
{
    m_Result.Success = true;
    m_Result.Reason = "Ok";
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilder::Failure(String reason)
{
    m_Result.Success = false;
    m_Result.Reason = reason;
}
//---------------------------------------------------------------------------
const Result& __fastcall SectionBuilder::Build()
{
    Clear();
    Execute();
    return m_Result;
}
//---------------------------------------------------------------------------
