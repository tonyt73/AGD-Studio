//---------------------------------------------------------------------------
#ifndef PathH
#define PathH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
namespace System
{
//---------------------------------------------------------------------------
class Path
{
public:
            enum                        Location { lpApplication, lpCommon, lpProjects };

private:
    static String                       m_Application;
    static String                       m_Common;
    static String                       m_Projects;
    static String                       m_Separator;

public:
							__fastcall  Path();

	static  void            __fastcall  Init();

	static  TStringDynArray __fastcall  GetFiles(const String& folder, const String& filter);
	static  TStringDynArray __fastcall  GetFiles(Location location, const String& filter, const String& subFolder = "");
	static  TStringDynArray __fastcall  GetFolders(Location location, const String& subFolder = "");
    static  String          __fastcall  GetFolder(const Location location, const String& subFolder = "");
	static  bool            __fastcall  Exists(Location location, const String& subFolder = "");
    static  void            __fastcall  Delete(Location location, const String& subFolder);

                                        // application specific files, configs etc (per installation)
    static  __property  String          Application = { read = m_Application };
                                        // common game asset files, common application files (shared)
    static  __property  String          Common = { read = m_Common };
                                        // game projects (shared)
    static  __property  String          Projects = { read = m_Projects };
                                        // The OS file system path separator
    static  __property  String          Separator = { read = m_Separator };
};
extern PACKAGE Path Path;
//---------------------------------------------------------------------------
} // file namespace
//---------------------------------------------------------------------------
#endif
