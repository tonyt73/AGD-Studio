//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "BuildProcess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall BuildProcess::BuildProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description)
: m_BuildMessages(buildMessages)
, m_Type(type)
, m_Description(description)
{
}
//---------------------------------------------------------------------------
__fastcall BuildProcess::~BuildProcess()
{
}
//---------------------------------------------------------------------------
