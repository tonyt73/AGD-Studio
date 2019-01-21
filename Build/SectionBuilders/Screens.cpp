//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/SectionBuilders/Screens.h"
#include "Project/DocumentManager.h"
#include "Project/ImageDocuments.h"
#include "Project/MapDocuments.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Screens::Screens()
: SectionBuilder("Screens")
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Screens::~Screens()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Screens::Execute()
{
    const auto& dm = theDocumentManager;
    // get the objects in the map
    auto mapDoc = dynamic_cast<TiledMapDocument*>(dm.Get("Map", "Tiled", "Tile Map"));
    assert(mapDoc != nullptr);

    const auto& wi = theDocumentManager.ProjectConfig()->Window;
    auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itTile].Minimum;
    auto wPt = TPoint(wi.X * tileSize.cx, wi.Y * tileSize.cy);
    auto ri = 0;
    for (auto ry = 0; ry < g_MaxMapRoomsDown; ry++ )
    {
        for (auto rx = 0; rx < g_MaxMapRoomsAcross; rx++)
        {
            if (!mapDoc->IsRoomEmpty(rx, ry))
            {
                auto roomEntities = mapDoc->Get(meRoom, TSize(rx, ry));
                auto roomPt = TPoint(rx * tileSize.cx * wi.Width, ry * tileSize.cy * wi.Height);
                String line = "DEFINESCREEN ";
                for (auto y = 0; y < mapDoc->RoomHeight; y++)
                {
                    for (auto x = 0; x < mapDoc->RoomWidth; x++)
                    {
                        auto entity = find_if(roomEntities.begin(), roomEntities.end(),
                            [&](const Entity& e)
                            {
                                return ((e.Image->ImageType == itTile) && (e.Pt.x == x * tileSize.cx) && (e.Pt.y == y * tileSize.cy));
                            } );
                        if (entity != roomEntities.end())
                        {
                            // get tile id as tile index
                            auto index = dm.GetAsIndex(entity->Id);
                            if (index != -1)
                            {
                                line += IntToStr(index) + " ";
                            }
                            else
                            {
                                // badly referenced tile
                                Failure("Tile Id: " + IntToStr((int)entity->Id) + ", in map was not found in the document manager.");
                                return;
                            }
                        }
                        else
                        {
                            // tile 0
                            line += "0 ";
                        }
                    }
                    AddLine(line);
                    line = "             ";
                }
                // list sprites
                for (const auto& entity : roomEntities)
                {
                    if (entity.Image->ImageType == itSprite)
                    {
                        // get sprite id as sprite index
                        auto index = dm.GetAsIndex(entity.Id);
                        line = "SPRITEPOSITION " + IntToStr(entity.SpriteType) + " " + IntToStr(index) + " " + IntToStr((int)(wPt.y + entity.Pt.y)) + " " + IntToStr((int)(wPt.x + entity.Pt.x));
                        AddLine(line);
                    }
                }

                LineBreak();
            }
        }
    }

    const auto& mapSize = mapDoc->GetMinimalMapSize();
    AddLine("MAP WIDTH " + IntToStr((int)mapSize.Width() + 1));
    AddLine("    STARTSCREEN " + IntToStr(mapDoc->GetRoomIndex(AGDX::Point(mapDoc->StartLocationX, mapDoc->StartLocationY))));
    for (auto y = mapSize.Top; y <= mapSize.Bottom; y++)
    {
        String line = "    ";
        for (auto x = mapSize.Left; x <= mapSize.Right; x++)
        {
            auto ri = mapDoc->GetRoomIndex(AGDX::Point(x, y));
            if (ri != -1)
            {
                line += IntToStr(ri) + " ";
            }
            else
            {
                line += "255 ";
            }
        }
        AddLine(line);
    }
    AddLine("ENDMAP");

    // no screens is ok
    Success();
}
//---------------------------------------------------------------------------
