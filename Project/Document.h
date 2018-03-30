//---------------------------------------------------------------------------
#ifndef DocumentH
#define DocumentH
//---------------------------------------------------------------------------
#include <Vcl.Controls.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
//---------------------------------------------------------------------------
#include <map>
#include <vector>
//---------------------------------------------------------------------------
class Document : public TPersistent
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
            String                  m_File;
            String                  m_Name;
            String                  m_Type;
            String                  m_SubType;
            String                  m_Folder;
            bool                    m_MultiDoc;
            TPropertyInfoMap        m_PropertyInfo;
            void*                   m_TreeNode;
            void*                   m_DockPanel;

                                    // update the documents json content
    virtual void        __fastcall  Update() {};//= 0;
                                    // convert json data to document data
    virtual void        __fastcall  OnLoad() {};//= 0;

            void        __fastcall  RegisterProperty(const String& property, const String& category, const String& info);

public:
                        __fastcall  Document();
                        __fastcall  Document(const String& subType);

            bool        __fastcall  Save();
            bool        __fastcall  Load(const String& json);
const TPropertyInfoMap& __fastcall  GetPropertyInfo() const;
            String      __fastcall  GetPropertyInfo(const String& property) const;

    __property          String      Type        = { read = m_Type                   };
    __property          String      SubType     = { read = m_SubType                };
    __property          bool        IsMultiDoc  = { read = m_MultiDoc               };
    __property          void*       TreeNode    = { read = m_TreeNode, write = m_TreeNode };
    __property          void*       DockPanel   = { read = m_DockPanel, write = m_DockPanel };


    static  Document*   __fastcall  Create()      { throw "Don't create this class";    }

__published:
    __property          String      Folder      = { read = m_Folder                     };
    __property          String      Name        = { read = m_Name   , write = m_Name    };
};
//---------------------------------------------------------------------------
typedef Document* (__fastcall *CreateDocumentFn)();
//---------------------------------------------------------------------------
class DocumentSet : public Document
{
private:
            int         __fastcall  GetCount();

protected:
    typedef std::vector<Document*> TDocumentList;
    typedef TDocumentList::iterator  TDocumentListIt;

    TDocumentList                   m_Documents;

    virtual void        __fastcall  Update() {};
    virtual void        __fastcall  OnLoad() {};

public:
                        __fastcall  DocumentSet();
                        __fastcall  DocumentSet(const String& subType);

            void        __fastcall  Clear();
            Document*   __fastcall  Add();
            void        __fastcall  Remove(int index);
            void        __fastcall  Remove(const String& name);
            Document*   __fastcall  Get(int index);
            Document*   __fastcall  Get(const String& name);


    __property          int         Count = { read = GetCount       };
    static  Document* __fastcall  Create() { throw "Don't create this class"; }
};
//---------------------------------------------------------------------------
class Text : public Document
{
private:
            //String                  m_Filename;
public:
                        __fastcall  Text();

    static  Document* __fastcall  Create() { return new Text(); };

            //String      __property  Filename        = { read = m_Filename, write = m_Filename };
};
//---------------------------------------------------------------------------
class TextCode : public Text
{
private:

public:
                        __fastcall  TextCode();

    static  Document* __fastcall  Create() { return new TextCode(); };
};
//---------------------------------------------------------------------------
class TextEvent : public Text
{
private:

public:
                        __fastcall  TextEvent();

