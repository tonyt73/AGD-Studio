//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "AgdImporter.h"
#include "Parser.h"
#include "Services/File.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/Controls.h"
#include "Project/Documents/Images.h"
#include "Project/Documents/Text.h"
#include "Project/Documents/Window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Importer;
//---------------------------------------------------------------------------
__fastcall AgdImporter::AgdImporter()
{
}
//---------------------------------------------------------------------------
bool __fastcall AgdImporter::CanConvert(const String& file)
{
    return (Services::File::Extension(file) == ".agd");
}
//---------------------------------------------------------------------------
String __fastcall AgdImporter::GetMachine(const String& file)
{
    // look through the agd file and find a DEFINEBLOCK definition
    // the number of bytes determines the machine type:
    //   8 - ZX Spectrum
    //  16 - Timex/Next
    //  24 - Amstrad CPC

    // Load the file
    auto lines = Services::File::ReadLines(file);
    String data = "";
    auto machine = "";

    for (auto line : lines) {
        auto ll = line.LowerCase().Trim();

        if (ll.Pos("defineblock") > 0) {
            // start collecting the data
            data = ".";
            ll = ".";
        }
        if (data != "") {
            if (ll != "") {
                ll = StringReplace(ll, ".", "" , TReplaceFlags() << rfReplaceAll);
                ll = StringReplace(ll, " ", ",", TReplaceFlags() << rfReplaceAll);
                data += "," + ll;
            } else {
                // process the data collected
                data = StringReplace(data, ".,,", "", TReplaceFlags() << rfReplaceAll);
                auto tokens = SplitString(data, ',');
                auto count = tokens.size();
                // default to ZX Spectrum (most common AGD project type)
                switch (count) {
                    case 16: // ZX Spectrum Next/Timex
                        machine = "ZX Spectrum 256x192 ULA+";
                        return machine;
                    case 24: // Amstrad CPC
                        machine = "Amstrad CPC 160x200 16 Colour";
                        return machine;
                    case  9: // ZX Spectrum 48K/128K
                    default:
                        machine = "ZX Spectrum 256x192 16 Colour";
                        return machine;
                }
            }
        }
    }

    return machine;
}
//---------------------------------------------------------------------------
bool __fastcall AgdImporter::Convert(const String& file)
{
    Parser parser;
    if (parser.Parse(file, theDocumentManager.ProjectConfig()->MachineConfiguration().Name)) {
        // convert contents to AGDS documents
        return true;
    }
    return false;
 }
 //---------------------------------------------------------------------------

