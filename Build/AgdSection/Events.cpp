//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include <System.StrUtils.hpp>
#include <System.Character.hpp>
#include "Build/AgdSection/Events.h"
#include "Project/DocumentManager.h"
#include "Project/MapDocuments.h"
#include "Project/FileDefinitions.h"
#include "System/File.h"
#include "System/Path.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Events::Events()
: SectionBuilder("Events")
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Events::~Events()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Events::Execute()
{
    const auto& dm = theDocumentManager;
    // get the objects in the map
    auto mapDoc = dynamic_cast<TiledMapDocument*>(dm.Get("Map", "Tiled", "Tile Map"));
    assert(mapDoc != nullptr);
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
                auto lc = 0;
                for (auto line : lines)
                {
                    lc++;
                    if (line.Trim().UpperCase().Pos(definition.Section) == 0)
					{
						// TODO: replace AGDx keywords with there AGD original
						line = line;
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

