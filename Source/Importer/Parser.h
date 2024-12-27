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
public:
    typedef std::map<String, ImportDefinition::Matcher>         MatcherList;
    typedef std::map<String, std::list<String>>                 MapStringList;
    typedef std::map<String, MapStringList>                     VariablesList;
    typedef std::map<String, unsigned int>                      VariableCounts;
    typedef std::map<String, std::map<String, unsigned int>>    ArrayCounts;

private:
    MatcherList                 m_MatchSections;        // the list of matches from the import definition json file
    Tokens                      m_SectionTokens;        // the list of tokens to match up with the current section
    ImportDefinition::Matcher   m_CurrentMatcher;       // the section matcher we are currently using
    String                      m_CurrentVariable;      // the current variable that values are added to
    VariablesList               m_Variables;            // the list of variables as a result of parsing each section
    VariableCounts              m_VariableCounts;       // the number of times a variable is being instanced
    ArrayCounts                 m_ArrayCounts;          // the number of times an array within a variable has been added to

    bool                        CreateMatchSets(const String& machine);
    bool                        AddMatchSection(const String& variable, ImportDefinition::Matcher& match);
    Tokens                      Tokenize(const String& line, const String& separator, bool incVars = false) const;
    bool                        ParseToken(const Token& token);
    bool                        ProcessSection(const Token& token);
    bool                        ProcessValue(const Token& token);
    Tokens                      ProcessLine(const String& line);
    Token                       ReplaceVariableReferencesWithValues(Token token);
    void                        ParseError(const String& message, Token token) const;
    void                        ParseError(const String& message, Token lineToken, Token sectionToken) const;
    void                        PopSectionToken();
    String                      SanitizeName(const String& name) const;
    void                        SetVariable(const String& var, const String& value);

public:
                                Parser();

    bool                        Parse(const String& file, const String& machine);
    bool                        hasVariable(const String& variable);
    int                         GetVarCount(const String& variable);
    int                         GetArrayCount(const String& variable, const String& array);
    String                      PadNum(const String& string) const;

    __property   VariablesList& Variables = { read = m_Variables };
};
//---------------------------------------------------------------------------
} // namespace Importer
//---------------------------------------------------------------------------
#endif
