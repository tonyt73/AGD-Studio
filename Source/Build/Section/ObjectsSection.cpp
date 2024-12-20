//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
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
    auto imgSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
    auto wPt = TPoint(wi->Rect.Left * imgSize.cx, wi->Rect.Top * imgSize.cy);
    auto objectsInMap = mapDoc->Get(Visuals::itObject);
    // get the list of object images
    Project::DocumentList images;
    dm.GetAllOfType("Image", images);
    for (auto image : images)
    {
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
            // TODO -cImprovement: Use the importer definition of the machine to determine if an object.colour parameter is needed
            if (gm.TypeOfBuffer == Visuals::BufferType::btAttribute) // && importer.contains("Objects", "object.colour")
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
            line += IntToStr(object->Y) + " " + IntToStr(object->X) + " ";
            //line += IntToStr((int)(wPt.Y + object->Y)) + " " + IntToStr((int)(wPt.X + object->X)) + " ";
            AddLine(line);
            // export the machine graphics data
            line = "             ";
            for (auto byte : enumerate(data))
            {
                line += IntToStr(byte.item) + " ";
                if (byte.index % imgSize.Width == 0)
                {
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

