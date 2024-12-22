//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Parameterizer.h"
#include "Project/Documents/DocumentManager.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
String Parameter::ization(const String& parameters)
{
    auto subbedParameters = parameters;
    auto gameName = Services::Folders::ProjectName;
    auto gamePath = Services::Folders::Project;

    subbedParameters = StringReplace(subbedParameters, "%GamePath%", gamePath, TReplaceFlags(rfReplaceAll | rfIgnoreCase));
    subbedParameters = StringReplace(subbedParameters, "%GameName%", gameName, TReplaceFlags(rfReplaceAll | rfIgnoreCase));

    return subbedParameters;
}
//---------------------------------------------------------------------------
