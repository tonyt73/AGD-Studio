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

    bool        CreateMatchSets(const String& machine);
    bool        AddMatchSection(const String& variable, ImportDefinition::Matcher& match);
    Tokens      Tokenize(const String& line, const String& separator, bool incVars = false) const;

    bool        ParseToken(const Token& token);
    bool        ProcessSection(const Token& token);
    bool        ProcessValue(const Token& token);
    Tokens      ProcessLine(const String& line);
    Token       ReplaceVariableReferencesWithValues(Token token);
    void        ParseError(const String& message, Token token);
    void        ParseError(const String& message, Token lineToken, Token sectionToken);
    void        PopSection();
    String      SanitizeName(const String& name);

    void        SetVariable(const String& var, const String& value);

public:

                Parser();
               ~Parser();

    bool        Parse(const String& file, const String& machine);
};
//---------------------------------------------------------------------------
} // namespace Importer
//---------------------------------------------------------------------------
#endif
