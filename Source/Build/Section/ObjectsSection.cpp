//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "ObjectsSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/Object.h"
#include "Project/Documents/TiledMap.h"
#include "Project/Documents/Window.h"
#include "Visuals/GraphicsMode.h"
#include "Visuals/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall ObjectsSection::ObjectsSection()
: Section("Objects")
{
}
//---------------------------------------------------------------------------
__fastcall ObjectsSection::~ObjectsSection()
{
}
//---------------------------------------------------------------------------
void __fastcall ObjectsSection::Execute()
{
    const auto& dm = theDocumentManager;
    // get the objects in the map
    auto mapDoc = dynamic_cast<Project::TiledMapDocument*>(dm.Get("Map", "Tiled", "Tile Map"));
    assert(mapDoc != nullptr);
    const auto& wi = (Project::WindowDocument*)theDocumentManager.Get("Window", "Definition", "Window");
    auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
    auto wPt = TPoint(wi->Rect.Left * tileSize.cx, wi->Rect.Top * tileSize.cy);
    auto objectsInMap = mapDoc->Get(Visuals::itObject);
    // get the list of object images
    Project::DocumentList images;
    dm.GetAllOfType("Image", images);
    for (auto image : images)
    {
        // TODO: Add support for big images
        auto object = dynamic_cast<Project::ObjectDocument*>(image);
        if (object != nullptr)
        {
            String line = "DEFINEOBJECT ";
            const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
            const auto& gm = (*(mc.GraphicsMode()));
            // make an image canvas
            auto image = std::make_unique<Visuals::Image>(object, gm);
            image->ChangeFrame(0);
            auto data = image->GetExportNativeFormat();
            if (mc.Name.Pos("ZX Spectrum") != 0)
            {
                // extract the image colour and remove the last 4 bytes (attributes) from the data
                line += IntToStr(data.back()) + " ";
                // remove the attributes
                data.pop_back();
                data.pop_back();
                data.pop_back();
                data.pop_back();
            }
            // add the room
            auto roomIndex = object->State == Visuals::osRoom ? ((Project::ObjectDocument*)object)->RoomIndex : (object->State == Visuals::osDisabled ? 254 : 255);
            line += IntToStr((int)roomIndex) + " ";
            line += IntToStr((int)(wPt.Y + object->Y)) + " " + IntToStr((int)(wPt.X + object->X)) + " ";
            AddLine(line);
            // export the machine graphics data
            line = "             ";
            auto x = 0;
            for (auto byte : data)
            {
                line += IntToStr(byte) + " ";
                if (++x == 16)
                {
                    x = 0;
                    AddLine(line);
                    line = "             ";
                }
            }
            line = line.SubString(1, line.Length() - 1);
            AddLine(line);
            LineBreak();
        }
    }

    // no objects is ok
    Success();
}
//---------------------------------------------------------------------------

