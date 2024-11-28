//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "ControlsSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/Controls.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
__fastcall ControlsSection::ControlsSection()
: Section("Controls")
{
}
//---------------------------------------------------------------------------
__fastcall ControlsSection::~ControlsSection()
{
}
//---------------------------------------------------------------------------
void __fastcall ControlsSection::Execute()
{
    const auto& Keys = (Project::ControlsDocument*)theDocumentManager.Get("Controls", "List", "Controls");
    String line = "DEFINECONTROLS  ";
    for (const auto key : Project::AgdKeys) {
        auto keyCode = Keys->GetAsciiCode(key);
        if (32 <= keyCode && keyCode <= 126) {
            line += "'" + UnicodeString::StringOfChar(keyCode, 1) + "' ";
        }
        else if (keyCode) {
            line += IntToStr(keyCode) + " ";
        }
    }
    AddLine(line);
    LineBreak();
    Success();
}
//---------------------------------------------------------------------------
}
