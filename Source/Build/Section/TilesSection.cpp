//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "TilesSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/BaseImage.h"
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
    Project::DocumentList images;
    theDocumentManager.GetAllOfType("Image", images);
    for (auto image : images) {
        // TODO 5 -cBuild: Add support for big images
        const auto imgDoc = static_cast<Project::ImageDocument*>(image);
        if (imgDoc->ImageType == Visuals::itTile) {
            // make an image canvas
            const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
            const auto& gm = *mc.GraphicsMode();
            auto visualImage = std::make_unique<Visuals::Image>(imgDoc, gm);
            visualImage->ChangeFrame(0);
            const auto& is = mc.ImageSizing[imgDoc->ImageType].Minimum;
            // if tile is oversized, then break it into normal tile sizes. Happily this works for normal size tiles as well.
            for (int y = 0; y < imgDoc->Width / is.cy; y++) {
                for (int x = 0; x < imgDoc->Height / is.cx; x++) {
                    auto data = visualImage->GetExportNativeFormat(TRect(x, y, is.cx, is.cy));
                    // we'll need to keep track of the tiles made to remove duplicates (screen data will also need to do this)
                    String line = "DEFINEBLOCK ";
                    line += g_BlockTypes[StrToInt(imgDoc->GetLayer("blocktype"))];
                    AddLine(line);
                    line = "            ";
                    // export the machine graphics data
                    for (auto byte : enumerate(data)) {
                        line += IntToStr(byte.item) + " ";
                        if (byte.index % is.cx == 0) {
                            line += "\r\n            ";
                        }
                    }
                    AddLine(line);
                    LineBreak();
                }
            }
        }
    }

    // no Tiles is ok
    Success();
}
//---------------------------------------------------------------------------

