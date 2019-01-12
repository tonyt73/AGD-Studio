//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/StringBuilders/Window.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall StringBuilders::Window::Window()
{
}
//---------------------------------------------------------------------------
__fastcall StringBuilders::Window::~Window()
{
}
//---------------------------------------------------------------------------
void __fastcall StringBuilders::Window::Execute()
{
    const auto& project = theDocumentManager.ProjectConfig();

    AddLine("DEFINEWINDOW " + IntToStr((int)project->Window.Y) + " " + IntToStr((int)project->Window.X) + " " + IntToStr((int)project->Window.Height) + " " + IntToStr((int)project->Window.Width));
    LineBreak();

    Success();
}
//---------------------------------------------------------------------------

