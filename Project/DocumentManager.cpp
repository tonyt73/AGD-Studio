//---------------------------------------------------------------------------
#include "agdx.pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "TextDocuments.h"
#include "ImageDocuments.h"
#include "MapDocuments.h"
#include "DocumentManager.h"
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
    Register("Text", "Plain", &TextDocument::Create);
    Register("Text", "Code", &CodeDocument::Create);
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
    TFactoryMapIt it = m_FactoryMap.find(type+'.'+subType);
    if (it != m_FactoryMap.end())
    {
        Document* document = it->second();
        document->Name = name;
        if (document != nullptr)
        {
            DocumentMapIt dit = m_Documents.find(document->Type);
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
        auto folder = doc->Folder;
        if (std::find(folders.begin(), folders.end(), folder) == folders.end())
        {
            folders.push_back(doc->Folder);
        }
    }
}
//---------------------------------------------------------------------------
