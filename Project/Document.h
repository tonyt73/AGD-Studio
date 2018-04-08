//---------------------------------------------------------------------------
#ifndef DocumentH
#define DocumentH
//---------------------------------------------------------------------------
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include <map>
#include <vector>
#include "System/JsonFile.h"
//---------------------------------------------------------------------------
// Inheritence map
// Document -> System::JsonFile -> TPersistent
// TPersistent is a Delphi class used by the property editor to extract
// published __property items from a class that can be then viewed/edited.
// JsonFile does not use TPersistent; but Document does.
// Delphi classes cannot use Multiple Inheritence; so JsonFile then needs to
// derive from TPersistent; since Document can't. But in the end this all
// works out nicely as technically a JsonFile file is persistent; it's just
// we aren't using Delphi's persistence.
//---------------------------------------------------------------------------
class Document : public System::JsonFile
{
public:
    struct TPropertyInfo
    {
        String  category;
        String  info;
    };
    typedef std::map<String,TPropertyInfo>  TPropertyInfoMap;
    TPropertyInfoMap::iterator              TPropertyInfoMapIt;

protected:
            String                  m_Name;
            String                  m_Type;
            String                  m_SubType;
            String                  m_File;
            String                  m_Folder;
            String                  m_Extension;
            bool                    m_MultiDoc;
            TPropertyInfoMap        m_PropertyInfo;
            void*                   m_TreeNode;
            void*                   m_DockPanel;

            void        __fastcall  SetName(String name);
            String      __fastcall  GetFile();
                                    // update the documents json content
    virtual void        __fastcall  Update() {};//= 0;
                                    // convert json data to document data
    virtual void        __fastcall  OnLoad() {};//= 0;

            void        __fastcall  RegisterProperty(const String& property, const String& category, const String& info);

public:
                        __fastcall  Document(const String& name);

    static  Document*   __fastcall  Create(const String& name, const String& extra)      { throw "Don't create this class";    }

const TPropertyInfoMap& __fastcall  GetPropertyInfo() const;
            String      __fastcall  GetPropertyInfo(const String& property) const;

    virtual void        __fastcall  Save() = 0;
    virtual bool        __fastcall  Load();

    __property          String      File        = { read = GetFile                          };
    __property          String      Type        = { read = m_Type                           };
    __property          String      SubType     = { read = m_SubType                        };
    __property          bool        IsMultiDoc  = { read = m_MultiDoc                       };
    __property          void*       TreeNode    = { read = m_TreeNode, write = m_TreeNode   };
    __property          void*       DockPanel   = { read = m_DockPanel, write = m_DockPanel };

__published:
    __property          String      Classification={read = m_Folder                         };
    __property          String      Name        = { read = m_Name, write = SetName          };
    __property          String      Path        = { read = m_File                           };
};
//---------------------------------------------------------------------------
typedef Document* (__fastcall *CreateDocumentFn)(const String& name, const String& extra);
//---------------------------------------------------------------------------
#endif
