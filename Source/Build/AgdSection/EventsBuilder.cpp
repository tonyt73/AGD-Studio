//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "EventsBuilder.h"
#include "Project/DocumentManager.h"
#include "Project/FileDefinitions.h"
#include "Project/TiledMapDocument.h"
#include "Services/File.h"
#include "Services/Folders.h"
#include <System.Character.hpp>
#include <System.StrUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall EventsBuilder::EventsBuilder()
    : SectionBuilder("EventsBuilder")
{
}
//---------------------------------------------------------------------------
__fastcall EventsBuilder::~EventsBuilder()
{
}
//---------------------------------------------------------------------------
void __fastcall EventsBuilder::Execute()
{
    const auto& dm = theDocumentManager;
    // get the objects in the map
    auto mapDoc = dynamic_cast<Project::TiledMapDocument*>(dm.Get("Map", "Tiled", "Tile Map"));
    assert(mapDoc != nullptr);
    auto gamePath = Services::Folders::Project;
    auto definitions = std::make_unique<Project::FileDefinitions>();
    for (const auto& definition : definitions->GetDefinitions()) {
        if (definition.Type == "Event") {
            auto file = Services::File::Combine(gamePath, definition.Filename + ".event");
            if (Services::File::Exists(file)) {
                auto lines = Services::File::ReadLines(file);
                AddLine(definition.Section);
                auto lc = 0;
                for (auto line : lines) {
                    lc++;
                    if (line.Trim().UpperCase().Pos(definition.Section) == 0) {
                        // TODO: replace AGDx keywords with there AGD original
                        line = line;
                        AddLine(line);
                    }
                }
                LineBreak();
                Success();
            } else {
                Failure("Failed to find the event file: " + file);
            }
        }
    }
}
//---------------------------------------------------------------------------

