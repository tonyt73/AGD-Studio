//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "ScreensSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/BaseImage.h"
#include "Project/Documents/TiledMap.h"
#include "Project/Documents/Window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall ScreensSection::ScreensSection()
: Section("Screens")
{
}
//---------------------------------------------------------------------------
__fastcall ScreensSection::~ScreensSection()
{
}
//---------------------------------------------------------------------------
void __fastcall ScreensSection::Execute()
{
    auto& dm = theDocumentManager;
    // get the objects in the map
    auto mapDoc = dynamic_cast<Project::TiledMapDocument*>(dm.Get("Map", "Tiled", "Tile Map"));
    assert(mapDoc != nullptr);

    const auto& wi = static_cast<Project::WindowDocument*>(dm.Get("Window", "Definition", "Window"));
    if (wi) {
        auto tileSize = dm.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
        auto wPt = TPoint(wi->Rect.Left * tileSize.cx, wi->Rect.Top * tileSize.cy);
        for (auto ri = 0; ri < 255; ri++) {
            for (auto ry = 0; ry < Project::g_MaxMapRoomsDown; ry++ ) {
                for (auto rx = 0; rx < Project::g_MaxMapRoomsAcross; rx++) {
                    if (mapDoc->GetRoomIndex(TPoint(rx, ry)) == ri) {
                        auto roomEntities = mapDoc->GetEntities(Project::meRoom, TSize(rx, ry));
                        // resolve big tiles and expand roomEntities
                        auto roomPt = TPoint(rx * tileSize.cx * wi->Rect.Width(), ry * tileSize.cy * wi->Rect.Height());
                        String line = "DEFINESCREEN ";
                        for (auto y = 0; y < wi->Rect.Height(); y++) {
                            for (auto x = 0; x < wi->Rect.Width(); x++) {
                                // single tile position
                                auto tx = x * tileSize.cx;
                                auto ty = y * tileSize.cy;
                                // find the tile (oversized or not) that intersects with the single tile position
                                auto entity = find_if(roomEntities.begin(), roomEntities.end(), [&](const Project::MapEntity& e) {
                                    return ((e.Image->ImageType == Visuals::itTile) && (e.Pt.x <= tx && tx < e.Pt.x + e.Image->Width) && (e.Pt.y <= ty && ty < e.Pt.y + e.Image->Height));
                                } );
                                if (entity != roomEntities.end()) {
                                    // get offset into tile (0,0 for a single tile)
                                    //                      (n, m for a big tile)
                                    auto txo = tx - entity->Pt.x;
                                    auto tyo = ty - entity->Pt.y;
                                    // get the game index of the tile object
                                    auto index = dm.GetIndexFor(entity->Id, txo, tyo);
                                    if (index != -1) {
                                        line += PadNum(IntToStr(index)) + " ";
                                    } else {
                                        // badly referenced tile
                                        Failure("Tile Id: " + UIntToStr(entity->Id) + ", in map was not found in the document manager.");
                                        return;
                                    }
                                } else {
                                    // tile 0
                                    line += "  0 ";
                                }
                            }
                            AddLine(line);
                            line = "             ";
                        }
                        // list sprites
                        for (const auto& entity : roomEntities) {
                            if (entity.IsSprite) {
                                auto type = std::max(0, entity.SpriteType);
                                // get sprite id as sprite index
                                auto index = dm.GetAsIndex(entity.Id);
                                line = "SPRITEPOSITION " + IntToStr(type) + " " + IntToStr(index) + " " + IntToStr(static_cast<int>(wPt.y + entity.Pt.y)) + " " + IntToStr(static_cast<int>(wPt.x + entity.Pt.x));
                                AddLine(line);
                            }
                        }
                        LineBreak();
                    }
                }
            }
        }
        // no screens is ok
        Success();
    } else {
        Failure("Window dimensions are not set");
    }
}
//---------------------------------------------------------------------------
