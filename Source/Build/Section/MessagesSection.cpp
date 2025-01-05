//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "MessagesSection.h"
#include "Project/Documents/DocumentManager.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
__fastcall MessagesSection::MessagesSection()
: Section("Messages")
{
}
//---------------------------------------------------------------------------
__fastcall MessagesSection::~MessagesSection()
{
}
//---------------------------------------------------------------------------
void __fastcall MessagesSection::Execute()
{
    const auto& dm = theDocumentManager;
    auto msgs = dm.Get("Text", "Messages", "Messages");
    if (msgs != nullptr) {
        auto file = msgs->File;
        if (Services::File::Exists(file)) {
            AddLine("DEFINEMESSAGES");
            auto lines = Services::File::ReadLines(file);
            // quote count
            auto quote = false;
            for (auto line : lines) {
                quote |= line.Trim().Pos("\"") == 1;
                if (quote) {
                    AppendLine(line + "\r");
                }
            }
            LineBreak();
            Success();
        } else {
            Failure("Cannot file messages file: " + file);
        }
    } else {
        Failure("No Messages document registered with the document manager");
    }
}
//---------------------------------------------------------------------------
}
