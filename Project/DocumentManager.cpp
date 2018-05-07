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
#include "Messaging/Messaging.h"
#include "Messaging/Event.h"
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
    //Register("Text", "Plain", &TextDocument::Create);
    Register("Text", "Event", &EventDocument::Create);
    Register("Text", "Message", &MessageDocument::Create);
    //Register("Image", "Single", &ImageDocument::Create);
    Register("Image", "Object", &ObjectDocument::Create);
    Register("Image", "Sprite", &SpriteDocument::Create);
    Register("Image", "Tile", &TileDocument::Create);
    Register("Image", "Character Set", &CharacterSetDocument::Create);
    //Register("Image", "TileSet", &TileSet::Create);
    //Register("Map", "Tiled", &TileMap::Create);
    Register("Text", "SoundFx", &SfxDocument::Create);

    ::Messaging::Bus::Subscribe<OnImport<String>>(OnImportString);
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::Register(const String& type, const String& subType, CreateDocumentFn pfnCreate)
{
    m_FactoryMap[type+'.'+subType] = pfnCreate;
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentManager::Add(const String& type, const String& subType, const String& name, const String& extra)
{
    auto it = m_FactoryMap.find(type+'.'+subType);
    if (it != m_FactoryMap.end())
    {
        auto document = it->second(name, extra);
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
bool __fastcall DocumentManager::Remove(const String& type, const String& name)
{
    auto dit = m_Documents.find(type);
    if (dit != m_Documents.end())
    {
        for (auto it = dit->second.begin(); it != dit->second.end(); it++)
        {
            if ((*it)->Name == name)
            {
                delete (*it);
                dit->second.erase(it);
                return true;
            }
        }
    }
    // wrong type? or not found
    return false;
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::DocumentFolders(std::vector<String>& folders) const
{
    for (auto it : m_FactoryMap)
    {
        auto doc = std::unique_ptr<Document>(it.second("unnamed",""));
        auto folder = doc->Classification;
        if (std::find(folders.begin(), folders.end(), folder) == folders.end())
        {
            folders.push_back(doc->Classification);
        }
    }
}
//---------------------------------------------------------------------------
ProjectDocument* __fastcall DocumentManager::ProjectConfig() const
{
    const auto file = System::Path::ProjectName;
    auto doc = Get("Game","Configuration", file);
    if (doc != nullptr)
        return dynamic_cast<ProjectDocument*>(doc);
    return nullptr;
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentManager::Get(const String& type, const String& subType, const String& name) const
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
    for (auto documentType : m_Documents)
    {
        for (auto document : documentType.second)
        {
            delete document;
        }
    }
    m_Documents.clear();
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::Save()
{
    auto projectDocument = dynamic_cast<ProjectDocument*>(Get("Game","Configuration", System::Path::ProjectName));
    if (projectDocument)
    {
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
        // save other files (eg. text files)
        ::Messaging::Bus::Publish<Event>(Event("project.save"));
    }
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
void __fastcall DocumentManager::OnImportString(const OnImport<String>& event)
{
    if (event.Id.Pos("event.") == 0)
    {
        auto eventName = event.Id.SubString(5, event.Id.Length() - 5);
        auto document = dynamic_cast<TextDocument*>(Get("Text", "Event", eventName));
        if (document)
        {
            document->Add(event.Value);
        }
    }
    else if (event.Id == "messages")
    {
        auto document = dynamic_cast<TextDocument*>(Get("Text", "Message", "Messages"));
        if (document)
        {
            document->Add(event.Value);
        }
    }
}
//---------------------------------------------------------------------------
String __fastcall DocumentManager::NextName(const String& type, const String& subType) const
{
    auto i = 1;
    String name = subType + " " + IntToStr(i);
    auto it = m_Documents.find(type);
    if (it != m_Documents.end())
    {
        auto exists = false;
        do
        {
            exists = false;
            name = subType + " " + IntToStr(i);
            for (const auto& document : it->second)
            {
                exists |= (document->SubType == subType && document->Name == name);
            }
            i++;
        }
        while (exists);
    }
    return name;
}
//---------------------------------------------------------------------------
bool __fastcall DocumentManager::DoesNameExist(const String& name) const
{
    for (const auto& docsOfType : m_Documents)
    {
        for (const auto& doc : docsOfType.second)
        {
            if (name.LowerCase() == doc->Name.LowerCase())
            {
                return true;
            }
        }
    }
    return false;
}
//---------------------------------------------------------------------------
String __fastcall DocumentManager::NextName(const String& name) const
{
    if (!DoesNameExist(name))
    {
        return name;
    }
    auto i = 1;
    String nextName = "";
    do
    {
        nextName = name + " " + IntToStr(i++);
    }
    while (DoesNameExist(nextName));
    return nextName;
}
//---------------------------------------------------------------------------

