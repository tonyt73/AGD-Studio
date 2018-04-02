//---------------------------------------------------------------------------
#ifndef ProjectDocumentH
#define ProjectDocumentH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
typedef struct FileInfo
{
    String          Name;
    String          Type;
    String          SubType;
} _fi;
typedef std::vector<FileInfo> FileList;
//---------------------------------------------------------------------------
class ProjectDocument : public Document
{
private:
                String              m_Version;
                String              m_Author;
                String              m_Description;
                String              m_Machine;
                FileInfo            m_FileInfo; // used by the json loader

                FileList            m_Files;

            String      __fastcall  GetFile() const;
            void        __fastcall  SetName(String name);
            void        __fastcall  OnChangeString(const OnChange<String>& event);
            void        __fastcall  OnEndObject(const String& object);

public:
                        __fastcall  ProjectDocument();
                        __fastcall  ProjectDocument(const String& name);
    static  Document*   __fastcall  Create(const String& name) { return new ProjectDocument(name); };

            void        __fastcall  Save();
            bool        __fastcall  Load();

            void        __fastcall  ClearFiles();
            void        __fastcall  AddFile(const String& file, const String& type, const String& subType);
    const FileList&     __fastcall  Files() const;


__published:
    // Project settings
    __property  String             Name = { read = m_Name, write = SetName };
    __property  String          Version = { read = m_Version, write = m_Version };
    __property  String           Author = { read = m_Author, write = m_Author };
    __property  String      Description = { read = m_Description, write = m_Description };
    __property  String          Machine = { read = m_Machine, write = m_Machine };
};
//---------------------------------------------------------------------------
#endif
