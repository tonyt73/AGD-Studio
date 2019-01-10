//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/StringBuilders/StringBuilder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall StringBuilders::StringBuilder::StringBuilder()
{
}
//---------------------------------------------------------------------------
__fastcall StringBuilders::StringBuilder::~StringBuilder()
{
}
//---------------------------------------------------------------------------
void __fastcall StringBuilders::StringBuilder::Clear()
{
    m_Result.Success = false;
    m_Result.Reason = "Not Implemented";
    m_Result.Content = "";
}
//---------------------------------------------------------------------------
void __fastcall StringBuilders::StringBuilder::AddLine(String line)
{
    m_Result.Content += line + "\r\n";
}
//---------------------------------------------------------------------------
void __fastcall StringBuilders::StringBuilder::LineBreak()
{
    m_Result.Content += "\r\n";
}
//---------------------------------------------------------------------------
void __fastcall StringBuilders::StringBuilder::Success()
{
    m_Result.Success = true;
}
//---------------------------------------------------------------------------
void __fastcall StringBuilders::StringBuilder::Reason(String reason)
{
    m_Result.Reason = reason;
}
//---------------------------------------------------------------------------
const StringBuilders::Result& __fastcall StringBuilders::StringBuilder::Build()
{
    Clear();
    Execute();
    return m_Result;
}
//---------------------------------------------------------------------------
