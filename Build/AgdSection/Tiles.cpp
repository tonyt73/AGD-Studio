//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
#include "Build/AgdSection/Tiles.h"
#include "Project/DocumentManager.h"
#include "Project/TileDocument.h"
#include "Graphics/GraphicsMode.h"
#include "Graphics/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const String BlockTypes[] = { "EMPTYBLOCK", "PLATFORMBLOCK", "WALLBLOCK", "LADDERBLOCK", "FODDERBLOCK", "DEADLYBLOCK", "CUSTOMBLOCK" };
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Tiles::Tiles()
: SectionBuilder("Tiles")
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Tiles::~Tiles()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Tiles::Execute()
{
    const auto& dm = theDocumentManager;
    DocumentList images;
    dm.GetAllOfType("Image", images);
    for (auto image : images)
    {
        // TODO: Add support for big images
        auto tile = dynamic_cast<TileDocument*>(image);
        if (tile != nullptr)
        {
            String line = "DEFINEBLOCK ";
            line += BlockTypes[StrToInt(tile->GetLayer("blocktype"))];
            AddLine(line);
            const auto& gm = (*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()));
            // make an image canvas
            auto image = std::make_unique<Agdx::Image>(tile, gm);
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

    // no tiles is ok
    Success();
}
//---------------------------------------------------------------------------

