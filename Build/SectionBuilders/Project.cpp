//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/SectionBuilders/Project.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Project::Project()
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Project::~Project()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Project::Execute()
{
    const auto& project = theDocumentManager.ProjectConfig();

    AddLine(";");
    AddLine("; GAME       : " + project->Name);
    AddLine("; VERSION    : " + project->Version);
    AddLine("; DESCRIPTION: " + project->Description);
    AddLine("; AUTHOR     : " + project->Author);
    AddLine("; BUILD DATE : " + DateTimeToStr(Now()));
    AddLine(";");
    AddLine("; This file is read-only and periodically auto generated.");
    AddLine(";");
    AddLine(";DEFINEMACHINE \"" + project->Machine + "\"");
    AddLine(";");
    LineBreak();

    Success();
}
//---------------------------------------------------------------------------

