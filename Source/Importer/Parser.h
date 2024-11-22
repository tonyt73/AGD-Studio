//---------------------------------------------------------------------------
#ifndef ParserH
#define ParserH
//---------------------------------------------------------------------------
#include <list>
#include <map>
#include "ImportDefinition.h"
//---------------------------------------------------------------------------
namespace Importer
{
//---------------------------------------------------------------------------
class Parser
{
private:
    struct ParseSection
    {
        ParseSection::ParseSection()
        : Section("")
        , Repeats(false)
        {
        }
        ParseSection::ParseSection(bool repeats)
        : Section("")
        , Repeats(repeats)
        {
        }

        String  Section;
        bool    Repeats;
    };

    struct Variable
    {
        String  Name;

    };


    std::map<String, ImportDefinition::Matcher>             m_MatchSections;
    Tokens                                                  m_SectionTokens;
    bool                                                    m_CollectingLines;
    std::list<String>                                       m_LineCollection;
    int                                                     m_ArrayCount;
    String                                                  m_CurrentVariable;
    std::map<String, int>                                   m_VariableCounts;
    std::map<String, std::map<String, std::list<String>>>   m_Variables;
    std::map<String, std::map<String, int>>                 m_ArrayCounts;

    enum    fsm { fsmSectionName, fsmSection, fsmValueElement, fsmList } m_ParserState;



    void        CreateMatchSets(const String& machine);
    void        AddMatchSection(ImportDefinition::Matcher& match);
    Tokens      Tokenize(const String& line, const String& separator) const;

    bool        ParseToken(const Token& token);
    bool        ProcessSection(const Token& token);
    bool        ProcessValue(const Token& token);
    bool        ProcessLine(const String& line, const Token& token);
    void        UpdateParameters();

public:

                Parser();
               ~Parser();

    bool        Parse(const String& file, const String& machine);
};
//---------------------------------------------------------------------------
} // namespace Importer
//---------------------------------------------------------------------------
#endif
