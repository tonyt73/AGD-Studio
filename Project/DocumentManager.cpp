//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ProjectDocument.h"
#include "TextDocuments.h"
#include "ImageDocuments.h"
#include "MapDocuments.h"
#include "DocumentManager.h"
#include "ProjectManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
DocumentManager& DocumentManager::get()
{
    static DocumentManager instance;
    return instance;
}
//---------------------------------------------------------------------------
__fastcall DocumentManager::DocumentManager()
{
    Register("Game", "Configuration", &ProjectDocument::Create);
    Register("Text", "Plain", &TextDocument::Create);
    Register("Text", "Event", &EventDocument::Create);
    Register("Image", "Single", &ImageDocument::Create);
    Register("Image", "Object", &ObjectDocument::Create);
    Register("Image", "Sprite", &SpriteDocument::Create);
    Register("Image", "Tile", &TileDocument::Create);
    //Register("Image", "TileSet", &TileSet::Create);
    //Register("Map", "Tiled", &TileMap::Create);
    Register("SoundFx", "List", &SfxDocument::Create);
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::Register(const String& type, const String& subType, CreateDocumentFn pfnCreate)
{
    m_FactoryMap[type+'.'+subType] = pfnCreate;
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentManager::Add(const String& type, const String& subType, const String& name)
{
    auto it = m_FactoryMap.find(type+'.'+subType);
    if (it != m_FactoryMap.end())
    {
        auto document = it->second();
        document->Name = name;
        if (document != nullptr)
        {
            auto dit = m_Documents.find(document->Type);
            if (dit != m_Documents.end())
            {
                // add the document to the list
                dit->second.push_back(document);
            }
            else
            {
                // create a new type list
                std::vector<Document*> documents;
                documents.push_back(document);
                m_Documents.emplace(std::make_pair(document->Type, documents));
            }
        }
        document->Load();
        theProjectManager.AddToTreeView(document);
        return document;
    }
    return nullptr;
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::DocumentFolders(std::vector<String>& folders) const
{
    for (auto it : m_FactoryMap)
    {
        auto doc = std::unique_ptr<Document>(it.second());
        auto folder = doc->Classification;
        if (std::find(folders.begin(), folders.end(), folder) == folders.end())
        {
            folders.push_back(doc->Classification);
        }
    }
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentManager::Get(const String& type, const String& subType, const String& name)
{
    auto it = m_Documents.find(type);
    if (it != m_Documents.end())
    {
        for (const auto& document : it->second)
        {
            if (document->SubType == subType && document->Name == name)
            {
                return document;
            }
        }
    }
    return nullptr;
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::Clear()
{
    m_Documents.clear();
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::Save()
{
    auto projectDocument = dynamic_cast<ProjectDocument*>(Get("Game","Configuration", System::Path::ProjectName));
    assert(projectDocument != nullptr);
    projectDocument->ClearFiles();
    // save all documents (except the project file) and add the document details to the project file
    for (const auto& documentType : m_Documents)
    {
        if (documentType.first != "Game")
        {
            for (const auto& document : documentType.second)
            {
                if (document->SubType != "Configuration")
                {
                    document->Save();
                    projectDocument->AddFile(System::File::NameWithExtension(document->File), document->Type, document->SubType);
                }
            }
        }
    }
    // now save the project file with all the document details included
    projectDocument->Save();
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::Load(const String& name)
{
    auto projectDocument = dynamic_cast<ProjectDocument*>(Get("Game","Configuration", name));
    assert(projectDocument != nullptr);
    for (const auto& fileInfo : projectDocument->Files())
    {
        Add(fileInfo.Type, fileInfo.SubType, System::File::NameWithoutExtension(fileInfo.Name));
    }
}
//---------------------------------------------------------------------------
