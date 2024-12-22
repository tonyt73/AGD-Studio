//---------------------------------------------------------------------------
#ifndef DocumentManagerH
#define DocumentManagerH
//---------------------------------------------------------------------------
#include "Document.h"
#include "Project.h"
#include "Templates/crc32c.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class DocumentManager
{
public: // singleton
    static DocumentManager& __fastcall get();
    DocumentManager(DocumentManager const&)     = delete;
    void operator=(DocumentManager const&)      = delete;

    // a list of tiles (unique, no duplicates)
    typedef std::vector<unsigned char>          ByteBuffer;
    class UniqueTile {
    private:
        wchar_t     m_BlockType;
        ByteBuffer  m_Data;
    public:
        UniqueTile(wchar_t type, ByteBuffer& buffer)
        : m_BlockType(type)
        , m_Data(buffer)
        {}

        __property wchar_t      BlockType = { read = m_BlockType };
        __property ByteBuffer   Data      = { read = m_Data      };
    };
    typedef std::vector<UniqueTile>             UniqueTiles;

private:
    // list of documents grouped by type
    typedef std::map<String, DocumentList>      DocumentMap;
    DocumentMap                                 m_Documents;

    // the document factory
    typedef std::map<String, CreateDocumentFn>  TFactoryMap;
    typedef TFactoryMap::iterator               TFactoryMapIt;
    TFactoryMap                                 m_FactoryMap;

    UniqueTiles                                 m_UniqueTiles;

    // refId tile mapping to unique tile index
    class MappedTile
    {
    public:
        unsigned int    m_TileIndex;
        unsigned int    m_Crc32c;
        wchar_t         m_BlockType;
        ByteBuffer      m_Data;
        int             m_Dx;
        int             m_Dy;

        MappedTile(wchar_t type, const ByteBuffer& buffer)
        : m_TileIndex(-1)
        , m_Crc32c(0)
        , m_BlockType(type)
        , m_Data(buffer)
        , m_Dx(0)
        , m_Dy(0)
        {
            // crc is a fast way to compare the buffer contents
            m_Crc32c = crc32c::calc(buffer);
        }

        MappedTile(wchar_t type, const ByteBuffer& buffer, int dx, int dy)
        : m_TileIndex(-1)
        , m_Crc32c(0)
        , m_BlockType(type)
        , m_Data(buffer)
        , m_Dx(dx)
        , m_Dy(dy)
        {
            m_Crc32c = crc32c::calc(buffer);
        }

        bool operator==(const MappedTile& other) const
        {
            return m_Crc32c == other.m_Crc32c && m_BlockType == other.m_BlockType;
        }
    };

    typedef std::map<unsigned int, std::vector<MappedTile>> MappedTiles;
    MappedTiles                 m_MappedTiles;

    void            __fastcall  Register(const String& type, const String& subType, CreateDocumentFn pfnCreate);

public:
                    __fastcall  DocumentManager();

    Document*       __fastcall  Add(const String& type, const String& subType, const String& name, const String& extra = "");
    bool            __fastcall  DoesNameExist(const String& name) const;
    String          __fastcall  NextName(const String& type, const String& subType) const;
    String          __fastcall  NextName(const String& name) const;
    bool            __fastcall  Remove(const String& type, const String& name);
    void            __fastcall  DocumentFolders(std::vector<String>& folders) const;
    Document*       __fastcall  Get(const String& type, const String& subType, const String& name) const;
    Document*       __fastcall  Get(unsigned int id) const;
    int             __fastcall  GetAsIndex(unsigned int id) const;
    int             __fastcall  GetIndexFor(unsigned int id, int dx, int dy);
 const UniqueTiles& __fastcall  MapUniqueTileIndexes();

    int             __fastcall  FindSameTile(const MappedTile& newTile);

   ProjectDocument* __fastcall  ProjectConfig() const;

    void            __fastcall  GetAllOfType(const String& type, DocumentList& list) const;
    bool            __fastcall  IsFirstOfType(const Document* document) const;

    void            __fastcall  Clear();
    void            __fastcall  Save();
    void            __fastcall  Load(const String& name);
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#define theDocumentManager Project::DocumentManager::get()
//---------------------------------------------------------------------------
#endif
