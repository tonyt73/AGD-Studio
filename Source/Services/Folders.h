//---------------------------------------------------------------------------
#ifndef FoldersH
#define FoldersH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
namespace Services
{
//---------------------------------------------------------------------------
class Folders
{
public:
			enum                Location { lpApplication, lpCommon, lpDocuments, lpProjects };

private:
	static String               m_Application;
	static String               m_Common;
	static String               m_Documents;
	static String               m_Projects;
	static String               m_ProjectName;
	static String               m_Separator;

								Folders();        // Disallow instantiation outside of the class
public:

								Folders(const Folders&) = delete;
								Folders(Folders&&) = delete;
								Folders& operator=(const Folders&) = delete;
								Folders& operator=(Folders&&) = delete;

	static auto& instance()     {
									static Folders folders;
									folders.Init();
									return folders;
								}
	void                        Init();

	static TStringDynArray      GetFiles(const String& folder, const String& filter);
	static TStringDynArray      GetFiles(Location location, const String& filter, const String& subFolder);
	static void			        GetFolders(Location location, const String& subFolder, TStringDynArray& folders);
	static String               GetFolder(const Location location, const String& subFolder = "");
	static String               GetFolderRelativeTo(const Location location, const String& path);
	static String               GetActiveProjectFolder();
	static String               Create(Location location, const String& subFolder);
	static bool                 Exists(const String& path);
	static bool                 Exists(Location location, const String& subFolder);
	static void                 Delete(Location location, const String& subFolder);
	static void                 Rename(Location location, const String& fromSubFolder, const String& toSubFolder);

								// application specific files, configs etc (per installation)
	__property  String          Application = { read = m_Application };
								// common game asset files, common application files (shared)
	__property  String          Common = { read = m_Common };
								// OS documents folder. The base for all projects
	__property  String          Documents = { read = m_Documents };
								// game projects folder (shared)
	__property  String          Projects = { read = m_Projects };
								// active project folder
    __property  String          Project = { read = GetActiveProjectFolder };
                                // the active project name
	__property  String          ProjectName = { read = m_ProjectName, write = m_ProjectName };
								// The OS file system path separator
	__property  String          Separator = { read = m_Separator };
};
//#define _Folders auto& Folders = Folders::instance()
//---------------------------------------------------------------------------
} // Services namespace
//---------------------------------------------------------------------------
#endif
