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
    // get the number of unique tiles
    auto uniqueTiles = theDocumentManager.MapUniqueTileIndexes();
    if (uniqueTiles.size() < 256) {
        const auto& is = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile].Minimum;
        for (auto tile : uniqueTiles) {
            // we'll need to keep track of the tiles made to remove duplicates (screen data will also need to do this)
            String line = "DEFINEBLOCK ";
            line += g_BlockTypes[tile.BlockType];
            AddLine(line);
            line = "            ";
            // export the machine graphics data
            for (auto byte : enumerate(tile.Data)) {
                line += IntToStr(byte.item) + " ";
                if ((byte.index + 1) % is.cx == 0) {
                    line += "\r\n            ";
                }
            }
            AddLine(line);
            LineBreak();
        }
        // no Tiles is ok
        Success();
    } else {
        Failure("The number of unique tiles (" + IntToStr((int)uniqueTiles.size()) + ") exceeds 256.");
    }
}
//---------------------------------------------------------------------------

