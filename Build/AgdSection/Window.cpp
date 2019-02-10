//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/AgdSection/Window.h"
#include "Project/DocumentManager.h"
#include "Project/WindowDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Window::Window()
: SectionBuilder("Window")
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Window::~Window()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Window::Execute()
{
    const auto& Window = (WindowDocument*)theDocumentManager.Get("Window", "Definition", "Window");
    AddLine("DEFINEWINDOW " + IntToStr((int)Window->Rect.Left) + " " + IntToStr((int)Window->Rect.Right) + " " + IntToStr((int)Window->Rect.Height()) + " " + IntToStr((int)Window->Rect.Width()));
    LineBreak();
    Success();
}
//---------------------------------------------------------------------------

