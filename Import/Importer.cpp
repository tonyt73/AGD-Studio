//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Importer.h"
#include "ImportSnaFile.h"
#include "ImportAgdFile.h"
#include "Messaging/Messaging.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Importer::Importer()
{
}
//---------------------------------------------------------------------------
bool __fastcall Importer::Convert(const String& file)
{
    auto ext = System::File::Extension(file);
    std::unique_ptr<ImportFile> import = nullptr;
    if (ext == ".agd")
    {
        import = std::make_unique<ImportAgdFile>();
    }
    else if (ext == ".sna")
    {
        import = std::make_unique<ImportSnaFile>();
    }
    else
    {
        // Unsupported file format
        return false;
    }
    return import->Process(file);
}
//---------------------------------------------------------------------------
