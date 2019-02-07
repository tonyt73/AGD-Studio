//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/SectionBuilders/Map.h"
#include "Project/DocumentManager.h"
#include "Project/MapDocuments.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Map::Map()
: SectionBuilder("Map")
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Map::~Map()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Map::Execute()
{
    const auto& dm = theDocumentManager;
    // get the objects in the map
    auto mapDoc = dynamic_cast<TiledMapDocument*>(dm.Get("Map", "Tiled", "Tile Map"));
    assert(mapDoc != nullptr);

    const auto& mapSize = mapDoc->GetMinimalMapSize();
	AddLine("MAP WIDTH " + IntToStr((int)mapSize.Width() + 3));
	AddLine("    STARTSCREEN " + IntToStr(mapDoc->StartRoomIndex));
    for (auto y = mapSize.Top; y <= mapSize.Bottom; y++)
    {
        String line = "    ";
        for (auto x = Max(0, mapSize.Left - 1); x <= Min(16, mapSize.Right + 1); x++)
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

