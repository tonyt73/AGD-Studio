//---------------------------------------------------------------------------
#ifndef ImportDefinitionH
#define ImportDefinitionH
//---------------------------------------------------------------------------
#include "Services/JsonFile.h"
#include "Token.h"
//---------------------------------------------------------------------------
namespace Importer
{
//---------------------------------------------------------------------------
class ImportDefinition : public Services::JsonFile
{
public:
    struct Matcher
    {
        String  Pattern;
        Tokens  Tokens;
        String  Variable;
    };

private:
    struct SectionList
    {
        Matcher Window;
        Matcher ControlSet;
        Matcher Objects;
        Matcher Sprites;
        Matcher Blocks;
        Matcher Map;
        Matcher Font;
        Matcher Palette;
        Matcher Events;
        Matcher Messages;
        Matcher JumpTable;
        Matcher Screens;
        Matcher SpritePosition;
    };

    String              m_Name;
    String              m_Format;
    SectionList         m_Sections;

public:

    __property  const SectionList& Sections = { read = m_Sections    };

            __fastcall  ImportDefinition(const String& name);

    bool    __fastcall  Load(const String& name);
};
//---------------------------------------------------------------------------
} // namespace Importer
//---------------------------------------------------------------------------
#endif
