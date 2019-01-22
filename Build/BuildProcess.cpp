//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "BuildProcess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
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
