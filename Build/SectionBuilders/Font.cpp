//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/SectionBuilders/Font.h"
#include "Project/DocumentManager.h"
#include "Project/ImageDocuments.h"
#include "Graphics/GraphicsMode.h"
#include "Graphics/Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Font::Font()
: SectionBuilder("Font")
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Font::~Font()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Font::Execute()
{
    const auto& dm = theDocumentManager;
    auto font = dynamic_cast<CharacterSetDocument*>(dm.Get("Image", "Character Set", "Game Font"));
    if (font != nullptr)
    {
        if (font->Frames == 96)
        {
            const auto& gm = (*(theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()));
            // make an image canvas
            auto image = std::make_unique<Agdx::Image>(font, gm);
            String line = "DEFINEFONT ";
            for (auto i = 0; i < font->Frames; i++)
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
            Failure("Character set does not have the correct number of characters (frames). It has " + IntToStr(font->Frames) + " when it needs 96");
            return;
        }
    }

    // no font is ok
    Success();
}
//---------------------------------------------------------------------------

