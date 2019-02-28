//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/AgdSection/Controls.h"
#include "Project/DocumentManager.h"
#include "Project/ControlsDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace SectionBuilders;
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Controls::Controls()
: SectionBuilder("Controls")
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Controls::~Controls()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Controls::Execute()
{
    const auto& Keys = (ControlsDocument*)theDocumentManager.Get("Controls", "List", "Controls");
    String line = "DEFINECONTROLS  ";
    for (auto i = 0; i < keyLast; i++)
    {
        auto keyCode = Keys->GetAsciiCode((eAgdKey)i);
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

