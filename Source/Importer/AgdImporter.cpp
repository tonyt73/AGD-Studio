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
: m_Blocks(0)
, m_Objects(0)
, m_Sprites(0)
, m_Screens(0)
, m_FontCharacter(0)
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
//    // Load the file
//    auto lines = Services::File::ReadLines(file);
//    const auto& machineConfig = theDocumentManager.ProjectConfig()->MachineConfiguration();
//
//    try {
//        String data = "";
//        for (auto line : lines) {
//            // find image marker
//            auto tline = line + "\r\n";
//            auto lline = tline.LowerCase();
//            // remove comments
//            auto cPos = tline.Pos(";");
//            if (cPos > 0) {
//                tline = tline.SubString(1, cPos - 1);
//            }
//            if (tline.Length() > 0) {
//                // process the line
//                if (lline.Pos("define") > 0 || lline.Pos("map") > 0 || lline.Pos("event")) {
//                    if (lline.Pos("endmap") == 1) {
//                        // capture the entire map
//                        ConvertMap(machineConfig, data);
//                        data = "";
//                    } else {
//                        if (data.Length() > 0) {
//                            // convert data
//                            ConvertData(machineConfig, data);
//                        }
//                    }
//                    // defining something
//                    data = tline;
//                } else {
//                    // collect all the current data for the definition
//                    data += tline;
//                }
//            }
//        }
//    } catch (...) {
//        //g_ErrorReporter.Add("Error: Exception caught while processing file. [" + file + "]");
//        return false;
//    }

//    return true;
 }
