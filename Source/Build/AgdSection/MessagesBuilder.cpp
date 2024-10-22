//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "MessagesBuilder.h"
#include "Project/DocumentManager.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace Build
{
//---------------------------------------------------------------------------
MessagesBuilder::MessagesBuilder()
: SectionBuilder("MessagesBuilder")
{
}
//---------------------------------------------------------------------------
MessagesBuilder::~MessagesBuilder()
{
}
//---------------------------------------------------------------------------
void MessagesBuilder::Execute()
{
    const auto& dm = theDocumentManager;
    auto msgs = dm.Get("Text", "MessagesBuilder", "MessagesBuilder");
    if (msgs != nullptr)
    {
        auto file = msgs->File;
        if (Services::File::Exists(file))
        {
            AddLine("DEFINEMESSAGES");
            AddLine(Services::File::ReadText(file));
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
        Failure("No MessagesBuilder document registered with the document manager");
    }
}
//---------------------------------------------------------------------------
}
