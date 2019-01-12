//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include <System.StrUtils.hpp>
#include "Build/StringBuilders/Events.h"
#include "Project/FileDefinitions.h"
#include "System/File.h"
#include "System/Path.h"
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
    auto gamePath = System::Path::Project;
    auto definitions = std::make_unique<FileDefinitions>();
    for (const auto& definition : definitions->GetDefinitions())
    {
        if (definition.Type == "Event")
        {
            auto file = System::File::Combine(gamePath, definition.Filename + ".event");
            if (System::File::Exists(file))
            {
                auto lines = System::File::ReadLines(file);
                AddLine(definition.Section);
                for (auto line : lines)
                {
                    if (line.Trim().UpperCase().Pos(definition.Section) == 0)
                    {
                        AddLine(line);
                    }
                }
                LineBreak();
                Success();
            }
            else
            {
                Failure("Failed to find the event file: " + file);
            }
        }
    }
}
//---------------------------------------------------------------------------

