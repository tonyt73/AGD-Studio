//---------------------------------------------------------------------------
#ifndef FileDefinitionsH
#define FileDefinitionsH
//---------------------------------------------------------------------------
#include <vector>
#include "Services/JsonFile.h"
//---------------------------------------------------------------------------
namespace Project
{
//---------------------------------------------------------------------------
class FileDefinitions : public Services::JsonFile
{
public:
    struct Definition
    {
        String  Filename;
        String  Section;
        String  Type;
    };
    typedef std::vector<Definition> DefinitionList;

private:


    void        __fastcall  Load();
    void        __fastcall  OnEndObject(const String& object);

    DefinitionList          m_Definitions;
    Definition              m_DefinitionLoader;

public:
                            __fastcall  FileDefinitions();

    const DefinitionList&   __fastcall  GetDefinitions() const;
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
