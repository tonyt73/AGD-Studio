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
    std::map<String, ImportDefinition::Matcher>             m_MatchSections;
    Tokens                                                  m_SectionTokens;
    String                                                  m_CurrentVariable;
    std::map<String, int>                                   m_VariableCounts;
    std::map<String, std::map<String, std::list<String>>>   m_Variables;
    std::map<String, std::map<String, int>>                 m_ArrayCounts;
    ImportDefinition::Matcher                               m_CurrentMatcher;

    bool        CreateMatchSets(const String& machine);
    bool        AddMatchSection(const String& variable, ImportDefinition::Matcher& match);
    Tokens      Tokenize(const String& line, const String& separator, bool incVars = false) const;

    bool        ParseToken(const Token& token);
    bool        ProcessSection(const Token& token);
    bool        ProcessValue(const Token& token);
    Tokens      ProcessLine(const String& line);
    Token       ReplaceVariableReferencesWithValues(Token token);
    void        ParseError(const String& message, Token token) const;
    void        ParseError(const String& message, Token lineToken, Token sectionToken) const;
    void        PopSectionToken();
    String      SanitizeName(const String& name) const;
    void        SetVariable(const String& var, const String& value);

public:
                Parser();

    bool        Parse(const String& file, const String& machine);
};
//---------------------------------------------------------------------------
} // namespace Importer
//---------------------------------------------------------------------------
#endif
