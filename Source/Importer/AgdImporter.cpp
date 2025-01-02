//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "AgdImporter.h"
#include "Services/File.h"
#include "Project/Documents/DocumentManager.h"
#include "Project/Documents/BaseImage.h"
#include "Project/Documents/CharacterSet.h"
#include "Project/Documents/Controls.h"
#include "Project/Documents/FileDefinitions.h"
#include "Project/Documents/JumpTable.h"
#include "Project/Documents/MapEntity.h"
#include "Project/Documents/Object.h"
#include "Project/Documents/Sprite.h"
#include "Project/Documents/Text.h"
#include "Project/Documents/Tile.h"
#include "Project/Documents/TiledMap.h"
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
    auto start = TDateTime::CurrentTime();
    InformationMessage("[AGD Importer] Parsing import file.");
    if (m_Parser.Parse(file, theDocumentManager.ProjectConfig()->MachineConfiguration().Name)) {
        auto name = Services::File::NameWithoutExtension(file);
        auto end = TDateTime::CurrentTime();
        auto ms = end - start;
        InformationMessage("[AGD Importer] Parsed '" + name + "' in " + IntToStr(static_cast<int>(ms)) + "ms");
        start = TDateTime::CurrentTime();
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
        result &= AddMap();
        end = TDateTime::CurrentTime();
        ms = end - start;
        InformationMessage("[AGD Importer] Parsed content conversion to documents took " + IntToStr(static_cast<int>(ms)) + "ms");
    }
    if (result) {
        InformationMessage("[AGD Importer] Import processed completed.");
    } else {
        ErrorMessage("[AGD Importer] Import processing failed.");
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
        m_Window = TRect(x, y, x + w, y + h);
        doc->SetRect(m_Window);
    }
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::UpdateControls()
{
    if (m_Parser.hasVariable("controlset")) {
        auto doc = dynamic_cast<Project::ControlsDocument*>(theDocumentManager.Get("Controls", "List", "Controls"));
        doc->SetAsciiCode(Project::keyUp     , static_cast<unsigned char>(GetNum("controlset", "key.up"     )));
        doc->SetAsciiCode(Project::keyDown   , static_cast<unsigned char>(GetNum("controlset", "key.down"   )));
        doc->SetAsciiCode(Project::keyLeft   , static_cast<unsigned char>(GetNum("controlset", "key.left"   )));
        doc->SetAsciiCode(Project::keyRight  , static_cast<unsigned char>(GetNum("controlset", "key.right"  )));
        doc->SetAsciiCode(Project::keyFire1  , static_cast<unsigned char>(GetNum("controlset", "key.fire1"  )));
        doc->SetAsciiCode(Project::keyFire2  , static_cast<unsigned char>(GetNum("controlset", "key.fire2"  )));
        doc->SetAsciiCode(Project::keyFire3  , static_cast<unsigned char>(GetNum("controlset", "key.fire3"  )));
        doc->SetAsciiCode(Project::keyOption1, static_cast<unsigned char>(GetNum("controlset", "key.option1")));
        doc->SetAsciiCode(Project::keyOption2, static_cast<unsigned char>(GetNum("controlset", "key.option2")));
        doc->SetAsciiCode(Project::keyOption3, static_cast<unsigned char>(GetNum("controlset", "key.option3")));
        doc->SetAsciiCode(Project::keyOption4, static_cast<unsigned char>(GetNum("controlset", "key.option4")));
    } else {
        WarningMessage("[AGD Importer] No Controls found during the import process");
    }
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::UpdateJumpTable()
{
    if (m_Parser.hasVariable("jumptable")) {
        auto doc = dynamic_cast<Project::JumpTableDocument*>(theDocumentManager.Add("Jump", "Table", "JumpTable"));
        for (unsigned char step = 0; step < doc->Count; step++) {
            doc->SetStep(step, GetNum("jumptable", "table", step));
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
        auto bpp = theDocumentManager.ProjectConfig()->MachineConfiguration().GraphicsMode()->BitsPerPixel;
        auto bytesPerFrame = static_cast<unsigned int>(doc->Width * doc->Height) / (8 * bpp);
        auto bytesRequired = bytesPerFrame * doc->Frames;
        auto bytes = m_Parser.Variables["font"]["characters"].size();
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
            ErrorMessage("[AGD Importer] Incorrect number of font bytes found. Require " + UIntToStr(bytesRequired) + "bytes, but got " + UIntToStr(bytes) + " bytes.");
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
        auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
        auto gm = mc.GraphicsMode();
        int bpp = gm->BitsPerPixel;
        for (auto obj = 1; obj <= vars; obj++) {
            auto objName = imgType + " " + IntToStr(obj);
            auto varName = name + m_Parser.PadNum(obj);
            auto doc = dynamic_cast<Project::ImageDocument*>(theDocumentManager.Add("Image", imgType, objName));
            auto bytesPerFrame = (doc->Width * doc->Height) / (8 * bpp);
            auto bytes = m_Parser.Variables[varName]["image"].size();
            String frame = "";
            auto frameCount = bytes / bytesPerFrame;
            if (bytes >= bytesPerFrame) {
                for (auto f = 0; f < frameCount; f++) {
                    frame = "";
                    // get bytes for each frame
                    for (auto i = 0; i < bytes; i++) {
                        frame += IntToHex(GetNum(varName, "image", bytesPerFrame * f + i), 2);
                    }
                    doc->Frame[f] = frame;
                }
            } else {
                ErrorMessage("[AGD Importer] Incorrect number of " + imgType + " bytes found. Require " + UIntToStr(bytesPerFrame) + "bytes, but got " + UIntToStr(bytes) + " bytes.");
                return false;
            }
            if (imgType == "Tile") {
                // process block type
                dynamic_cast<Project::TileDocument*>(doc)->SetType(m_Parser.Variables[varName]["type"].front());
            } else if (imgType == "Object") {
                // process room info
                auto objDoc = dynamic_cast<Project::ObjectDocument*>(doc);
                objDoc->RoomIndex = StrToInt(m_Parser.Variables[varName]["room"].front());
                objDoc->Position = TPoint(StrToInt(m_Parser.Variables[varName]["x"].front() - (m_Window.Left * mc.ImageSizing[Visuals::itTile].Minimum.Width)), StrToInt(m_Parser.Variables[varName]["y"].front() - (m_Window.Top * mc.ImageSizing[Visuals::itTile].Minimum.Height)));
                if (m_Parser.Variables[varName].count("colour") == 1) {
                    // change the colour of the object
                    if (gm->TypeOfBuffer == Visuals::BufferType::btAttribute) {
                        String colour = "";
                        for (int x = 0; x < objDoc->Width / (8 / bpp); x++) {
                            for (int y = 0; y < objDoc->Height / (8 / bpp); y++) {
                                colour += IntToHex(StrToInt(m_Parser.Variables[varName]["colour"].front()), 2);
                            }
                        }
                        frame = objDoc->Frame[0];
                        frame = frame.SubString(1, bytesPerFrame * 2) + colour;
                        objDoc->Frame[0] = frame;
                    } else {
                        WarningMessage("[AGD Importer] The 'object.colour' property was found during the import process, but the graphics mode (" + gm->Name + ") does not support attributes.");
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
    auto doc = dynamic_cast<Project::TextDocument*>(theDocumentManager.Add("Text", "Messages", "Messages"));
    doc->Add("\r\n");
    for (auto msg : m_Parser.Variables["messagelist"]["lines"]) {
        auto line = msg.Trim();
        if (line != "") {
            doc->Add(line+"\r\n");
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
                    auto eventName = m_Parser.Variables[varName]["name"].front().LowerCase();
                    if (section.Pos(" " + eventName) > 0) {
                        // add the event lines into the event document
                        auto doc = dynamic_cast<Project::EventDocument*>(theDocumentManager.Get("Text", "Event", definition.Filename));
                        doc->Add("\r\n");
                        doc->Add("\r\n");
                        auto lines = m_Parser.Variables[varName]["lines"];
                        for (auto line : lines) {
                            doc->Add(line + "\r\n");
                        }
                    }
                }
            }
        }
    } else {
        ErrorMessage("[AGD Importer] No game events found during the import process.");
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
bool AgdImporter::AddMap()
{
    // unset an empty map
    std::map<int, TPoint> mapIndexToPt;
    // read in the map indexes
    auto mapWidth = StrToIntDef(m_Parser.Variables["map"]["width"].front(), -1);
    auto mapSize = m_Parser.Variables["map"]["table"].size();
    auto mapHeight = mapSize / mapWidth;
    auto numSprites = static_cast<int>(m_Parser.VarCounts["sprites"]);
    TPoint scrPos;
    auto ssi = StrToIntDef(m_Parser.Variables["map"]["startscreen"].front(), -1);
    auto numScreens = 0;
    bool result = false;
    if (0 < mapSize && mapSize < Project::g_MaxRooms) {
        result = true;
        // set up the map indexes
        int mi = 0;
        for (auto value : m_Parser.Variables["map"]["table"]) {
            auto si = StrToIntDef(value, -1);
            if (si != -1 && si != Project::g_EmptyRoom) {
                auto sx = mi % mapWidth;
                auto sy = mi / mapWidth;
                mapIndexToPt[si] = TPoint(sx,sy);
                if (si == ssi) {
                    scrPos.x = sx;
                    scrPos.y = sy;
                }
                numScreens++;
            }
            mi++;
        }
        // now read the screens and convert the tile positions into map entity positions
        Project::MapEntityList entities;
        auto is = theDocumentManager.ProjectConfig()->MachineConfiguration().ImageSizing[Visuals::itTile];
        auto tx = is.Step.cx;
        auto ty = is.Step.cy;
        for (auto i = 0; i < numScreens; i++) {
            // add screen (si) tile entities to the map
            auto varName = "screens" + m_Parser.PadNum(i+1);
            auto screen = m_Parser.Variables[varName]["screen"];
            std::vector<int> screenTiles;
            for (auto tidx : screen) {
                screenTiles.push_back(StrToInt(tidx));
            }
            // get the screens map.x and map.y positions
            auto scrCoords = mapIndexToPt[i];
            scrCoords.x *= m_Window.Width()  * static_cast<LONG>(tx);
            scrCoords.y *= m_Window.Height() * static_cast<LONG>(ty);
            for (auto sy = 0; sy < m_Window.Height(); sy++) {
                for (auto sx = 0; sx < m_Window.Width(); sx++) {
                    Project::MapEntity me;
                    auto ti = screenTiles[sy * m_Window.Width() + sx];
                    // get the tile document
                    auto tileDoc = dynamic_cast<Project::TileDocument*>(theDocumentManager.Get("Image", "Tile", "Tile " + IntToStr(ti+1)));
                    if (tileDoc) {
                        me.Id = tileDoc->Id;
                        me.RoomIndex = i;
                        me.Pt = TPoint(scrCoords.x + (sx * tx), scrCoords.y + (sy * ty));
                        entities.push_back(me);
                    } else {
                        WarningMessage("[AGD Importer] Tile document for index[" + IntToStr(ti) + "] not found during Map import process.");
                    }
                }
            }
            // get the spritepositions for the screen(room)
            auto screenName = "screen" + m_Parser.PadNum(i+1);
            auto spc = m_Parser.Variables["spriteposition"][screenName + ".sprite.type"].size();
            for (auto sp = 0; sp < spc; sp++) {
                auto spt = StrToInt(m_Parser.Variables["spriteposition"][screenName + ".sprite.type"].front());
                auto spi = StrToIntDef(m_Parser.Variables["spriteposition"][screenName + ".sprite.index"].front(), 0);
                if (spi > numSprites) {
                    spi = 0;
                }
                auto spx = StrToInt(m_Parser.Variables["spriteposition"][screenName + ".sprite.x"].front()) - (m_Window.Left * is.Minimum.Width );
                auto spy = StrToInt(m_Parser.Variables["spriteposition"][screenName + ".sprite.y"].front()) - (m_Window.Top  * is.Minimum.Height);
                Project::MapEntity me;
                auto spriteDoc = dynamic_cast<Project::SpriteDocument*>(theDocumentManager.Get("Image", "Sprite", "Sprite " + IntToStr(spi+1)));
                if (spriteDoc) {
                    me.Id = spriteDoc->Id;
                    me.RoomIndex = i;
                    me.SpriteType = spt;
                    me.Pt = TPoint(scrCoords.x +spx, scrCoords.y + spy);
                    entities.push_back(me);
                } else {
                    WarningMessage("[AGD Importer] Sprite document for index[" + IntToStr(spi) + "] not found during SpritePositions import process for Room: " + IntToStr(i) + ", Spriteposition: " + IntToStr(sp) + ".");
                }
                m_Parser.Variables["spriteposition"][screenName + ".sprite.type"].pop_front();
                m_Parser.Variables["spriteposition"][screenName + ".sprite.index"].pop_front();
                m_Parser.Variables["spriteposition"][screenName + ".sprite.x"].pop_front();
                m_Parser.Variables["spriteposition"][screenName + ".sprite.y"].pop_front();
            }
        }
        // add objects to the map entities list
        Project::DocumentList imageDocs;
        theDocumentManager.GetAllOfType("Image", imageDocs);
        for (auto imgDoc : imageDocs) {
            auto objDoc = dynamic_cast<Project::ObjectDocument*>(imgDoc);
            if (objDoc != nullptr) {
                auto scrCoords = mapIndexToPt[objDoc->RoomIndex];
                scrCoords.x *= m_Window.Width()  * tx;
                scrCoords.y *= m_Window.Height() * ty;

                Project::MapEntity me;
                me.Id = objDoc->Id;
                me.Pt = TPoint(scrCoords.x + objDoc->X, scrCoords.y + objDoc->Y);
                me.RoomIndex = objDoc->RoomIndex;
                entities.push_back(me);
            }
        }

        // get the map document
        auto doc = dynamic_cast<Project::TiledMapDocument*>(theDocumentManager.Get("Map", "Tiled", "Tile Map"));
        // set all the tile entities
        doc->SetEntities(Project::meMap, entities);
        // set the start screen
        Bus::Publish<SetStartRoom>(SetStartRoom(scrPos));
        // loop over the objects/spritepositions and add them to each room's entity list
    } else {
        ErrorMessage("Map size is invalid: " + IntToStr(mapWidth) + "x" + UIntToStr(mapHeight) + " (" + UIntToStr(mapSize) + ", is not >= 1 and < 255.");
    }

    return result;
}
//---------------------------------------------------------------------------

