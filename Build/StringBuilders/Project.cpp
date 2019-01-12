//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/StringBuilders/Project.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall StringBuilders::Project::Project()
{
}
//---------------------------------------------------------------------------
__fastcall StringBuilders::Project::~Project()
{
}
//---------------------------------------------------------------------------
void __fastcall StringBuilders::Project::Execute()
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

