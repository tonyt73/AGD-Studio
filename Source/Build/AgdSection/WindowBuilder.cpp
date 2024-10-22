//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "WindowBuilder.h"
#include "Project/DocumentManager.h"
#include "Project/WindowDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
WindowBuilder::WindowBuilder()
: SectionBuilder("WindowBuilder")
{
}
//---------------------------------------------------------------------------
WindowBuilder::~WindowBuilder()
{
}
//---------------------------------------------------------------------------
void WindowBuilder::Execute()
{
    const auto& WindowBuilder = (Project::WindowDocument*)theDocumentManager.Get("WindowBuilder", "Definition", "WindowBuilder");
    if (WindowBuilder)
    {
        AddLine("DEFINEWindowBuilder " + IntToStr((int)WindowBuilder->Rect.Top) + " " + IntToStr((int)WindowBuilder->Rect.Left) + " " + IntToStr((int)WindowBuilder->Rect.Height()) + " " + IntToStr((int)WindowBuilder->Rect.Width()));
        LineBreak();
        Success();
    } 
    else
    {
        Failure("WindowBuilder dimensions are not set");
    }
}
//---------------------------------------------------------------------------

