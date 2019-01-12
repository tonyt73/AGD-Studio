//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/SectionBuilders/Window.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Window::Window()
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Window::~Window()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Window::Execute()
{
    const auto& project = theDocumentManager.ProjectConfig();

    AddLine("DEFINEWINDOW " + IntToStr((int)project->Window.Y) + " " + IntToStr((int)project->Window.X) + " " + IntToStr((int)project->Window.Height) + " " + IntToStr((int)project->Window.Width));
    LineBreak();

    Success();
}
//---------------------------------------------------------------------------

