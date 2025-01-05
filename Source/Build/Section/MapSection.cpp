//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "MapSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/TiledMap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall MapSection::MapSection()
: Section("Map")
{
}
//---------------------------------------------------------------------------
__fastcall MapSection::~MapSection()
{
}
//---------------------------------------------------------------------------
void __fastcall MapSection::Execute()
{
    const auto& dm = theDocumentManager;
    // get the objects in the map
    auto mapDoc = dynamic_cast<Project::TiledMapDocument*>(dm.Get("Map", "Tiled", "Tile Map"));
    assert(mapDoc != nullptr);

    const auto mapSize = mapDoc->SetMinimalMapSize();
    AddLine("MAP WIDTH " + IntToStr(reinterpret_cast<int>(mapSize.Width() + 1)));
    AddLine("    STARTSCREEN " + IntToStr(mapDoc->StartRoomIndex));
    for (auto y = mapSize.Top; y <= mapSize.Bottom; y++) {
        String line = "    ";
        for (auto x = mapSize.Left; x <= mapSize.Right; x++) {
            auto ri = mapDoc->GetRoomIndex(TPoint(x, y));
            // don't export the disabled room (254)
            ri = (ri >= Project::g_RoomIndexDisabled) ? Project::g_RoomIndexEmpty : ri;
            line += PadNum(IntToStr(ri)) + " ";
        }
        AddLine(line);
    }
    AddLine("ENDMAP");
    LineBreak();

    // no map is ok
    Success();
}
//---------------------------------------------------------------------------

