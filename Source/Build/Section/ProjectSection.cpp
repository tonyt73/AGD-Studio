//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "ProjectSection.h"
#include "Project/Documents/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
__fastcall ProjectSection::ProjectSection()
: Section("Project Header")
{
}
//---------------------------------------------------------------------------
__fastcall ProjectSection::~ProjectSection()
{
}
//---------------------------------------------------------------------------
void __fastcall ProjectSection::Execute()
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
