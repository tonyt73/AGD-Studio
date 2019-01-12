//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/StringBuilders/Events.h"
#include "Project/FileDefinitions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall StringBuilders::Events::Events()
{
}
//---------------------------------------------------------------------------
__fastcall StringBuilders::Events::~Events()
{
}
//---------------------------------------------------------------------------
void __fastcall StringBuilders::Events::Execute()
{
    auto definitions = std::make_unique<FileDefinitions>();
    for (const auto& definition : definitions->GetDefinitions())
    {
        if (definition.Type == "Event")
        {

        }
    }
}
//---------------------------------------------------------------------------

