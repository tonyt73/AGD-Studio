//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
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
    AddLine("; This file is read-only.");
    AddLine(";");
    AddLine("; MACHINE \"" + project->Machine + "\"");
    AddLine(";");
    AddLine("MACHINE " + project->MachineId);
    LineBreak();
    Success();
}
//---------------------------------------------------------------------------
}
