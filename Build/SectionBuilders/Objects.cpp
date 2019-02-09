//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/SectionBuilders/Objects.h"
#include "Project/DocumentManager.h"
#include "Project/ImageDocuments.h"
#include "Project/MapDocuments.h"
#include "Graphics/GraphicsMode.h"
#include "Graphics/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Objects::Objects()
: SectionBuilder("Objects")
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Objects::~Objects()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Objects::Execute()
{
    const auto& dm = theDocumentManager;
    // get the objects in the map
    auto mapDoc = dynamic_cast<TiledMapDocument*>(dm.Get("Map", "Tiled", "Tile Map"));
    assert(mapDoc != nullptr);
    const auto& wi = theDocumentManager.ProjectConfig()->Window;
    auto tileSize = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[itTile].Minimum;
    auto wPt = TPoint(wi.X * tileSize.cx, wi.Y * tileSize.cy);
    auto objectsInMap = mapDoc->Get(itObject);
    // get the list of object images
    DocumentList images;
    dm.GetAllOfType("Image", images);
    for (auto image : images)
    {
        // TODO: Add support for big images
        auto object = dynamic_cast<ObjectDocument*>(image);
        if (object != nullptr)
        {
            String line = "DEFINEOBJECT ";
            const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
            const auto& gm = (*(mc.GraphicsMode()));
            // make an image canvas
            auto image = std::make_unique<Agdx::Image>(object, gm);
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
            auto roomIndex = object->State == osRoom ? ((ObjectDocument*)object)->RoomIndex : (object->State == osDisabled ? 254 : 255);
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

