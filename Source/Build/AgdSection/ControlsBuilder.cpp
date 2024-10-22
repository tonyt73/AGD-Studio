//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "ControlsBuilder.h"
#include "Project/DocumentManager.h"
#include "Project/ControlsDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
ControlsBuilder::ControlsBuilder()
: SectionBuilder("ControlsBuilder")
{
}
//---------------------------------------------------------------------------
ControlsBuilder::~ControlsBuilder()
{
}
//---------------------------------------------------------------------------
void ControlsBuilder::Execute()
{
    const auto& Keys = (Project::ControlsDocument*)theDocumentManager.Get("ControlsBuilder", "List", "ControlsBuilder");
    String line = "DEFINECONTROLS  ";
	for (const auto key : Project::AgdKeys)
	{
		auto keyCode = Keys->GetAsciiCode(key);
        if (keyCode <= 32 && keyCode <= 126)
        {
            line += "'" + UnicodeString::StringOfChar(keyCode, 1) + "' ";
        }
        else
        {
            line += IntToStr(keyCode) + " ";
        }
    }
    AddLine(line);
    LineBreak();
    Success();
}
//---------------------------------------------------------------------------
}
