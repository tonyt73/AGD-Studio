//---------------------------------------------------------------------------
#ifndef ProjectManagerH
#define ProjectManagerH
//---------------------------------------------------------------------------
#include "ElXTree.hpp"
//---------------------------------------------------------------------------
#include "DocumentManager.h"
#include "MostRecentlyUsedList.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class ProjectManager
{
public: // singleton
    static ProjectManager& get();
    ProjectManager(ProjectManager const&) = delete;
    void operator=(ProjectManager const&) = delete;

private:

    std::unique_ptr<MostRecentlyUsedList>   m_MostRecentUsedList;

    enum TreeviewIcons { tiProject,
                         tiFolderClosed, tiFolderOpened,
                         tiFolderFile, tiFolderSprites, tiFolderMusic, tiFolderSfx, tiFolderPatterns, tiFolderTileSets, tiFolderMaps, tiFolderImages,
                         tiBuild, tiConfiguration,
                         tiFileC, tiFileH, tiFileAsm,
                         tiAssetSprite, tiAssetMusic, tiAssetSfx, tiAssetPattern, tiAssetTile, tiAssetMap, tiAssetImage,
                         tiWindow, tiKeyboard, tiText, tiFileAgd, tiFileFont
                       };

    std::map<String, TElXTreeItem*> m_TreeLeafNodes;
    Elxtree::TElXTree*              m_TreeView;
    bool                            m_IsOpen;

    void         SetTreeIcon(const String& parent, TElXTreeItem* node) const;

protected:
                  friend    DocumentManager;
    void         OnDocumentChange(Document* doc);
    void         ClearTree(const String& rootName);
    Document*    AddToTreeView(Document* document);

public:

                 ProjectManager();

    void         Initialise(Elxtree::TElXTree* treeView);
    void         New(const String& name, const String& machine);
    void         Open(const String& file);
    void         Close();
    void         Save();

    Document*    Add(const String& type, const String& subType, const String& name, const String& extra);
    Document*    Add(const String& type, const String& subType, const String& extra);
    bool         Remove(const String& type, const String& name);

    void         RemoveMostRecentlyUsedItem(const String& name, const String& path);
    cMRUList     GetMostRecentlyUsedList();
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#define theProjectManager Project::ProjectManager::get()
//---------------------------------------------------------------------------
#endif
