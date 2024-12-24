//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "SpritesSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/Sprite.h"
#include "Visuals/GraphicsMode.h"
#include "Visuals/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall SpritesSection::SpritesSection()
: Section("Sprites")
{
}
//---------------------------------------------------------------------------
__fastcall SpritesSection::~SpritesSection()
{
}
//---------------------------------------------------------------------------
void __fastcall SpritesSection::Execute()
{
    const auto& dm = theDocumentManager;
    auto imgSize = dm.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itSprite].Minimum;
    Project::DocumentList images;
    dm.GetAllOfType("Image", images);
    for (auto image : images) {
        auto sprite = dynamic_cast<Project::SpriteDocument*>(image);
        if (sprite != nullptr) {
            String line = "DEFINESPRITE " + UIntToStr(sprite->Frames) + " ";
            AddLine(line);
            const auto& gm = (*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()));
            auto gfx = std::make_unique<Visuals::Image>(sprite, gm);
            for (auto fi = 0; fi < sprite->Frames; fi++) {
                line = "             ";
                gfx->ChangeFrame(fi);
                auto data = gfx->GetExportNativeFormat();
                // export the machine graphics data
                for (auto byte : enumerate(data)) {
                    line += IntToStr(byte.item) + " ";
                    if (static_cast<long>(byte.index + 1) % imgSize.Width == 0) {
                        line += "\r\n             ";
                    }
                }
                AddLine(line);
            }
            LineBreak();
        }
    }

    // No sprites is ok? Is it really? Shouldn't we have at least 1 sprite?
    Success();
}
//---------------------------------------------------------------------------

