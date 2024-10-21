//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "FontBuilder.h"
#include "Project/DocumentManager.h"
#include "Project/CharacterSetDocument.h"
#include "Visuals/GraphicsMode.h"
#include "Visuals/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall FontBuilder::FontBuilder()
: SectionBuilder("FontBuilder")
{
}
//---------------------------------------------------------------------------
__fastcall FontBuilder::~FontBuilder()
{
}
//---------------------------------------------------------------------------
void __fastcall FontBuilder::Execute()
{
    const auto& dm = theDocumentManager;
    auto FontBuilder = dynamic_cast<Project::CharacterSetDocument*>(dm.Get("Image", "Character Set", "Game FontBuilder"));
    if (FontBuilder != nullptr)
    {
        if (FontBuilder->Frames == 96)
        {
            const auto& gm = (*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()));
            // make an image canvas
            auto image = std::make_unique<Visuals::Image>(FontBuilder, gm);
            String line = "DEFINEFontBuilder ";
            for (auto i = 0; i < FontBuilder->Frames; i++)
            {
                // get the frame data in machine specific format
                image->ChangeFrame(i);
                auto data = image->GetExportNativeFormat();
                // export the machine graphics data
                for (auto byte : data)
                {
                    line += IntToStr(byte) + " ";
                }
                AddLine(line);
                line = "           ";
            }
            LineBreak();
        }
        else
        {
            Failure("Character set does not have the correct number of characters (frames). It has " + IntToStr(FontBuilder->Frames) + " when it needs 96");
            return;
        }
    }

    // no FontBuilder is ok
    Success();
}
//---------------------------------------------------------------------------