//---------------------------------------------------------------------------
String __fastcall AgdImporter::PreProcess(const String& data) const
{
    String line;
    auto sPos = data.Pos(' ');
    auto tPos = data.Pos('\t');
    try {
        sPos = sPos != 0 && tPos != 0 ? std::min(sPos, tPos) : (sPos == 0 ? tPos : sPos);
        // remove the define/map/endmap statement
        line = data.SubString(sPos, data.Length()).Trim();
        // replace all newlines + tabs with space
        int rPos, nPos;
        do {
            rPos = line.Pos("\r");
            if (rPos > 0) {
                line = line.SubString(1, rPos - 1) + + " " + line.SubString(rPos + 1, line.Length());
            }
            nPos = line.Pos("\n");
            if (nPos > 0) {
                line = line.SubString(1, nPos - 1) + + " " + line.SubString(nPos + 1, line.Length());
            }
            tPos = line.Pos("\t");
            if (tPos > 0) {
                line = line.SubString(1, tPos - 1) + " " + line.SubString(tPos + 1, line.Length());
            }
        } while (rPos != 0 || nPos != 0 || tPos != 0);
    } catch (...) {
        //g_ErrorReporter.Add("Error: Exception caught while pre-processing white space");
        throw;
    }
    // change ',' to ' '
    for (auto i = 1; i <= line.Length(); i++) {
        if (line[i] == ',') {
            line[i] = ' ';
        }
    }
    // all data should now be on 1 line
    // convert hex to decimal
    try
    {
        int hPos = 0;
        do {
            hPos = line.Pos("$");
            if (hPos > 0) {
                auto l1 = line.SubString(1, hPos - 1).Trim();
                auto l2 = line.SubString(hPos + 1, line.Length());
                auto l3 = String();
                sPos    = l2.Pos(' ');
                if (sPos > 0) {
                    l3 = l2.SubString(sPos, l2.Length()).Trim();
                    l2 = l2.SubString(1, sPos).Trim();
                }
                auto value = StrToInt("0x" + l2);
                line = l1 + " " + IntToStr(value) + " " + l3;
            }
        } while (hPos != 0);
    } catch (...) {
        //g_ErrorReporter.Add("Error: Exception caught while pre-processing hex into decimal");
        throw;
    }
    return line.Trim();
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertData(const Project::MachineConfig& machineConfig, const String& data)
{
    try {
        auto ld = data.LowerCase();
        if (ld.Pos("event ") == 1) {
            //m_Events.push_back(data);
        }
        else if (ld.Pos("definemessages") == 0) {
            auto pdata = PreProcess(data);
            if (ld.Pos("defineblock") == 1) {
                ConvertBlock(machineConfig, pdata);
            }
            else if (ld.Pos("defineobject") == 1) {
                ConvertObject(machineConfig, pdata);
            }
            else if (ld.Pos("definesprite") == 1) {
                ConvertSprite(machineConfig, pdata, 16);
            }
            else if (ld.Pos("definefont") == 1) {
                ConvertFont(machineConfig, pdata);
            }
            else if (ld.Pos("definewindow") == 1) {
                ConvertWindow(machineConfig, pdata);
            }
            else if (ld.Pos("definescreen") == 1) {
                ConvertScreen(machineConfig, pdata);
            }
            else if (ld.Pos("definecontrols") == 1) {
                ConvertControls(machineConfig, pdata);
            }
            else if (ld.Pos("definejump") == 1) {
                ConvertJumpTable(machineConfig, pdata);
            }
        } else {
            ConvertMessages(data);
        }
    } catch (...) {
        //g_ErrorReporter.Add("Error: Exception caught while converting data to valid AGD type");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertJumpTable(const Project::MachineConfig& machineConfig, const String& data)
{
    // convert the data
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertScreen(const Project::MachineConfig& machineConfig, const String& data)
{
    // convert the data
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertControls(const Project::MachineConfig& machineConfig, const String& data)
{
    auto keys = SplitString(StringReplace(data, "'", "", TReplaceFlags()), " ");
    auto dirKeys = machineConfig.Controls.Directions;
    auto firKeys = machineConfig.Controls.Fires;
    auto optKeys = machineConfig.Controls.Options;
    // convert the data
    auto keysDoc = dynamic_cast<Project::ControlsDocument*>(theDocumentManager.Get("Controls", "List", "Controls"));
    if (keysDoc != nullptr) {
        // set direction keys
        if (keys.size() >= dirKeys) {
            for (int key = 0; key < dirKeys; key++) {
                auto i = key;
                unsigned char iKey = StrToIntDef(keys[i], keys[i][1]);
                // key value is an ascii code for the machine
                keysDoc->SetAsciiCode((Project::eAgdKey)key, (unsigned char)iKey);
            }
            InformationMessage("[Importer] " + IntToStr(dirKeys) + " Direction Keys imported");
        }
        // set fire keys
        if (keys.size() >= dirKeys + firKeys) {
            for (int key = 0; key < firKeys; key++) {
                auto i = key + dirKeys;
                unsigned char iKey = StrToIntDef(keys[i], keys[i][1]);
                // key value is an ascii code for the machine
                keysDoc->SetAsciiCode((Project::eAgdKey)(Project::keyOption1 + key), (unsigned char)iKey);
            }
            InformationMessage("[Importer] " + IntToStr(firKeys) + " Fire Keys imported");
        }
        // set option keys
        if (keys.size() >= dirKeys + firKeys + optKeys) {
            for (int key = 0; key < optKeys; key++) {
                auto i = key + dirKeys + firKeys;
                unsigned char iKey = StrToIntDef(keys[i], keys[i][1]);
                // key value is an ascii code for the machine
                keysDoc->SetAsciiCode((Project::eAgdKey)(Project::keyOption1 + key), (unsigned char)iKey);
            }
            InformationMessage("[Importer] " + IntToStr(optKeys) + " Options Keys imported");
        } else {
            keysDoc->SetAsciiCode(Project::keyOption1, '1');
            keysDoc->SetAsciiCode(Project::keyOption2, '2');
            keysDoc->SetAsciiCode(Project::keyOption3, '3');
            keysDoc->SetAsciiCode(Project::keyOption4, '4');
            WarningMessage("[Importer] No Options Keys imported, set to 1,2,3,4");
        }
    } else {
        // TODO: failed to retrieve the controls document
        ErrorMessage("[Importer] Failed to convert controls. Couldn't create a Controls document.");
    }
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertMap(const Project::MachineConfig& machineConfig, const String& data)
{
    try
    {
        auto pdata = PreProcess(data);
        //m_Map      = std::make_unique <Map> (pdata);
    }
    catch (...)
    {
        //g_ErrorReporter.Add("Error: Exception caught while converting Map data");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertEventCode()
{
    try
    {
//        auto lines = SplitString(m_EventCode, "\n");
//        String content;
//        for (auto line : lines)
//        {
//            line += "\n";
//            if (line.SubString(1, 5).UpperCase() == "EVENT" && content != "")
//            {
//                m_Events.push_back(content);
//                content = "";
//            }
//            if (line.Trim() != "")
//            {
//                content += line;
//            }
//        }
//        m_Events.push_back(content);
    }
    catch (...)
    {
        //g_ErrorReporter.Add("Error: Exception caught while converting Event code");
        throw;
    }
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertWindow(const Project::MachineConfig& machineConfig, const String& data)
{
    auto tokens = SplitString(data, " ");
    const auto wc = machineConfig.Window;
    auto windowDoc = dynamic_cast<Project::WindowDocument*>(theDocumentManager.Get("Window", "Definition", "Window"));
    if (tokens.size() == 4) {
        auto wy = StrToInt(tokens[0]);
        auto wx = StrToInt(tokens[1]);
        auto wh = StrToInt(tokens[2]);
        auto ww = StrToInt(tokens[3]);
        if (windowDoc != nullptr) {
            if (wx < 0 || wx >= wc.Width || wx + ww > wc.Width) {
                wx = 0;
                ww = wc.Width;
            }
            if (wy < 0 || wy >= wc.Height || wy + wh > wc.Height) {
                wy = 0;
                wh = wc.Height;
            }
            TRect rect(wx, wy, ww, wh);
            windowDoc->Set(rect);
            InformationMessage("[Importer] Window imported");
        }
    } else {
        // Set window to full size
        TRect rect(0, 0, wc.Width, wc.Height);
        windowDoc->Set(rect);
        WarningMessage("[Importer] Window set to screen size. Failed to read the correct number of Window parameters.");
    }
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertToImage(const Project::MachineConfig& machineConfig, const String& data, Visuals::ImageTypes type, int instance, int frames)
{
    auto adata = SplitString(data.Trim(), " ");
    String img = "";
    for (auto value : adata) {
        if (value.Trim() != "") {
            auto d = (unsigned char)StrToIntDef(value, 0);
            img += IntToHex(d);
        }
    }

    auto typeName = ImageTypeName(type);
    auto name = typeName + " " + IntToStr(instance);
    auto imgDoc = dynamic_cast<Project::ImageDocument*>(theDocumentManager.Add("Image", typeName, name));

    if (imgDoc != nullptr) {
        // Validate image is the correct size
        const auto iw = machineConfig.ImageSizing[type].Minimum.Width;
        const auto ih = machineConfig.ImageSizing[type].Minimum.Height;

        // number of bytes the pixels of w x h image would take up
        const auto pb = machineConfig.GraphicsMode()->GetSizeOfPixels(iw, ih) * frames;
        // number of bytes the attributes of w x h image would take up
        const auto ab = machineConfig.GraphicsMode()->GetSizeOfAttributes(iw, ih) * frames;
        // number of bytes the imported image is using
        const auto il = img.Length() / 2;

        // set the image frames
        int span = (il / frames) * 2;
        for (int frame = 0; frame < frames; frame++) {
            auto frameImg = img.SubString(frame * span, frame * span + span - 1);
            imgDoc->Frame[frame] = frameImg;
        }
        InformationMessage("[Importer] " + name + " imported with " + IntToStr(frames) + " frames");
    } else {
        ErrorMessage("[Importer] Failed to create an Image document for " + name);
    }
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertBlock(const Project::MachineConfig& machineConfig, const String& data)
{
    // convert the data
    // get the type
    auto tPos    = data.Pos(" ");
    auto subType = data.SubString(1, tPos - 1);
    auto idata   = data.SubString(tPos + 1, data.Length());
    ConvertToImage(machineConfig, idata, Visuals::itTile, m_Blocks++, 1);
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertObject(const Project::MachineConfig& machineConfig, const String& data)
{
    // convert the data
    // get the type
    auto tPos   = data.Pos(" ");
    auto params = SplitString(data.SubString(1, tPos - 1), " ");
    auto idata  = data.SubString(tPos + 1, data.Length());
    ConvertToImage(machineConfig, idata, Visuals::itObject, m_Objects++, 1);
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertSprite(const Project::MachineConfig& machineConfig, const String& data, unsigned int spriteHeight)
{
    // convert the data
    // get the number of frames
    auto tPos   = data.Pos(" ");
    auto frames = StrToIntDef(data.SubString(1, tPos - 1).Trim(), 1);
    auto idata  = data.SubString(tPos + 1, data.Length());
    ConvertToImage(machineConfig, idata, Visuals::itSprite, m_Sprites++, frames);
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertFont(const Project::MachineConfig& machineConfig, const String& data)
{
    // convert the data
    //m_Font.push_back(std::move(std::make_unique <ImageFont> (data)));
}
//---------------------------------------------------------------------------
void __fastcall AgdImporter::ConvertMessages(const String& data)
{
    auto mdata = data;
    // convert the data
    if (data.Pos("definemessages ")) {
        auto mPos = data.Pos(" ");
        mdata  = data.SubString(mPos + 1, data.Length());
    }
    auto messages = SplitString(mdata, "\"");
    auto msgsDoc = dynamic_cast<Project::MessageDocument*>(theDocumentManager.Get("Text", "Messages", "Messages"));
    if (msgsDoc != nullptr) {
        for (auto message : messages) {
            message = message.Trim();
            if (message != "") {
                msgsDoc->Add(message);
            }
        }
    }
}
 //---------------------------------------------------------------------------

