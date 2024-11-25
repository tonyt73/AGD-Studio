//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "../ProjectManager.h"
#include "DocumentManager.h"
#include "CharacterSet.h"
#include "Controls.h"
#include "JumpTable.h"
#include "Object.h"
#include "Project.h"
#include "Sprite.h"
#include "Text.h"
#include "Tile.h"
#include "TiledMap.h"
#include "Window.h"
#include "Settings.h"
#include "Messaging/Event.h"
#include "Messaging/Messaging.h"
#include "Services/File.h"
#include "Services/Folders.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Project;
//---------------------------------------------------------------------------
DocumentManager& __fastcall DocumentManager::get()
{
    static DocumentManager instance;
    return instance;
}
//---------------------------------------------------------------------------
__fastcall DocumentManager::DocumentManager()
{
    Register("Game"    , "Configuration", &ProjectDocument::Create     );
    Register("Image"   , "Character Set", &CharacterSetDocument::Create);
    Register("Image"   , "Object"       , &ObjectDocument::Create      );
    Register("Image"   , "Sprite"       , &SpriteDocument::Create      );
    Register("Image"   , "Tile"         , &TileDocument::Create        );
    Register("Map"     , "Tiled"        , &TiledMapDocument::Create    );
    Register("Text"    , "AGD"          , &AGDDocument::Create         );
    Register("Text"    , "Assembly"     , &AssemblyDocument::Create    );
    Register("Text"    , "Event"        , &EventDocument::Create       );
    Register("Text"    , "Plain"        , &TextDocument::Create        );
    Register("Text"    , "SoundFx"      , &SfxDocument::Create         );
    Register("Text"    , "Messages"     , &MessageDocument::Create     );
    Register("Window"  , "Definition"   , &WindowDocument::Create      );
    Register("Jump"    , "Table"        , &JumpTableDocument::Create   );
    Register("Controls", "List"         , &ControlsDocument::Create    );
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::Register(const String& type, const String& subType, CreateDocumentFn pfnCreate)
{
    m_FactoryMap[type + '.' + subType] = pfnCreate;
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentManager::Add(const String& type, const String& subType, const String& name, const String& extra)
{
    auto docCreate = m_FactoryMap.find(type + '.' + subType);
    if (docCreate != m_FactoryMap.end()) {
        auto document = docCreate->second(name, extra);
        if (document != nullptr) {
            auto dit = m_Documents.find(document->Type);
            if (dit != m_Documents.end()) {
                auto docIt = std::find_if(dit->second.begin(), dit->second.end(), [&](const Document* document) { return document->Name == name; });
                if (docIt != dit->second.end()) {
                    return *docIt;
                }
                // add the document to the list
                dit->second.push_back(document);
            } else {
                // create a new type list
                std::vector<Document*> documents;
                documents.push_back(document);
                m_Documents.emplace(std::make_pair(document->Type, documents));
            }
            Bus::Publish<Event>(Event("document.added"));
        }
        document->Load();
        // assign an id if we don't have one, but need one
        document->AssignId();
        theProjectManager.AddToTreeView(document);
        InformationMessage("[DocumentManager] Added Document '" + document->Name + "' to Project");
        return document;
    }
    return nullptr;
}
//---------------------------------------------------------------------------
bool __fastcall DocumentManager::Remove(const String& type, const String& name)
{
    auto dit = m_Documents.find(type);
    if (dit != m_Documents.end()) {
        for (auto it = dit->second.begin(); it != dit->second.end(); it++) {
            if ((*it)->Name == name) {
                Bus::Publish<DocumentChange<String>>(DocumentChange<String>("document.removing", (*it), name));
                delete (*it);
                dit->second.erase(it);
                InformationMessage("[DocumentManager] Removed Document '" + (*it)->Name + "' from Project");
                Bus::Publish<DocumentChange<String>>(DocumentChange<String>("document.removed", nullptr, name));
                return true;
            }
        }
    }
    WarningMessage("[DocumentManager] Tried to remove Document of Type '" + type + "' and Name '" + name + "', but document was not found in Project");
    // wrong type? or not found
    return false;
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::DocumentFolders(std::vector<String>& folders) const
{
    for (auto it : m_FactoryMap) {
        auto doc = std::unique_ptr<Document>(it.second(Unnamed, ""));
        auto folder = doc->Classification;
        if (std::find(folders.begin(), folders.end(), folder) == folders.end()) {
            folders.push_back(doc->Classification);
        }
    }
}
//---------------------------------------------------------------------------
ProjectDocument* __fastcall DocumentManager::ProjectConfig() const
{
    const auto file = Services::Folders::ProjectName;
    auto doc = Get("Game", "Configuration", file);
    if (doc != nullptr)
        return dynamic_cast<ProjectDocument*>(doc);
    return nullptr;
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentManager::Get(const String& type, const String& subType, const String& name) const
{
    auto it = m_Documents.find(type);
    if (it != m_Documents.end()) {
        for (const auto& document : it->second) {
            if (document->SubType == subType && document->Name == name) {
                return document;
            }
        }
    }
    return nullptr;
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentManager::Get(unsigned int id) const
{
    if (id != InvalidDocumentId) {
        for (const auto& docTypes : m_Documents) {
            for (const auto& doc : docTypes.second) {
                if (doc->Id == id)
                    return doc;
            }
        }
    }
    return nullptr;
}
//---------------------------------------------------------------------------
int __fastcall DocumentManager::GetAsIndex(unsigned int id) const
{
    const auto& document = Get(id);
    if (document != nullptr) {
        auto type = document->Type;
        auto subType = document->SubType;
        int i = 0;
        auto it = m_Documents.find(type);
        if (it != m_Documents.end())
            for (const auto& doc : it->second) {
                if (doc->Id == id) {
                    return i;
                }
                i += (doc->SubType == subType) ? 1 : 0;
            }
    }
    return -1;
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::Clear()
{
    Save();
    for (auto documentType : m_Documents) {
        for (auto document : documentType.second) {
            document->Close();
            delete document;
        }
    }
    m_Documents.clear();
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::Save()
{
    auto projectDocument = dynamic_cast<ProjectDocument*>(Get("Game", "Configuration", Services::Folders::ProjectName));
    if (projectDocument) {
        projectDocument->ClearFiles();
        // save all documents (except the project file) and add the document details to the project file
        for (const auto& documentType : m_Documents) {
            for (const auto& document : documentType.second) {
                if (document->Type == "Game" && document->SubType == "Configuration")
                    continue;
                document->Save();
                projectDocument->AddFile(Services::File::NameWithExtension(document->File), document->Type, document->SubType);
            }
        }
        // if supported; load any changed palette mappings
        projectDocument->MachineConfiguration().GraphicsMode()->SaveLogicalCLUT();
        // now save the project file with all the document details included
        projectDocument->Save();
        // save other files (eg. text files)
        Bus::Publish<Event>(Event("project.save"));
        InformationMessage("[DocumentManager] Saved all Project files");
    }
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::Load(const String& name)
{
    auto start = TDateTime::CurrentTime();
    InformationMessage("[DocumentManager] Loading Project '" + name + "'");
    auto projectDocument = dynamic_cast<ProjectDocument*>(Get("Game", "Configuration", name));
    assert(projectDocument != nullptr);
    for (const auto& fileInfo : projectDocument->Files()) {
        Bus::Publish<Event>(Event("project.loading.tick"));
        InformationMessage("[DocumentManager] Loading Project file '" + fileInfo.Type + "." + fileInfo.SubType + "." + fileInfo.Name + "'");
        Add(fileInfo.Type, fileInfo.SubType, fileInfo.Name);
    }
    auto end = TDateTime::CurrentTime();
    auto ms = (end - start).FormatString("zzz");
    InformationMessage("[DocumentManager] Project '" + name + "' Loaded in " + ms + "ms");
    theAppSettings.LastProject = name;
}
//---------------------------------------------------------------------------
String __fastcall DocumentManager::NextName(const String& type, const String& subType) const
{
    auto i = 1;
    String name = subType + " " + IntToStr(i);
    auto it = m_Documents.find(type);
    if (it != m_Documents.end()) {
        auto exists = false;
        do {
            exists = false;
            name = subType + " " + IntToStr(i++);
            for (const auto& document : it->second) {
                exists |= (document->SubType == subType && document->Name == name);
            }
        } while (exists);
    }
    return name;
}
//---------------------------------------------------------------------------
bool __fastcall DocumentManager::DoesNameExist(const String& name) const
{
    for (const auto& docsOfType : m_Documents) {
        for (const auto& doc : docsOfType.second) {
            if (name.LowerCase() == doc->Name.LowerCase()) {
                return true;
            }
        }
    }
    return false;
}
//---------------------------------------------------------------------------
String __fastcall DocumentManager::NextName(const String& name) const
{
    if (!DoesNameExist(name)) {
        return name;
    }
    auto i = 1;
    String nextName = "";
    do {
        nextName = name + " " + IntToStr(i++);
    } while (DoesNameExist(nextName));
    return nextName;
}
//---------------------------------------------------------------------------
void __fastcall DocumentManager::GetAllOfType(const String& type, DocumentList& list) const
{
    auto dit = m_Documents.find(type);
    if (dit != m_Documents.end()) {
        list = dit->second;
    }
}
//---------------------------------------------------------------------------
bool __fastcall DocumentManager::IsFirstOfType(const Document* document) const
{
    auto dit = m_Documents.find(document->Type);
    if (dit != m_Documents.end()) {
        for (const auto& doc : dit->second) {
            if (document->Type == doc->Type && document->SubType == doc->SubType) {
                return doc == document;
            }
        }
    }
    return false;
}
//---------------------------------------------------------------------------

