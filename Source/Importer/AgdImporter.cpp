//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "AgdImporter.h"
#include <iterator>
#include "Services/File.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/BaseImage.h"
#include "Project/Documents/CharacterSet.h"
#include "Project/Documents/Controls.h"
#include "Project/Documents/FileDefinitions.h"
#include "Project/Documents/JumpTable.h"
#include "Project/Documents/Object.h"
#include "Project/Documents/Sprite.h"
#include "Project/Documents/Text.h"
#include "Project/Documents/Tile.h"
#include "Project/Documents/Window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Importer;
//---------------------------------------------------------------------------
AgdImporter::AgdImporter()
{
}
//---------------------------------------------------------------------------
int AgdImporter::GetNum(const String& var, const String& subVar, int index)
{
    auto it = m_Parser.Variables[var][subVar].begin();
    auto end = m_Parser.Variables[var][subVar].end();
    for (; index && it != end ; index--) it++;
    if (it != end) {
        auto str = *it;
        auto num = StrToIntDef(str, -1);
        if (num == -1) {
            if (str[1] == '\'') {   // convert ascii character to integer
                return str[2];
            }
        } else {
            return num;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
bool AgdImporter::Convert(const String& file)
{
    bool result = false;
    if (m_Parser.Parse(file, theDocumentManager.ProjectConfig()->MachineConfiguration().Name)) {
        // convert import contents to AGD Studio documents
        result  = UpdateWindow();
        result &= UpdateControls();
        result &= UpdateJumpTable();
        result &= UpdateFont();
        result &= AddImages("blocks" , "Tile"  );
        result &= AddImages("objects", "Object");
        result &= AddImages("sprites", "Sprite");
        result &= AddMessages();
        result &= AddEvents();
        result &= AddScreens();
        result &= AddMap();
    }
    return result;
 }
//---------------------------------------------------------------------------
bool AgdImporter::UpdateWindow()
{
    if (m_Parser.hasVariable("window")) {
        auto doc = dynamic_cast<Project::WindowDocument*>(theDocumentManager.Get("Window", "Definition", "Window"));
        auto x = GetNum("window", "window.x");
        auto y = GetNum("window", "window.y");
        auto w = GetNum("window", "window.width");
        auto h = GetNum("window", "window.height");
        TRect rect(x, y, x + w, y + h);
        doc->Set(rect);
    }
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::UpdateControls()
{
    if (m_Parser.hasVariable("controlset")) {
        auto doc = dynamic_cast<Project::ControlsDocument*>(theDocumentManager.Get("Controls", "List", "Controls"));
        doc->SetAsciiCode(Project::keyUp     , GetNum("controlset", "key.up"     ));
        doc->SetAsciiCode(Project::keyDown   , GetNum("controlset", "key.down"   ));
        doc->SetAsciiCode(Project::keyLeft   , GetNum("controlset", "key.left"   ));
        doc->SetAsciiCode(Project::keyRight  , GetNum("controlset", "key.right"  ));
        doc->SetAsciiCode(Project::keyFire1  , GetNum("controlset", "key.fire1"  ));
        doc->SetAsciiCode(Project::keyFire2  , GetNum("controlset", "key.fire2"  ));
        doc->SetAsciiCode(Project::keyFire3  , GetNum("controlset", "key.fire3"  ));
        doc->SetAsciiCode(Project::keyOption1, GetNum("controlset", "key.option1"));
        doc->SetAsciiCode(Project::keyOption2, GetNum("controlset", "key.option2"));
        doc->SetAsciiCode(Project::keyOption3, GetNum("controlset", "key.option3"));
        doc->SetAsciiCode(Project::keyOption4, GetNum("controlset", "key.option4"));
    } else {
        WarningMessage("No Controls found during the import process");
    }
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::UpdateJumpTable()
{
    if (m_Parser.hasVariable("jumptable")) {
        auto doc = dynamic_cast<Project::JumpTableDocument*>(theDocumentManager.Add("Jump", "Table", "JumpTable"));
        for (int step = 0; step < doc->Count; step++) {
            doc->SetStep(step, GetNum("jumptable", "jump.table", step));
        }
    }
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::UpdateFont()
{
    if (m_Parser.hasVariable("font")) {
        auto doc = dynamic_cast<Project::CharacterSetDocument*>(theDocumentManager.Add("Image", "Character Set", "Game Font"));
        // check font size is the same as parsed
        // get the image byte values and convert to hex
        int bpp = theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()->BitsPerPixel;
        int bytesPerFrame = (doc->Width * doc->Height) / (8 * bpp);
        int bytesRequired = bytesPerFrame * doc->Frames;
        int bytes = m_Parser.Variables["font"]["characters"].size();
        if (bytesRequired == bytes) {
            for (auto f = 0; f < doc->Frames; f++) {
                // get bytes for each frame
                String frame = "";
                for (auto i = 0; i < bytesPerFrame; i++) {
                    frame += IntToHex(GetNum("font", "characters", bytesPerFrame * f + i), 2);
                }
                doc->Frame[f] = frame;
            }
        } else {
            ErrorMessage("[Importer] Incorrect number of font bytes found. Require " + IntToStr(bytesRequired) + "bytes, but got " + IntToStr(bytes) + " bytes.");
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::AddImages(const String& name, const String& imgType)
{
    int vars = m_Parser.GetVarCount(name);
    if (vars > 0) {
        auto gm = theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode();
        int bpp = gm->BitsPerPixel;
        for (auto obj = 1; obj <= vars; obj++) {
            auto objName = imgType + " " + IntToStr(obj);
            auto varName = name + m_Parser.PadNum(obj);
            auto doc = dynamic_cast<Project::ImageDocument*>(theDocumentManager.Add("Image", imgType, objName));
            int bytesPerFrame = (doc->Width * doc->Height) / (8 * bpp);
            int bytes = m_Parser.Variables[varName]["image"].size();
            String frame = "";
            if (bytes >= bytesPerFrame) {
                for (auto f = 0; f < doc->Frames; f++) {
                    frame = "";
                    // get bytes for each frame
                    for (auto i = 0; i < bytes; i++) {
                        frame += IntToHex(GetNum(varName, "image", bytesPerFrame * f + i), 2);
                    }
                    doc->Frame[f] = frame;
                }
            } else {
                ErrorMessage("[Importer] Incorrect number of " + imgType + " bytes found. Require " + IntToStr(bytesPerFrame) + "bytes, but got " + IntToStr(bytes) + " bytes.");
                return false;
            }
            if (imgType == "Tile") {
                // process block type
                dynamic_cast<Project::TileDocument*>(doc)->SetType(m_Parser.Variables[varName]["block.type"].front());
            } else if (imgType == "Object") {
                // process room info
                auto obj = dynamic_cast<Project::ObjectDocument*>(doc);
                obj->RoomIndex = StrToInt(m_Parser.Variables[varName]["object.room"].front());
                obj->Position = TPoint(StrToInt(m_Parser.Variables[varName]["object.x"].front()), StrToInt(m_Parser.Variables[varName]["object.y"].front()));
                if (m_Parser.Variables[varName].count("object.colour") == 1) {
                    // change the colour of the object
                    if (gm->TypeOfBuffer == Visuals::BufferType::btAttribute) {
                        String colour = "";
                        for (int x = 0; x < doc->Width / (8 / bpp); x++) {
                            for (int y = 0; y < doc->Height / (8 / bpp); y++) {
                                colour += IntToHex(StrToInt(m_Parser.Variables[varName]["object.colour"].front()), 2);
                            }
                        }
                        frame = doc->Frame[0];
                        frame = frame.SubString(1, bytesPerFrame * 2) + colour;
                         doc->Frame[0] = frame;
                    } else {
                        WarningMessage("[Importer] The 'object.colour' property was found during the import process, but the graphics mode (" + gm->Name + ") does not support attributes.");
                    }
                }
            }
        }
    }
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::AddMessages()
{
    int vars = m_Parser.GetVarCount("messagelist");
    if (vars > 0) {
        auto doc = dynamic_cast<Project::TextDocument*>(theDocumentManager.Add("Text", "Messages", "Messages"));
        for (auto msg : m_Parser.Variables["messagelist"]["message"]) {
            auto line = StringReplace(msg, "\"", "", TReplaceFlags() << rfReplaceAll).Trim();
            if (line != "") {
                doc->Add(line+"\r\n");
            }
        }
    }
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::AddEvents()
{
    int vars = m_Parser.GetVarCount("events");
    if (vars > 0) {
        auto definitions = std::make_unique<Project::FileDefinitions>();
        for (const auto& definition : definitions->GetDefinitions())
        {
            if (definition.Type == "Event") {
                auto section = definition.Section.LowerCase();
                // the event that matches this section
                for (auto event = 1; event <= vars; event++) {
                    auto varName = "events" + m_Parser.PadNum(event);
                    auto eventName = m_Parser.Variables[varName]["event.name"].front().LowerCase();
                    if (section.Pos(eventName) > 0) {
                        // add the event lines into the event document
                        auto doc = dynamic_cast<Project::EventDocument*>(theDocumentManager.Get("Text", "Event", definition.Filename));
                        doc->Add("\r\n");
                        doc->Add("\r\n");
                        for (auto line : m_Parser.Variables[varName]["event.lines"]) {
                            doc->Add(line + "\r\n");
                        }
                    }
                }
            }
        }
    } else {
        ErrorMessage("No game events found during the import process");
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::AddScreens()
{
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::AddMap()
{
    // define map with screens/rooms including sprite positions
    // adds objects to map
    return true;
}
//---------------------------------------------------------------------------

