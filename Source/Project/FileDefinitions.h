//---------------------------------------------------------------------------
#ifndef FileDefinitionsH
#define FileDefinitionsH
//---------------------------------------------------------------------------
#include <vector>
#include "System/JsonFile.h"
//---------------------------------------------------------------------------
class FileDefinitions : public System::JsonFile
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
#endif
