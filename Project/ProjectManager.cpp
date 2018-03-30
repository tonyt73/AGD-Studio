//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "ProjectManager.h"
#include "fEditorCode.h"
#include "fEditorImage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ProjectManager& ProjectManager::get()
{
    static ProjectManager instance;
    return instance;
}
//---------------------------------------------------------------------------
__fastcall ProjectManager::ProjectManager()
: m_TreeView(nullptr)
, m_Project(nullptr)
{
	m_MostRecentlyUsedList.push_back(MostRecentlyUsedItem("Big Sprite Demo", "AGDX Studio\\Big Sprite Demo"));
	m_MostRecentlyUsedList.push_back(MostRecentlyUsedItem("Sabre Wulf", "AGDX Studio\\Sabre Wulf"));
	m_MostRecentlyUsedList.push_back(MostRecentlyUsedItem("Space Invaders", "AGDX Studio\\Space Invaders"));
}
//---------------------------------------------------------------------------
__fastcall ProjectManager::~ProjectManager()
{
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::Initialise(Elxtree::TElXTree* treeView)
{
    m_TreeView = treeView;
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::RemoveMostRecentlyUsedItem(const String& name, const String& path)
{
	m_MostRecentlyUsedList.erase(std::remove_if(
		m_MostRecentlyUsedList.begin(),
		m_MostRecentlyUsedList.end(),
		[&](const MostRecentlyUsedItem& item) { return (item.Name == name && item.Path == path); }), m_MostRecentlyUsedList.end());
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::SetTreeIcon(const String& parent, TElXTreeItem* node) const
{
    auto caption = node->Text.LowerCase();
    node->ImageIndex = tiFolderClosed;
    int index = tiFolderOpened;
    if (parent.LowerCase() == "game")
    {
        if (caption == "code" || caption == "events")
        {
            index = tiFolderFile;
        }
    }
    else if (parent.LowerCase() == "assets")
    {
             if (caption == "sprites"   ) index = tiFolderSprites;
        else if (caption == "images"    ) index = tiFolderImages;
        else if (caption == "objects"   ) index = tiFolderImages;
        else if (caption == "music"     ) index = tiFolderMusic;
        else if (caption == "tiles"     ) index = tiFolderImages;
        else if (caption == "tile sets" ) index = tiFolderImages;
        //else if (caption == "patterns"  ) index = tiFolderPatterns;
        else if (caption == "maps"      ) index = tiFolderMaps;
        else if (caption == "sounds"    ) index = tiFolderSfx;
    }
    else
    {
        caption = node->Parent->Text.LowerCase();
             if (caption == "sprites"   ) index = tiAssetSprite;
        else if (caption == "images"    ) index = tiAssetImage;
        else if (caption == "objects"   ) index = tiAssetImage;
        else if (caption == "music"     ) index = tiAssetMusic;
        else if (caption == "tiles"     ) index = tiAssetTile;
        else if (caption == "tile sets" ) index = tiAssetTile;
        else if (caption == "maps"      ) index = tiAssetMap;
        else if (caption == "sounds"    ) index = tiAssetSfx;
        else if (caption == "configuration") index = tiConfiguration;
        else if (caption == "events"    ) index = tiConfiguration;
    }
    node->ImageIndex = index;
//    node->ExpandedImageIndex = index;
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::New(const String& name, const String& machine)
{
    if (m_TreeView)
    {
        if (m_Project == nullptr)
        {
            m_Project = std::make_unique<GameProject>(name, machine);
        }
        m_TreeLeafNodes.clear();
        m_TreeView->Items->Clear();
        m_TreeView->Items->Delete(m_TreeView->Items->Item[0]);
        m_TreeView->Items->Add(NULL, name);
        auto rootNode = m_TreeView->Items->Item[0];
        std::map<String, TElXTreeItem*> childRootNodes;
        std::vector<String> documentFolders;
        theDocumentManager.DocumentFolders(documentFolders);
        for (auto it : documentFolders)
        {
            auto folder = it;
            auto rootFolder = folder.SubString(0, folder.Pos("\\")-1);
            auto childFolder = folder.SubString(folder.Pos("\\")+1, folder.Length());
            auto nodeIt = childRootNodes.find(rootFolder);
            if (nodeIt == childRootNodes.end())
            {
                // add a new root node
                auto node = m_TreeView->Items->AddChild(rootNode, rootFolder);
                SetTreeIcon("root", node);
                auto childnode = m_TreeView->Items->AddChild(node, childFolder);
                SetTreeIcon(rootFolder, childnode);
                childRootNodes[rootFolder] = node;
                m_TreeLeafNodes[folder] = childnode;
            }
            else
            {
                // add to the root node
                auto childnode = m_TreeView->Items->AddChild(nodeIt->second, childFolder);
                SetTreeIcon(rootFolder, childnode);
                m_TreeLeafNodes[folder] = childnode;
            }
        }
        Add("Game", "Configuration", "Settings");
    }
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::Open(const String& file)
{
    m_Project = std::make_unique<GameProject>();
    if (m_Project->Load(file))
    {
        New(m_Project->Name, m_Project->Machine);
    }
}
//---------------------------------------------------------------------------
Document* __fastcall ProjectManager::AddToTreeView(Document* document)
{
    if (document)
    {
        auto folder = document->Folder;
        auto node = m_TreeView->Items->AddChild(m_TreeLeafNodes[folder], document->Name);
        auto childFolder = folder.SubString(folder.Pos("\\")+1, folder.Length());
        SetTreeIcon(childFolder, node);
        document->TreeNode = node;
        node->Tag = (NativeInt)(document);
        node->MakeVisible();
    }
    return document;
}
//---------------------------------------------------------------------------
Document* __fastcall ProjectManager::Add(const String& type, const String& subType, const String& name)
{
    return AddToTreeView(m_DocumentManager.Add(type, subType, name));
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::OnDocumentChange(Document* doc)
{
    // TODO: update the document properties
}
//---------------------------------------------------------------------------

