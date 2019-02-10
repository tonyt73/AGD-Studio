//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/AgdSection/Map.h"
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

