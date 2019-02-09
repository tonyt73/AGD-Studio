//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/AgdSection/SectionBuilder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::SectionBuilder::SectionBuilder(const String& description)
: m_Description(description)
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::SectionBuilder::~SectionBuilder()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::SectionBuilder::Clear()
{
    m_Result.Success = false;
    m_Result.Reason = "Not Implemented";
    m_Result.Content = "";
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::SectionBuilder::AddLine(String line)
{
    m_Result.Content += line + "\r\n";
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::SectionBuilder::LineBreak()
{
    m_Result.Content += "\r\n";
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::SectionBuilder::Success()
{
    m_Result.Success = true;
    m_Result.Reason = "Ok";
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::SectionBuilder::Failure(String reason)
{
    m_Result.Success = false;
    m_Result.Reason = reason;
}
//---------------------------------------------------------------------------
const SectionBuilders::Result& __fastcall SectionBuilders::SectionBuilder::Build()
{
    Clear();
    Execute();
    return m_Result;
}
//---------------------------------------------------------------------------
