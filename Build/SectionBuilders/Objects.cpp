//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/SectionBuilders/Objects.h"
#include "Project/DocumentManager.h"
#include "Project/ImageDocuments.h"
#include "Graphics/GraphicsMode.h"
#include "Graphics/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Objects::Objects()
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
                // extract the image colour and remove the last 4 bytes from the data
                line += IntToStr(data.back()) + " ";
                // remove the attributes
                data.pop_back();
                data.pop_back();
                data.pop_back();
                data.pop_back();
            }
            // add the room
            line += IntToStr(object->Room) + " ";
            // TODO: Get y/x for the obejct from the map?
            line += IntToStr(0) + " " + IntToStr(0) + " ";
            // export the machine graphics data
            for (auto byte : data)
            {
                line += IntToStr(byte) + " ";
            }
            AddLine(line);
            LineBreak();
        }
    }

    // no objects is ok
    Success();
}
//---------------------------------------------------------------------------

