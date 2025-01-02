//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "WindowSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/Window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall WindowSection::WindowSection()
: Section("Window")
{
}
//---------------------------------------------------------------------------
__fastcall WindowSection::~WindowSection()
{
}
//---------------------------------------------------------------------------
void __fastcall WindowSection::Execute()
{
    const auto& Window = dynamic_cast<Project::WindowDocument*>(theDocumentManager.Get("Window", "Definition", "Window"));
    if (Window) {
        AddLine("DEFINEWindow " + IntToStr(static_cast<int>(Window->Rect.Top)) + " " + IntToStr(static_cast<int>(Window->Rect.Left)) + " " + IntToStr(static_cast<int>(Window->Rect.Height())) + " " + IntToStr(static_cast<int>(Window->Rect.Width())));
        LineBreak();
        Success();
    } else {
        Failure("Window dimensions are not set");
    }
}
//---------------------------------------------------------------------------

