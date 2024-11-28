//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
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
    const auto& dm = theDocumentManager;
    // get the objects in the map
    auto mapDoc = dynamic_cast<Project::TiledMapDocument*>(dm.Get("Map", "Tiled", "Tile Map"));
    assert(mapDoc != nullptr);

    const auto& wi = (Project::WindowDocument*)theDocumentManager.Get("Window", "Definition", "Window");
    if (wi)
    {
        auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
        auto wPt = TPoint(wi->Rect.Left * tileSize.cx, wi->Rect.Top * tileSize.cy);
        auto ri = 0;
        for (auto ri = 0; ri < 255; ri++)
        {
            for (auto ry = 0; ry < Project::g_MaxMapRoomsDown; ry++ )
            {
                for (auto rx = 0; rx < Project::g_MaxMapRoomsAcross; rx++)
                {
                    if (mapDoc->GetRoomIndex(TPoint(rx, ry)) == ri)
                    {
                        auto roomEntities = mapDoc->Get(Project::meRoom, TSize(rx, ry));
                        auto roomPt = TPoint(rx * tileSize.cx * wi->Rect.Width(), ry * tileSize.cy * wi->Rect.Height());
                        String line = "DEFINESCREEN ";
                        for (auto y = 0; y < wi->Rect.Height(); y++)
                        {
                            for (auto x = 0; x < wi->Rect.Width(); x++)
                            {
                                auto entity = find_if(roomEntities.begin(), roomEntities.end(),
                                    [&](const Project::MapEntity& e)
                                    {
                                        return ((e.Image->ImageType == Visuals::itTile) && (e.Pt.x == x * tileSize.cx) && (e.Pt.y == y * tileSize.cy));
                                    } );
                                if (entity != roomEntities.end())
                                {
                                    // get tile id as tile index
                                    auto index = dm.GetAsIndex(entity->Id);
                                    if (index != -1)
                                    {
                                        auto number = "   " + IntToStr(index);
                                        line += number.SubString(number.Length() - 2, 3) + " ";
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
                                    line += "  0 ";
                                }
                            }
                            AddLine(line);
                            line = "             ";
                        }
                        // list sprites
                        for (const auto& entity : roomEntities)
                        {
                            if (entity.IsSprite)
                            {
                                auto type = std::max(0, entity.SpriteType);
                                // get sprite id as sprite index
                                auto index = dm.GetAsIndex(entity.Id);
                                line = "SPRITEPOSITION " + IntToStr(type) + " " + IntToStr(index) + " " + IntToStr((int)(entity.Pt.y)) + " " + IntToStr((int)(entity.Pt.x));
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
    }
    else
    {
        Failure("Window dimensions are not set");
    }
}
//---------------------------------------------------------------------------
