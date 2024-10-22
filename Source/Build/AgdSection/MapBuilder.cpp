//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "MapBuilder.h"
#include "Project/DocumentManager.h"
#include "Project/TiledMapDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
MapBuilder::MapBuilder()
: SectionBuilder("MapBuilder")
{
}
//---------------------------------------------------------------------------
MapBuilder::~MapBuilder()
{
}
//---------------------------------------------------------------------------
void MapBuilder::Execute()
{
    const auto& dm = theDocumentManager;
    // get the objects in the map
    auto mapDoc = dynamic_cast<Project::TiledMapDocument*>(dm.Get("MapBuilder", "Tiled", "Tile MapBuilder"));
    assert(mapDoc != nullptr);

    const auto& mapSize = mapDoc->GetMinimalMapSize();
    AddLine("MAP WIDTH " + IntToStr((int)mapSize.Width() + 1));
    AddLine("    STARTSCREEN " + IntToStr(mapDoc->StartRoomIndex));
    for (auto y = mapSize.Top; y <= mapSize.Bottom; y++)
    {
        String line = "    ";
        for (auto x = mapSize.Left; x <= mapSize.Right; x++)
        {
            auto ri = mapDoc->GetRoomIndex(TPoint(x, y));
            line += IntToStr(ri) + " ";
        }
        AddLine(line);
    }
    AddLine("ENDMAP");
    LineBreak();

    // no map is ok
    Success();
}
//---------------------------------------------------------------------------

