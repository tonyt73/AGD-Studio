//---------------------------------------------------------------------------
#ifndef ProjectManagerH
#define ProjectManagerH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <memory>
#include "ElXTree.hpp"
//---------------------------------------------------------------------------
#include <list>
//---------------------------------------------------------------------------
#include "Project/DocumentManager.h"
#include "Project/ProjectDocument.h"
//---------------------------------------------------------------------------
using namespace Project;
class ProjectManager
{
public: // singleton
    static ProjectManager& get();
    ProjectManager(ProjectManager const&) = delete;
    void operator=(ProjectManager const&) = delete;

public:
    class MostRecentlyUsedItem
    {
    public:
        String  Name;
        String  Path;

        MostRecentlyUsedItem(String name, String path)
        : Name(name)
        , Path(path)
        {
        }
    };
    typedef std::list<MostRecentlyUsedItem> MRUList;
    typedef const MRUList cMRUList;

private:

    enum TreeviewIcons { tiProject,
                         tiFolderClosed, tiFolderOpened,
                         tiFolderFile, tiFolderSprites, tiFolderMusic, tiFolderSfx, tiFolderPatterns, tiFolderTileSets, tiFolderMaps, tiFolderImages,
                         tiBuild, tiConfiguration,
                         tiFileC, tiFileH, tiFileAsm,
                         tiAssetSprite, tiAssetMusic, tiAssetSfx, tiAssetPattern, tiAssetTile, tiAssetMap, tiAssetImage
                       };

    std::map<String, TElXTreeItem*> m_TreeLeafNodes;

    MRUList                         m_MostRecentlyUsedList;
    DocumentManager                 m_DocumentManager;
    Elxtree::TElXTree*              m_TreeView;
    std::unique_ptr<ProjectDocument>m_Project;

    void        __fastcall  SetTreeIcon(const String& parent, TElXTreeItem* node) const;


protected:
                  friend    DocumentManager;
    void        __fastcall  OnDocumentChange(Document* doc);
    Document*   __fastcall  AddToTreeView(Document* document);

public:

                __fastcall  ProjectManager();
                __fastcall ~ProjectManager();
    void        __fastcall  Initialise(Elxtree::TElXTree* treeView);

    void        __fastcall  New(const String& name, const String& machine);
    void        __fastcall  Open(const String& file);
    Document*   __fastcall  Add(const String& type, const String& subType, const String& name);

    void        __fastcall  RemoveMostRecentlyUsedItem(const String& name, const String& path);

    cMRUList    __property  MostRecentlyUsedList = { read = m_MostRecentlyUsedList };
};
//---------------------------------------------------------------------------
#define theProjectManager ProjectManager::get()
//---------------------------------------------------------------------------
#endif
