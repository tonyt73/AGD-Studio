//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#include "Build/Parameterizer.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
String Parameter::ization(const String& parameters)
{
    auto subbedParameters = parameters;
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    auto gameName = System::Path::ProjectName;
    auto gamePath = System::Path::Project;

    subbedParameters = StringReplace(subbedParameters, "%GamePath%", gamePath, TReplaceFlags(rfReplaceAll || rfIgnoreCase));
    subbedParameters = StringReplace(subbedParameters, "%GameName%", gameName, TReplaceFlags(rfReplaceAll || rfIgnoreCase));

    return subbedParameters;
}
//---------------------------------------------------------------------------
