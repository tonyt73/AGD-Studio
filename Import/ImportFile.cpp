//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "ImportFile.h"
#include "Messaging.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ImportFile::ImportFile()
{
}
//---------------------------------------------------------------------------
__fastcall ImportFile::~ImportFile()
{
}
//---------------------------------------------------------------------------
void __fastcall ImportFile::Error(const String& message) const
{
    ::Messaging::Bus::Publish<ErrorMessage>(ErrorMessage(message));
}
//---------------------------------------------------------------------------
void __fastcall ImportFile::Warning(const String& message) const
{
    ::Messaging::Bus::Publish<WarningMessage>(WarningMessage(message));
}
//---------------------------------------------------------------------------
void __fastcall ImportFile::Information(const String& message) const
{
    ::Messaging::Bus::Publish<InformationMessage>(InformationMessage(message));
}
//---------------------------------------------------------------------------
