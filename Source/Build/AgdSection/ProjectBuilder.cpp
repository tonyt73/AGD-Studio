//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "ProjectBuilder.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
ProjectBuilder::ProjectBuilder()
: SectionBuilder("Project Header")
{
}
//---------------------------------------------------------------------------
ProjectBuilder::~ProjectBuilder()
{
}
//---------------------------------------------------------------------------
void ProjectBuilder::Execute()
{
    const auto& project = ::theDocumentManager.ProjectConfig();
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
}
