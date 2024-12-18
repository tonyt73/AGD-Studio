//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "TilesSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/Tile.h"
#include "Visuals/BlockTypes.h"
#include "Visuals/GraphicsMode.h"
#include "Visuals/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall TilesSection::TilesSection()
: Section("Tiles")
{
}
//---------------------------------------------------------------------------
__fastcall TilesSection::~TilesSection()
{
}
//---------------------------------------------------------------------------
void __fastcall TilesSection::Execute()
{
    const auto& dm = theDocumentManager;
    auto imgSize = dm.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
    Project::DocumentList images;
    dm.GetAllOfType("Image", images);
    for (auto image : images) {
        //TODO 1 -cBuild: Add support for big images
        auto tile = dynamic_cast<Project::TileDocument*>(image);
        if (tile != nullptr) {
            String line = "DEFINEBLOCK ";
            line += g_BlockTypes[StrToInt(tile->GetLayer("blocktype"))];
            AddLine(line);
            const auto& gm = (*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()));
            // make an image canvas
            auto image = std::make_unique<Visuals::Image>(tile, gm);
            image->ChangeFrame(0);
            auto data = image->GetExportNativeFormat();
            line = "            ";
            // export the machine graphics data
            for (auto byte : enumerate(data)) {
                line += IntToStr(byte.item) + " ";
                if (byte.index % imgSize.Width == 0) {
                    line += "\r\n            ";
                }
            }
            AddLine(line);
            LineBreak();
        }
    }

    // no Tiles is ok
    Success();
}
//---------------------------------------------------------------------------

