//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Services;
//---------------------------------------------------------------------------
String Folders::m_Application = "";
String Folders::m_Common = "";
String Folders::m_Documents = "";
String Folders::m_Projects = "";
String Folders::m_ProjectName = "";
String Folders::m_Separator = "";
//---------------------------------------------------------------------------
//Folders::Path()
//{
//    // Can't initialise the Folders here; Android API is not available during static object construction
//    Init();
//}
//---------------------------------------------------------------------------
void Folders::Init()
{
    const String appName = ApplicationName;
	m_Separator = System::Ioutils::TPath::DirectorySeparatorChar;
	m_Application = System::Ioutils::TPath::GetSharedDocumentsPath() + m_Separator + appName + m_Separator;
	m_Common = System::Ioutils::TPath::GetSharedDocumentsPath() + m_Separator + appName + m_Separator + "Common" + m_Separator;
	m_Documents = System::Ioutils::TPath::GetSharedDocumentsPath() + m_Separator;
    m_Projects = System::Ioutils::TPath::GetSharedDocumentsPath() + m_Separator + appName + m_Separator + "Projects" + m_Separator;
}
//---------------------------------------------------------------------------
String Folders::GetFolder(const Location location, const String& subFolder)
{
    auto folder = m_Common;
    if (location == lpApplication) folder = m_Application;
    else if (location == lpDocuments) folder = m_Documents;
    else if (location == lpProjects) folder = m_Projects;
    folder += subFolder;
    return folder;
}
//---------------------------------------------------------------------------
void Folders::GetFolders(Location location, const String& subFolder, TStringDynArray& folders)
{
	auto folder = GetFolder(location, subFolder);
	if (System::Ioutils::TDirectory::Exists(folder))
	{
		folders = System::Ioutils::TDirectory::GetDirectories(folder);
	}
}
//---------------------------------------------------------------------------
String Folders::GetFolderRelativeTo(const Location location, const String& path)
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
String Folders::GetActiveProjectFolder()
{
    return Projects + ProjectName + Separator;
}
//---------------------------------------------------------------------------
TStringDynArray Folders::GetFiles(const String& folder, const String& filter)
{
	if (System::Ioutils::TDirectory::Exists(folder))
	{
		return System::Ioutils::TDirectory::GetFiles(folder, filter);
	}
    return TStringDynArray();
}
//---------------------------------------------------------------------------
TStringDynArray Folders::GetFiles(Location location, const String& filter, const String& subFolder)
{
    auto folder = GetFolder(location, subFolder);
    return GetFiles(folder, filter);
}
//---------------------------------------------------------------------------
String Folders::Create(Location location, const String& subFolder)
{
    auto folder = GetFolder(location, subFolder);
    if (!Exists(location, subFolder))
    {
        System::Ioutils::TDirectory::CreateDirectory(folder);
    }
    return folder;
}
//---------------------------------------------------------------------------
bool Folders::Exists(const String& path)
{
    return System::Ioutils::TDirectory::Exists(path);
}
//---------------------------------------------------------------------------
bool Folders::Exists(Location location, const String& subFolder)
{
    return Exists(GetFolder(location, subFolder));
}
//---------------------------------------------------------------------------
void Folders::Delete(Location location, const String& subFolder)
{
    if (Exists(location, subFolder))
    {
        auto folder = GetFolder(location, subFolder);
        System::Ioutils::TDirectory::Delete(folder, true);
    }
}
//---------------------------------------------------------------------------
void Folders::Rename(Location location, const String& fromSubFolder, const String& toSubFolder)
{
    if (Exists(location, fromSubFolder))
    {
        auto fromFolder = GetFolder(location, fromSubFolder);
        auto toFolder = GetFolder(location, toSubFolder);
        System::Ioutils::TDirectory::Move(fromFolder, toFolder);
    }
}
//---------------------------------------------------------------------------
