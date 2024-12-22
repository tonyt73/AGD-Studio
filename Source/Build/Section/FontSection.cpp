//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "FontSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/CharacterSet.h"
#include "Visuals/GraphicsMode.h"
#include "Visuals/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Build;
//---------------------------------------------------------------------------
__fastcall FontSection::FontSection()
: Section("Font")
{
}
//---------------------------------------------------------------------------
__fastcall FontSection::~FontSection()
{
}
//---------------------------------------------------------------------------
void __fastcall FontSection::Execute()
{
    const auto& dm = theDocumentManager;
    auto Font = dynamic_cast<Project::CharacterSetDocument*>(dm.Get("Image", "Character Set", "Game Font"));
    if (Font != nullptr)
    {
        if (Font->Frames == 96)
        {
            const auto& gm = (*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()));
            // make an image canvas
            auto image = std::make_unique<Visuals::Image>(Font, gm);
            String line = "DEFINEFONT ";
            for (auto i = 0; i < Font->Frames; i++)
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
            Failure("Character set does not have the correct number of characters (frames). It has " + UIntToStr(Font->Frames) + " when it needs 96");
            return;
        }
    }

    // no Font is ok
    Success();
}
//---------------------------------------------------------------------------

