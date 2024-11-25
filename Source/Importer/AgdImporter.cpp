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
#include "Project/Documents/JumpTable.h"
#include "Project/Documents/Text.h"
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
            if (str[1] == '\'') {
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
    if (m_Parser.Parse(file, theDocumentManager.ProjectConfig()->MachineConfiguration().Name)) {
        // convert contents to AGD Studio documents
        UpdateWindow();
        UpdateControls();
        UpdateJumpTable();
        UpdateFont();
        UpdateObjects();
        return true;
    }
    return false;
 }
//---------------------------------------------------------------------------
void AgdImporter::UpdateWindow()
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
}
//---------------------------------------------------------------------------
void AgdImporter::UpdateControls()
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
    }
}
//---------------------------------------------------------------------------
void AgdImporter::UpdateJumpTable()
{
    if (m_Parser.hasVariable("jumptable")) {
        auto doc = dynamic_cast<Project::JumpTableDocument*>(theDocumentManager.Add("Jump", "Table", "JumpTable"));
        for (int step = 0; step < doc->Count; step++) {
            doc->SetStep(step, GetNum("jumptable", "jump.table", step));
        }
    }
}
//---------------------------------------------------------------------------
void AgdImporter::UpdateFont()
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
                    frame += IntToHex(GetNum("font", "characterset", bytesPerFrame * f + i), 2);
                }
                doc->Frame[f] = frame;
            }
        } else {
            ErrorMessage("[Importer] Incorrect number of font bytes found. Require " + IntToStr(bytesRequired) + "bytes, but got " + IntToStr(bytes) + " bytes.");
        }
    }
}
//---------------------------------------------------------------------------
void AgdImporter::UpdateObjects()
{
    if (m_Parser.hasVariable("objects")) {
        auto name = "Object " + IntToStr(1);
        auto doc = dynamic_cast<Project::CharacterSetDocument*>(theDocumentManager.Add("Image", "Object", name));
    }
}
//---------------------------------------------------------------------------

