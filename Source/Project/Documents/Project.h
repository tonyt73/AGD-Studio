//---------------------------------------------------------------------------
#ifndef ProjectH
#define ProjectH
//---------------------------------------------------------------------------
#include "Document.h"
#include "MachineConfig.h"
#include "Messaging/Event.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
typedef struct FileInfo
{
    String          Name;
    String          Type;
    String          SubType;
} _fi;
typedef std::list<FileInfo> FileList;
//---------------------------------------------------------------------------
class ProjectDocument : public Document
{
private:
                String              m_Version;      // version of the project
                String              m_Author;       // the game author
                String              m_Description;  // a description of their game
                String              m_MachineName;  // json loader
     std::unique_ptr<MachineConfig> m_MachineConfig;// the machine this project uses
                FileInfo            m_FileInfo;     // used by the json loader
                FileList            m_Files;        // a list of files the project uses

            String      __fastcall  GetFile() const;
            void        __fastcall  SetName(String name);
            void        __fastcall  OnChangeString(const OnChange<String>& event);
            void        __fastcall  OnEndObject(const String& object);
            void        __fastcall  DoSave();
            String      __fastcall  GetGraphicsMode() const;
            int         __fastcall  GetScreenSize(int index) const;

public:
                        __fastcall  ProjectDocument(const String& name, const String& machine);
                        __fastcall ~ProjectDocument();
    static  Document*   __fastcall  Create(const String& name, const String& extra) { return new ProjectDocument(name, extra); };

   const MachineConfig& __fastcall  MachineConfiguration() const;
         MachineConfig& __fastcall  WritableMachineConfiguration() const;
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
    __property  String GraphicsMode = { read = GetGraphicsMode                      };
    __property  int     ScreenWidth = { read = GetScreenSize, index = 0             };
    __property  int    ScreenHeight = { read = GetScreenSize, index = 1             };
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
