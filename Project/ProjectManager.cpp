//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
#include "ProjectManager.h"
#include "fEditorCode.h"
#include "fEditorImage.h"
#include "ProjectDocument.h"
#include "FileDefinitions.h"
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
{
}
//---------------------------------------------------------------------------
__fastcall ProjectManager::~ProjectManager()
{
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::Initialise(Elxtree::TElXTree* treeView)
{
    m_TreeView = treeView;
    m_MostRecentUsedList = std::make_unique<MostRecentlyUsedList>();
}
//---------------------------------------------------------------------------
cMRUList __fastcall ProjectManager::GetMostRecentlyUsedList() const
{
    return m_MostRecentUsedList->GetList();
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::RemoveMostRecentlyUsedItem(const String& name, const String& path)
{
    m_MostRecentUsedList->Remove(name, path);
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
        else if (caption == "sounds"    ) index = tiFolderSfx;
    }
    else if (parent.LowerCase() == "images")
    {
             if (caption == "sprites"      ) index = tiFolderSprites;
        else if (caption == "images"       ) index = tiFolderImages;
        else if (caption == "objects"      ) index = tiFolderImages;
        else if (caption == "character set") index = tiFolderImages;
        else if (caption == "music"        ) index = tiFolderMusic;
        else if (caption == "tiles"        ) index = tiFolderImages;
        else if (caption == "tile sets"    ) index = tiFolderImages;
        else if (caption == "maps"         ) index = tiFolderMaps;
    }
    else
    {
        caption = node->Parent->Text.LowerCase();
             if (caption == "sprites"      ) index = tiAssetSprite;
        else if (caption == "images"       ) index = tiAssetImage;
        else if (caption == "objects"      ) index = tiAssetImage;
        else if (caption == "music"        ) index = tiAssetMusic;
        else if (caption == "tiles"        ) index = tiAssetTile;
        else if (caption == "character set") index = tiAssetImage;
        else if (caption == "tile sets"    ) index = tiAssetTile;
        else if (caption == "maps"         ) index = tiAssetMap;
        else if (caption == "sounds"       ) index = tiAssetSfx;
        else if (caption == "events"       ) index = tiConfiguration;
        else if (caption == "messages"     ) index = tiConfiguration;
        else if (caption == "configuration") index = tiConfiguration;
    }
    node->ImageIndex = index;
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::New(const String& name, const String& machine)
{
    System::Path::ProjectName = name;
    Close();
    if (m_TreeView)
    {
        ClearTree(name);
        // create a new project file, but load the file if it exists
        auto config = dynamic_cast<ProjectDocument*>(Add("Game", "Configuration", name, machine));
        assert(config != nullptr);
        if (config->Files().size() == 0)
        {
            auto definitions = std::make_unique<FileDefinitions>();
            for (const auto& definition : definitions->GetDefinitions())
            {
                Add("Text", definition.Type, definition.Filename);
            }
        }
        else
        {
            theDocumentManager.Load(name);
        }
        m_MostRecentUsedList->Remove(name, config->Path);
        m_MostRecentUsedList->Add(name, config->Path, config->Machine);
    }
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::Open(const String& file)
{
    Close();
    auto name = System::File::NameWithoutExtension(file);
    System::Path::ProjectName = name;
    ClearTree(name);
    theDocumentManager.Clear();
    // create a new project file and load the file
    auto config = dynamic_cast<ProjectDocument*>(Add("Game", "Configuration", name));
    assert(config != nullptr);
    // get the document manager to load all the files from the project file
    theDocumentManager.Load(name);
    m_MostRecentUsedList->Remove(name, file);
    m_MostRecentUsedList->Add(name, file, config->Machine);
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::Save()
{
    theDocumentManager.Save();
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::Close()
{
    Save();
    theDocumentManager.Clear();
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::ClearTree(const String& rootName)
{
    m_TreeLeafNodes.clear();
    m_TreeView->Items->Clear();
    m_TreeView->Items->Delete(m_TreeView->Items->Item[0]);
    m_TreeView->Items->Add(NULL, rootName);
    auto rootNode = m_TreeView->Items->Item[0];
    std::map<String, TElXTreeItem*> childRootNodes;
    // get the list of document folders we support
    std::vector<String> documentFolders;
    theDocumentManager.DocumentFolders(documentFolders);
    // now create them as a tree view hierarchy
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
}
//---------------------------------------------------------------------------
Document* __fastcall ProjectManager::AddToTreeView(Document* document)
{
    if (document)
    {
        auto folder = document->Classification;
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
Document* __fastcall ProjectManager::Add(const String& type, const String& subType, const String& name, const String& extra)
{
    return theDocumentManager.Add(type, subType, theDocumentManager.NextName(name), extra);
}
//---------------------------------------------------------------------------
Document* __fastcall ProjectManager::Add(const String& type, const String& subType)
{
    return theDocumentManager.Add(type, subType, theDocumentManager.NextName(type, subType));
}
//---------------------------------------------------------------------------
bool __fastcall ProjectManager::Remove(const String& type, const String& name)
{
    return theDocumentManager.Remove(type, name);
}
//---------------------------------------------------------------------------
void __fastcall ProjectManager::OnDocumentChange(Document* doc)
{
    // TODO: update the document properties
    // theProjectManager.AddToTreeView(document);
}
//---------------------------------------------------------------------------

