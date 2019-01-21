//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Builder.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Builder::Builder(BuildMessages& buildMessages, BuildMessageType type, const String& description)
: m_BuildMessages(buildMessages)
, m_Type(type)
, m_Description(description)
{
}
//---------------------------------------------------------------------------
__fastcall Builder::~Builder()
{
}
//---------------------------------------------------------------------------
