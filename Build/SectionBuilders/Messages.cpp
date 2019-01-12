//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/SectionBuilders/Messages.h"
#include "Project/DocumentManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Messages::Messages()
{
}
//---------------------------------------------------------------------------
__fastcall SectionBuilders::Messages::~Messages()
{
}
//---------------------------------------------------------------------------
void __fastcall SectionBuilders::Messages::Execute()
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

