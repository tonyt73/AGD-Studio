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
    const String appName = "AGDX Studio";
    m_Separator = System::Ioutils::TPath::DirectorySeparatorChar;
    m_Application = System::Ioutils::TPath::GetHomePath() + m_Separator + appName + m_Separator;
    m_Common = System::Ioutils::TPath::GetSharedDocumentsPath() + m_Separator + appName + m_Separator + "Common" + m_Separator;
    m_Projects = System::Ioutils::TPath::GetSharedDocumentsPath() + m_Separator + appName + m_Separator + "Projects" + m_Separator;
}
//---------------------------------------------------------------------------
String __fastcall Path::GetFolder(const Location location, const String& subFolder)
{
    auto folder = m_Common;
    if (location == lpApplication) folder = m_Application;
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
bool __fastcall Path::Exists(Location location, const String& subFolder)
{
    auto folder = GetFolder(location, subFolder);
    return System::Ioutils::TDirectory::Exists(folder);
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
} // File namespace
//---------------------------------------------------------------------------
