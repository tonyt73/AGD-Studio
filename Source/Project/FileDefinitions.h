//---------------------------------------------------------------------------
#ifndef FileDefinitionsH
#define FileDefinitionsH
//---------------------------------------------------------------------------
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


    void         Load();
    void         OnEndObject(const String& object);

    DefinitionList          m_Definitions;
    Definition              m_DefinitionLoader;

public:
                             FileDefinitions();

    const DefinitionList&    GetDefinitions() const;
};
//---------------------------------------------------------------------------
} // Project namespace
//---------------------------------------------------------------------------
#endif
