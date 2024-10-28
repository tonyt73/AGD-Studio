//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "TilesBuilder.h"
#include "Project/DocumentManager.h"
#include "Project/TileDocument.h"
#include "Visuals/GraphicsMode.h"
#include "Visuals/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
const String BlockTypes[] = { "EMPTYBLOCK", "PLATFORMBLOCK", "WALLBLOCK", "LADDERBLOCK", "FODDERBLOCK", "DEADLYBLOCK", "CUSTOMBLOCK" };
//---------------------------------------------------------------------------
__fastcall TilesBuilder::TilesBuilder()
: SectionBuilder("Tiles")
{
}
//---------------------------------------------------------------------------
__fastcall TilesBuilder::~TilesBuilder()
{
}
//---------------------------------------------------------------------------
void __fastcall TilesBuilder::Execute()
{
    const auto& dm = theDocumentManager;
    Project::DocumentList images;
    dm.GetAllOfType("Image", images);
    for (auto image : images)
    {
        // TODO: Add support for big images
        auto tile = dynamic_cast<Project::TileDocument*>(image);
        if (tile != nullptr)
        {
            String line = "DEFINEBLOCK ";
            line += BlockTypes[StrToInt(tile->GetLayer("blocktype"))];
            AddLine(line);
            const auto& gm = (*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()));
            // make an image canvas
            auto image = std::make_unique<Visuals::Image>(tile, gm);
            image->ChangeFrame(0);
            auto data = image->GetExportNativeFormat();
            line = "            ";
            // export the machine graphics data
            auto i = 0;
            for (auto byte : data)
            {
                line += IntToStr(byte) + " ";
                if (++i == 8)
                {
                    line += "\r\n            ";
                }
            }
            AddLine(line);
            LineBreak();
        }
    }

    // no TilesBuilder is ok
    Success();
}
//---------------------------------------------------------------------------

