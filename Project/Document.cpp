//---------------------------------------------------------------------------
#include "agdx.pch.h"
//---------------------------------------------------------------------------
#include "Document.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall Document::Document()
: m_Name("Unnamed")
, m_Type("No Type")
, m_SubType("No SubType")
, m_MultiDoc(false)
, m_Folder("Misc\\Files")
, m_TreeNode(nullptr)
, m_DockPanel(nullptr)
{
    m_Type = "Document";
    RegisterProperty("Name", "Object", "The name of the asset/document");
}
//---------------------------------------------------------------------------
void __fastcall Document::RegisterProperty(const String& property, const String& category, const String& info)
{
    m_PropertyInfo[property] = { category, info };
}
//---------------------------------------------------------------------------
const Document::TPropertyInfoMap& __fastcall Document::GetPropertyInfo() const
{
    return m_PropertyInfo;
}
//---------------------------------------------------------------------------
String __fastcall Document::GetPropertyInfo(const String& property) const
{
    auto info = m_PropertyInfo.find(property);
    if (info != m_PropertyInfo.end())
    {
        return info->second.info;
    }
    return "Invalid property";
}
//---------------------------------------------------------------------------
__fastcall DocumentSet::DocumentSet()
{
    m_MultiDoc = true;
}
//---------------------------------------------------------------------------
void __fastcall DocumentSet::Clear()
{
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentSet::Add()
{
    return theDocumentManager.Add(m_Type, m_SubType, Name);
}
//---------------------------------------------------------------------------
void __fastcall DocumentSet::Remove(int index)
{
}
//---------------------------------------------------------------------------
void __fastcall DocumentSet::Remove(const String& name)
{
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentSet::Get(int index)
{
    return nullptr;
}
//---------------------------------------------------------------------------
Document* __fastcall DocumentSet::Get(const String& name)
{
    return nullptr;
}
//---------------------------------------------------------------------------
int __fastcall DocumentSet::GetCount()
{
    return m_Documents.size();
}
//---------------------------------------------------------------------------
__fastcall Text::Text()
: Document()
{
    m_Type = "Text";
    m_SubType = "Plain";
    m_Folder = "Assets\\Files";
    RegisterProperty("Name", "Object", "The name of the document");
    RegisterProperty("Filename", "File", "The name and path of the file");
}
//---------------------------------------------------------------------------
__fastcall TextCode::TextCode()
: Text()
{
    m_SubType = "Code";
    m_Folder = "Game\\Code";
    RegisterProperty("Name", "Object", "The name of the source code file");
}
//---------------------------------------------------------------------------
__fastcall TextEvent::TextEvent()
: Text()
{
    m_SubType = "Event";
    m_Folder = "Game\\Events";
    RegisterProperty("Name", "Object", "The name of the event source code file");
}
//---------------------------------------------------------------------------
__fastcall TextSoundFx::TextSoundFx()
: Text()
{
    m_SubType = "SoundFx";
    m_Folder = "Assets\\Sounds";
    RegisterProperty("Name", "Object", "The name of the SoundFx definitions file");
}
//---------------------------------------------------------------------------
__fastcall Image::Image()
: Document()
{
    m_Type = "Image";
    m_SubType = "Single";
    m_Folder = "Assets\\Images";
    RegisterProperty("Name", "Object", "The name of the image");
    RegisterProperty("Width", "Dimensions", "The width in pixels of the image");
    RegisterProperty("Height", "Dimensions", "The height in pixels of the image");
}
//---------------------------------------------------------------------------
__fastcall ImageSet::ImageSet()
: DocumentSet()
{
    m_Folder = "Assets\\Images";
    m_Type = "Image";
    m_SubType = "Set";
    RegisterProperty("Name", "Object", "The name of the image set");
    RegisterProperty("Width", "Dimensions", "The width in pixels of the images in the set");
    RegisterProperty("Height", "Dimensions", "The height in pixels of the images in the set");
}
//---------------------------------------------------------------------------
__fastcall Sprite::Sprite()
: ImageSet()
{
    m_SubType = "Sprite";
    m_Folder = "Assets\\Sprites";
    RegisterProperty("Name", "Object", "The name of the sprite");
//    RegisterProperty("Width", "Dimensions", "The width in pixels of the sprite");
//    RegisterProperty("Height", "Dimensions", "The height in pixels of the sprite");
}
//---------------------------------------------------------------------------
__fastcall Object::Object()
: Image()
{
    m_SubType = "Object";
    m_Folder = "Assets\\Objects";
    RegisterProperty("Name", "Object", "The name of the object");
//    RegisterProperty("Width", "Dimensions", "The width in pixels of the object");
//    RegisterProperty("Height", "Dimensions", "The height in pixels of the object");
}
//---------------------------------------------------------------------------
__fastcall Tile::Tile()
: Image()
{
    m_SubType = "Tile";
    m_Folder = "Assets\\Tiles";
    RegisterProperty("Name", "Object", "The name of the tile");
}
//---------------------------------------------------------------------------
__fastcall TileSet::TileSet()
: ImageSet()
{
    m_SubType = "TileSet";
    m_Folder = "Assets\\Tile Sets";
    RegisterProperty("Name", "Object", "The name of the tile set");
    RegisterProperty("TileWidth", "Dimensions", "The width in pixels of the tiles in the set");
    RegisterProperty("TileHeight", "Dimensions", "The height in pixels of the tiles in the set");
    RegisterProperty("IsTransparent", "Visual", "Indicates if the images are transparent or not");
    RegisterProperty("TransparentColor", "Visual", "The color of transparent pixels");
}
//---------------------------------------------------------------------------
__fastcall TileMap::TileMap()
: Document()
{
    m_Type = "Map";
    m_SubType = "Tile";
    m_Folder = "Assets\\Maps";
    RegisterProperty("Name", "Object", "The name of the map");
    RegisterProperty("Across", "Dimensions", "The width in screens accross of the map");
    RegisterProperty("Down", "Dimensions", "The height in Screens down of the map");
    RegisterProperty("WindowWidth", "Dimensions", "The width in character blocks of the map window");
    RegisterProperty("WindowHeight", "Dimensions", "The height in character blocks of the map window");
    RegisterProperty("BackgroundColor", "Visual", "The color of the background when no tile is present");
}
//---------------------------------------------------------------------------
__fastcall ProjectFile::ProjectFile()
: Document()
{
    m_Type = "Game";
    m_SubType = "Configuration";
    m_Folder = "Game\\Configuration";
    RegisterProperty("Name", "Object", "The name of your game");
    RegisterProperty("Author", "Details", "Your name");
    RegisterProperty("Version", "Details", "The version of your game");
}


//---------------------------------------------------------------------------
DocumentManager& DocumentManager::get()
{
    static DocumentManager instance;
    return instance;
}
//---------------------------------------------------------------------------
__fastcall DocumentManager::DocumentManager()
{
    Register("Game", "Configuration", &ProjectFile::Create);
    Register("Text", "Plain", &Text::Create);
    //Register("Text", "Code", &TextCode::Create);
    Register("Text", "Event", &TextEvent::Create);
    //Register("Image", "Single", &Image::Create);
    Register("Image", "Object", &Object::Create);
    Register("Image", "Sprite", &Sprite::Create);
    Register("Image", "Tile", &Tile::Create);
    //Register("Image", "TileSet", &TileSet::Create);
    Register("Map", "Tile", &TileMap::Create);
    Register("SoundFx", "List", &TextSoundFx::Create);
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
            folders.push_back(doc->Folder);
    }
}
//---------------------------------------------------------------------------

