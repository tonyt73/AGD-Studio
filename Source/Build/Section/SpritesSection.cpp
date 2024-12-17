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
    auto imgSize = dm.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
    Project::DocumentList images;
    dm.GetAllOfType("Image", images);
    for (auto image : images)
    {
        // TODO: Add support for big images
        auto sprite = dynamic_cast<Project::SpriteDocument*>(image);
        if (sprite != nullptr)
        {
            String line = "DEFINESPRITE " + IntToStr(sprite->Frames) + " ";
            AddLine(line);
            const auto& gm = (*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()));
            auto image = std::make_unique<Visuals::Image>(sprite, gm);
            for (auto i = 0; i < sprite->Frames; i++)
            {
                line = "             ";
                image->ChangeFrame(i);
                auto data = image->GetExportNativeFormat();
                // export the machine graphics data
                auto w = 0;
                for (auto byte : data)
                {
                    line += IntToStr(byte) + " ";
                    if (++w % imgSize.Width == 0)
                    {
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

