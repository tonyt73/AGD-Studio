//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
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
#include "Visuals/Image.h"
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
                auto docIt = std::find_if(dit->second.begin(), dit->second.end(), [&](const Document* doc) { return doc->Name == name; });
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
            Bus::Publish<DocumentAdded>(DocumentAdded(document));
        }
        document->Load();
        // assign an id if we don't have one, but need one
        document->AssignId();
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
                auto file = (*it)->File;
                Bus::Publish<DocumentChange<String>>(DocumentChange<String>("document.removing", (*it), name));
                delete (*it);
                dit->second.erase(it);
                InformationMessage("[DocumentManager] Removed Document '" + (*it)->Name + "' from Project");
                Bus::Publish<DocumentChange<String>>(DocumentChange<String>("document.removed", nullptr, name));
                Services::File::Delete(file);
                InformationMessage("[DocumentManager] Deleted Document file '" + (*it)->File + "' from Project folder");
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
            if (document->SubType == subType&& document->Name == name) {
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
// Used by oversized Tiles.
int __fastcall DocumentManager::GetIndexFor(unsigned int id, int dx, int dy)
{
    // ensure the MapUniqueTileIndexes() has been called and we have a list of mapped tiles
    if (m_MappedTiles.count(id) > 0) {
        // find the tile at the offset (dx,dy) required
        auto mappedTile = std::find_if(m_MappedTiles[id].begin(), m_MappedTiles[id].end(), [&](const DocumentManager::MappedTile& mt) { return (mt.m_Dx == dx && mt.m_Dy == dy); });
        if (mappedTile != m_MappedTiles[id].end()) {
            // unique tile found for the doc RefId and the offset
            return mappedTile->m_TileIndex;
        }
        // Document found, but no reference to the offset
        WarningMessage("Document ID: " + UIntToStr(id) + " was found in the Mapped Tiles list, but no reference to the offset (" + IntToStr(dx) + ", " + IntToStr(dy) + " was found in the Mapped Tiles entity list.");
        return -1;
    }
    // document, not found in the mapped tiles list.
    WarningMessage("Document ID: " + UIntToStr(id) + " was not found in the Mapped Tiles list.");
    return -1;
}
//---------------------------------------------------------------------------
int __fastcall DocumentManager::FindSameTile(const MappedTile& tile)
{
    for (auto const& [refId, list] : m_MappedTiles) {
        auto existingTile = std::find(list.begin(), list.end(), tile);
        if (existingTile != list.end()) {
            return existingTile->m_TileIndex;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
 const DocumentManager::UniqueTiles& __fastcall DocumentManager::MapUniqueTileIndexes()
{
    // clear the tile index map
    m_UniqueTiles.clear();
    m_MappedTiles.clear();
    // create the tile mappings
    //
    // get all the images
    DocumentList images;
    GetAllOfType("Image", images);
    // get the normal tile size
    const auto& mc = theDocumentManager.ProjectConfig()->MachineConfiguration();
    const auto& gm = *mc.GraphicsMode();
    auto ts = mc.ImageSizing[Visuals::itTile].Minimum;
    // map all the normal tiles first. Mapping RefId to Unique tile instances
    for (auto image : images) {
        auto imgDoc = dynamic_cast<ImageDocument*>(image);
        if (imgDoc->ImageType == Visuals::itTile && imgDoc->Width == ts.cx && imgDoc->Height == ts.cy) {
            auto visualImage = std::make_unique<Visuals::Image>(imgDoc, gm);
            visualImage->ChangeFrame(0);
            // create a possible new unique tile
            auto bt = imgDoc->GetLayer("blocktype");
            assert(bt.Length() > 0);
            auto mappedTile = MappedTile(static_cast<wchar_t>(bt[1] - '0'), visualImage->GetExportNativeFormat());
            // check it is unique
            auto sameAsTileIndex = FindSameTile(mappedTile);
            if (sameAsTileIndex == -1) {
                // tile is unique, assign it a new tile index
                mappedTile.m_TileIndex = static_cast<unsigned int>(m_UniqueTiles.size());
                // and add it to our unqiue tiles map
                m_UniqueTiles.push_back(UniqueTile(mappedTile.m_BlockType, mappedTile.m_Data));
            } else {
                // copy the index of the tile we are the same as
                mappedTile.m_TileIndex = sameAsTileIndex;
            }
            // map refId's to a tile (only ever 1 item in the list)
            m_MappedTiles[imgDoc->Id] = { mappedTile };
        }
    }

    // now convert the oversized tiles to single tiles, replacing the duplicate instances with the existing single ones
    for (auto image : images) {
        auto imgDoc = dynamic_cast<ImageDocument*>(image);
        if (imgDoc->ImageType == Visuals::itTile && (imgDoc->Width > ts.cx || imgDoc->Height > ts.cy)) {
            auto visualImage = std::make_unique<Visuals::Image>(imgDoc, gm);
            visualImage->ChangeFrame(0);
            // create a possible new unique tile
            auto bt = imgDoc->GetLayer("blocktype");
            assert(bt.Length() > 0);
            // start with a blank unique tiles list
            m_MappedTiles[imgDoc->Id] = {};
            // loop over the height and width of the tile set
            for (int y = 0; y < imgDoc->Height; y += ts.cy) {
                for (int x = 0; x < imgDoc->Width; x += ts.cx) {
                    // calculate the block type index, there should be a block type per single tile block. so 2x2 is 4 block types.
                    int bti = (x / ts.cx) + ((y / ts.cy) * (imgDoc->Width / ts.cx));
                    // sometimes, the block type might be only 1 block, in which case apply it to all blocks in the tile set.
                    bti = std::min(bt.Length(), bti);
                    // create a mapped tile with the block type and the section of the tile set at (x,y,w,h)
                    auto mappedTile = MappedTile(static_cast<wchar_t>(bt[bti+1] - '0'), visualImage->GetExportNativeFormat(TRect(x, y, x + ts.cx, y + ts.cy)), x, y);
                    // is it the same as an existing unique tile?
                    auto sameAsTileIndex = FindSameTile(mappedTile);
                    if (sameAsTileIndex == -1) {
                        // no, tile is unique, assign it a new tile index
                        mappedTile.m_TileIndex = static_cast<unsigned int>(m_UniqueTiles.size());
                        // and add it to our unqiue tiles map
                        m_UniqueTiles.push_back(UniqueTile(mappedTile.m_BlockType, mappedTile.m_Data));
                    } else {
                        // yes, copy the index of the tile we are the same as
                        mappedTile.m_TileIndex = sameAsTileIndex;
                    }
                    // add the newly mapped tile to the list
                    m_MappedTiles[imgDoc->Id].push_back(mappedTile);
                }
            }
        }
    }
    InformationMessage("[DocumentManager] Found " + UIntToStr(m_MappedTiles.size()) + " defined tiles and " + UIntToStr(m_UniqueTiles.size()) + " are unique.");

    return m_UniqueTiles;
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

