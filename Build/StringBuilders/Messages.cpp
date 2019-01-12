//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/StringBuilders/Messages.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall StringBuilders::Messages::Messages()
{
}
//---------------------------------------------------------------------------
__fastcall StringBuilders::Messages::~Messages()
{
}
//---------------------------------------------------------------------------
void __fastcall StringBuilders::Messages::Execute()
{
    const auto& dm = theDocumentManager;
    auto msgs = dm.Get("Text", "Message", "Messages");
    if (msgs != nullptr)
    {
        auto file = msgs->File;
        if (System::File::Exists(file))
        {
            AddLine("DEFINEMESSAGES");
            AddLine(System::File::ReadText(file));
            LineBreak();
            Success();
        }
        else
        {
            Failure("Cannot file messages file: " + file);
        }
    }
    else
    {
        Failure("No Messages document registered with the document manager");
    }
}
//---------------------------------------------------------------------------

