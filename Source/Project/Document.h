//---------------------------------------------------------------------------
#ifndef DocumentH
#define DocumentH
//---------------------------------------------------------------------------
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include <map>
#include <vector>
//---------------------------------------------------------------------------
#include "Services/JsonFile.h"
#include "Messaging/Messaging.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
// Inheritence map
// Document -> Services::JsonFile -> TPersistent
// TPersistent is a Delphi class used by the property editor to extract
// published __property items from a class that can be then viewed/edited.
// JsonFile does not use TPersistent; but Document does.
// Delphi classes cannot use Multiple Inheritence; so JsonFile then needs to
// derive from TPersistent; since Document can't. But in the end this all
// works out nicely as technically a JsonFile file is persistent; it's just
// we aren't using Delphi's persistence.
//---------------------------------------------------------------------------
const unsigned int InvalidDocumentId = 0;
const String       Unnamed = "unnamed";
//---------------------------------------------------------------------------
class Document : public Services::JsonFile
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
            Registrar               m_Registrar;
            String                  m_Name;
            String                  m_Type;
            String                  m_SubType;
            String                  m_File;
            String                  m_Folder;
            String                  m_Extension;
            bool                    m_ShowFileExtension;
            bool                    m_ReadOnly;
            TPropertyInfoMap        m_PropertyInfo;
            // TODO: Remove these 2 and put them in to the document manager
            void*                   m_TreeNode;
            void*                   m_DockPanel;

            // document reference id
            unsigned int            m_RefId;        // used by editor to find documents quickly
            // next ref id is the next largest id available (updated on load)
static      unsigned int            s_NextRefId;    // next unused ref id. Reset on load
            bool                    m_SaveRefId;    // flag:

            void         SetName(String name);
            String       GetFile(String name = "");
            bool         IsValid() const;
            bool         IsValid(const String& name) const;
                                    // update the documents json content
    virtual void         Update() {};//= 0;

                                    // LMD property editor - property is item been edited, category is section and info is the hint description
            void         RegisterProperty(const String& property, const String& category, const String& info);
    virtual void         DoSave() = 0;
            void         SetShowFileExtension(bool value);

public:
                         Document(const String& name);
    virtual             ~Document();

    static  Document*    Create(const String& name, const String& extra)      { throw "Don't create this class";    }

const TPropertyInfoMap&  GetPropertyInfo() const;
            String       GetPropertyInfo(const String& property) const;

    virtual void         Save();
    virtual bool         Load();
            void         AssignId();
            void         Close();

    __property         unsigned int Id          = { read = m_RefId                          };
    __property          String      File        = { read = GetFile                          };
    __property          String      Type        = { read = m_Type                           };
    __property          String      SubType     = { read = m_SubType                        };
    __property          bool        ShowFileExt = { read = m_ShowFileExtension              };
    __property          bool        IsReadOnly  = { read = m_ReadOnly                       };
    __property          void*       TreeNode    = { read = m_TreeNode, write = m_TreeNode   };
    __property          void*       DockPanel   = { read = m_DockPanel, write = m_DockPanel };

__published:
    __property          String   Classification = { read = m_Folder                         };
    __property          String      Name        = { read = m_Name, write = SetName          };
    __property          String      Path        = { read = m_File                           };
};
//---------------------------------------------------------------------------
typedef Document* (*CreateDocumentFn)(const String& name, const String& extra);
typedef std::vector<Document*> DocumentList;
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
