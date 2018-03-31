//---------------------------------------------------------------------------
#ifndef ProjectDocumentH
#define ProjectDocumentH
//---------------------------------------------------------------------------
#include "Project/Document.h"
//---------------------------------------------------------------------------
class ProjectDocument : public Document
{
private:
                String              m_Version;
                String              m_Author;
                String              m_Description;
                String              m_Machine;

            void        __fastcall  SetName(const String& name);
            void        __fastcall  Save();
            void        __fastcall  OnChangeString(const OnChange<String>& event);

public:
                        __fastcall  ProjectDocument();
                        __fastcall  ProjectDocument(const String& name, const String& machine);

__published:
    // Project settings
    __property  String             Name = { read = m_Name, write = SetName };
    __property  String          Version = { read = m_Version, write = m_Version };
    __property  String           Author = { read = m_Author, write = m_Author };
    __property  String      Description = { read = m_Description, write = m_Description };
    __property  String          Machine = { read = m_Machine };
};
//---------------------------------------------------------------------------
#endif
