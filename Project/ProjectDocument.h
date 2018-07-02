//---------------------------------------------------------------------------
#ifndef ProjectDocumentH
#define ProjectDocumentH
//---------------------------------------------------------------------------
#include <memory>
#include "Project/Document.h"
#include "Project/MachineConfig.h"
//---------------------------------------------------------------------------
typedef struct FileInfo
{
    String          Name;
    String          Type;
    String          SubType;
} _fi;
typedef std::vector<FileInfo> FileList;
typedef struct WindowInfo
{
    unsigned int X;
    unsigned int Y;
    unsigned int Width;
    unsigned int Height;
} _wi;
//---------------------------------------------------------------------------
class ProjectDocument : public Document
{
private:
                String              m_Version;
                String              m_Author;
                String              m_Description;
                String              m_MachineName;  // json loader
     std::unique_ptr<MachineConfig> m_MachineConfig;
                FileInfo            m_FileInfo;     // used by the json loader
                FileList            m_Files;
                WindowInfo          m_Window;

            String      __fastcall  GetFile() const;
            void        __fastcall  SetName(String name);
            void        __fastcall  OnChangeString(const OnChange<String>& event);
            void        __fastcall  OnEndObject(const String& object);

public:
                        __fastcall  ProjectDocument(const String& name, const String& machine);
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new ProjectDocument(name, extra); };

   const MachineConfig& __fastcall  MachineConfiguration() const;
            void        __fastcall  Save();
            bool        __fastcall  Load();

            void        __fastcall  ClearFiles();
            void        __fastcall  AddFile(const String& file, const String& type, const String& subType);
    const FileList&     __fastcall  Files() const;


__published:
    // Project settings
    __property  String         Name = { read = m_Name       , write = SetName       };
    __property  String      Version = { read = m_Version    , write = m_Version     };
    __property  String       Author = { read = m_Author     , write = m_Author      };
    __property  String  Description = { read = m_Description, write = m_Description };
    __property  String      Machine = { read = m_MachineName                        };
    __property  WindowInfo   Window = { read = m_Window     , write = m_Window      };
    // TODO: Keys, Jump Table
};
//---------------------------------------------------------------------------
#endif
