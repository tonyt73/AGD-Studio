//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "SectionBuilder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
SectionBuilder::SectionBuilder(const String& description)
: m_Description(description)
{
}
//---------------------------------------------------------------------------
SectionBuilder::~SectionBuilder()
{
}
//---------------------------------------------------------------------------
void SectionBuilder::Clear()
{
    m_Result.Success = false;
    m_Result.Reason = "Not Implemented";
    m_Result.Content = "";
}
//---------------------------------------------------------------------------
void SectionBuilder::AddLine(String line)
{
    m_Result.Content += line + "\r\n";
}
//---------------------------------------------------------------------------
void SectionBuilder::LineBreak()
{
    m_Result.Content += "\r\n";
}
//---------------------------------------------------------------------------
void SectionBuilder::Success()
{
    m_Result.Success = true;
    m_Result.Reason = "Ok";
}
//---------------------------------------------------------------------------
void SectionBuilder::Failure(String reason)
{
    m_Result.Success = false;
    m_Result.Reason = reason;
}
//---------------------------------------------------------------------------
const Result& SectionBuilder::Build()
{
    Clear();
    Execute();
    return m_Result;
}
//---------------------------------------------------------------------------
