//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "System/Path.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
namespace System
{
String Path::m_Application;
String Path::m_Common;
String Path::m_Documents;
String Path::m_Projects;
String Path::m_ProjectName;
String Path::m_Separator;
class Path Path;
//---------------------------------------------------------------------------
__fastcall Path::Path()
{
    // Can't initialise the paths here; Android API is not available during static object construction
    Init();
}
//---------------------------------------------------------------------------
void __fastcall Path::Init()
{
    const String appName = ApplicationName;
    m_Separator = System::Ioutils::TPath::DirectorySeparatorChar;
    m_Application = System::Ioutils::TPath::GetSharedDocumentsPath() + m_Separator + appName + m_Separator;
    m_Common = System::Ioutils::TPath::GetSharedDocumentsPath() + m_Separator + appName + m_Separator + "Common" + m_Separator;
    m_Documents = System::Ioutils::TPath::GetSharedDocumentsPath() + m_Separator;
    m_Projects = System::Ioutils::TPath::GetSharedDocumentsPath() + m_Separator + appName + m_Separator + "Projects" + m_Separator;
}
//---------------------------------------------------------------------------
String __fastcall Path::GetFolder(const Location location, const String& subFolder)
{
    auto folder = m_Common;
    if (location == lpApplication) folder = m_Application;
    else if (location == lpDocuments) folder = m_Documents;
    else if (location == lpProjects) folder = m_Projects;
    folder += subFolder;
    return folder;
}
//---------------------------------------------------------------------------
TStringDynArray Path::GetFolders(Location location, const String& subFolder)
{
    auto folder = GetFolder(location, subFolder);
    if (System::Ioutils::TDirectory::Exists(folder))
    {
        return System::Ioutils::TDirectory::GetDirectories(folder);
    }
    TStringDynArray empty;
    return empty;
}
//---------------------------------------------------------------------------
String __fastcall Path::GetFolderRelativeTo(const Location location, const String& path)
{
    auto relPath = path;
    auto folder = GetFolder(location);
    if (path.Pos(folder) == 1)
    {
        relPath = path.SubString(folder.Length() + 1, path.Length());
    }
    return relPath;
}
//---------------------------------------------------------------------------
String __fastcall Path::GetActiveProjectFolder()
{
    return Projects + ProjectName + Separator;
}
//---------------------------------------------------------------------------
TStringDynArray __fastcall Path::GetFiles(const String& folder, const String& filter)
{
    if (System::Ioutils::TDirectory::Exists(folder))
    {
        return System::Ioutils::TDirectory::GetFiles(folder, filter);
    }
    TStringDynArray empty;
    return empty;
}
//---------------------------------------------------------------------------
TStringDynArray __fastcall Path::GetFiles(Location location, const String& filter, const String& subFolder)
{
    auto folder = GetFolder(location, subFolder);
    return GetFiles(folder, filter);
}
//---------------------------------------------------------------------------
String __fastcall Path::Create(Location location, const String& subFolder)
{
    auto folder = GetFolder(location, subFolder);
    if (!Exists(location, subFolder))
    {
        System::Ioutils::TDirectory::CreateDirectory(folder);
    }
    return folder;
}
//---------------------------------------------------------------------------
bool __fastcall Path::Exists(const String& path)
{
    return System::Ioutils::TDirectory::Exists(path);
}
//---------------------------------------------------------------------------
bool __fastcall Path::Exists(Location location, const String& subFolder)
{
    return Exists(GetFolder(location, subFolder));
}
//---------------------------------------------------------------------------
void __fastcall Path::Delete(Location location, const String& subFolder)
{
    if (Exists(location, subFolder))
    {
        auto folder = GetFolder(location, subFolder);
        System::Ioutils::TDirectory::Delete(folder, true);
    }
}
//---------------------------------------------------------------------------
void __fastcall Path::Rename(Location location, const String& fromSubFolder, const String& toSubFolder)
{
    if (Exists(location, fromSubFolder))
    {
        auto fromFolder = GetFolder(location, fromSubFolder);
        auto toFolder = GetFolder(location, toSubFolder);
        System::Ioutils::TDirectory::Move(fromFolder, toFolder);
    }
}
//---------------------------------------------------------------------------
} // File namespace
//---------------------------------------------------------------------------