    static  Document* __fastcall  Create() { return new TextEvent(); };
};
//---------------------------------------------------------------------------
class TextSoundFx : public Text
{
private:

public:
                        __fastcall  TextSoundFx();
    static  Document*   __fastcall  Create() { return new TextSoundFx(); };
};
//---------------------------------------------------------------------------
class Image : public Document
{
private:
    // width, height, format, palette
            int                     m_Width;
            int                     m_Height;
public:
                        __fastcall  Image();
    static  Document*   __fastcall  Create() { return new Image(); };

__published:
            int         __property  Width       = { read = m_Width , write = m_Width    };
            int         __property  Height      = { read = m_Height, write = m_Height   };
            // TODO: add palette info
};
//---------------------------------------------------------------------------
class ImageSet : public DocumentSet
{
private:
            int                     m_Width;
            int                     m_Height;
            int                     m_Count;
public:
                        __fastcall  ImageSet();
    static  Document*   __fastcall  Create() { return new ImageSet(); };


__published:
    __property          int         Width       = { read = m_Width , write = m_Width    };
    __property          int         Height      = { read = m_Height, write = m_Height   };
    __property          int         Count       = { read = m_Count                      };  // TODO: change to GetCount()
};
//---------------------------------------------------------------------------
class Sprite : public ImageSet
{
private:
public:
                        __fastcall  Sprite();
    static Document*    __fastcall  Create() { return new Sprite(); };
};
//---------------------------------------------------------------------------
class Object : public Image
{
private:
    // style, 2d, 3d iso, hexagonal etc
public:
                        __fastcall  Object();
    static  Document*   __fastcall  Create() { return new Object(); };
};
//---------------------------------------------------------------------------
class Tile : public Image
{
private:
    // style, 2d, 3d iso, hexagonal etc
public:
                        __fastcall  Tile();
    static  Document*   __fastcall  Create() { return new Tile(); };
};
//---------------------------------------------------------------------------
class TileSet : public ImageSet
{
private:
            int                     m_TileWidth;
            int                     m_TileHeight;
            bool                    m_IsTransparent;
            TColor                  m_TransparentColor;

public:

                        __fastcall  TileSet();
    static  Document*   __fastcall  Create() { return new TileSet(); };

__published:
    __property          int         TileWidth       = { read = m_TileWidth          , write = m_TileWidth       };
    __property          int         TileHeight      = { read = m_TileHeight         , write = m_TileHeight      };
    __property          bool        IsTransparent   = { read = m_IsTransparent      , write = m_IsTransparent   };
    __property          TColor      TransparentColor= { read = m_TransparentColor   , write = m_TransparentColor};
};
//---------------------------------------------------------------------------
class TileMap : public Document
{
public:

private:
            int                     m_Across;
            int                     m_Down;
            int                     m_StartLocationX;
            int                     m_StartLocationY;
            int                     m_WindowWidth;
            int                     m_WindowHeight;
            TColor                  m_BackgroundColor;

public:
                        __fastcall  TileMap();
    static  Document* __fastcall  Create() { return new TileMap(); };

__published:
    __property          int         Across          = { read = m_Across         , write = m_Across          };
    __property          int         Down            = { read = m_Down           , write = m_Down            };
    __property          int         StartLocationX  = { read = m_StartLocationX , write = m_StartLocationX  };
    __property          int         StartLocationY  = { read = m_StartLocationY , write = m_StartLocationY  };
    __property          int         WindowWidth     = { read = m_WindowWidth    , write = m_WindowWidth     };
    __property          int         WindowHeight    = { read = m_WindowHeight   , write = m_WindowHeight    };
    __property          TColor      BackgroundColor = { read = m_BackgroundColor, write = m_BackgroundColor };
};
//---------------------------------------------------------------------------
class ProjectFile : public Document
{
private:
            String                  m_Author;
            String                  m_Version;

public:
                        __fastcall  ProjectFile();
    static  Document*   __fastcall  Create() { return new ProjectFile(); };

__published:
    // Project settings
    __property          String      Author          = { read = m_Author         , write = m_Author          };
    __property          String      Version         = { read = m_Version        , write = m_Version         };
};
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
class DocumentManager
{
public: // singleton
    static DocumentManager& get();
    DocumentManager(DocumentManager const&) = delete;
    void operator=(DocumentManager const&)   = delete;

private:
    // list of documents grouped by type
    typedef std::map<String, std::vector<Document*>> DocumentMap;
    typedef DocumentMap::iterator  DocumentMapIt;

    DocumentMap                     m_Documents;

    // the document factory
    typedef std::map<String, CreateDocumentFn>  TFactoryMap;
    typedef TFactoryMap::iterator TFactoryMapIt;
    TFactoryMap                     m_FactoryMap;

            void        __fastcall  Register(const String& type, const String& subType, CreateDocumentFn pfnCreate);

public:
                        __fastcall  DocumentManager();
            Document*   __fastcall  Add(const String& type, const String& subType, const String& name);
            bool        __fastcall  Remove(const String& type, const String& name);
            void        __fastcall  DocumentFolders(std::vector<String>& folders) const;
};
//---------------------------------------------------------------------------
#define theDocumentManager DocumentManager::get()
//---------------------------------------------------------------------------
#endif
