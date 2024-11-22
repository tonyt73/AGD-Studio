//---------------------------------------------------------------------------
#include <AgdStudio.pch.h>
//---------------------------------------------------------------------------
#include <cctype>
#include "Parser.h"
#include "Services/File.h"
#include "Project/Documents/DocumentManager.h"
//---------------------------------------------------------------------------
#include "Parser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Importer;
//---------------------------------------------------------------------------
Parser::Parser()
: m_ParserState(fsmSectionName)
, m_CollectingLines(false)
, m_CurrentVariable("")
{
}
//---------------------------------------------------------------------------
Parser::~Parser()
{
}
//---------------------------------------------------------------------------
void Parser::CreateMatchSets(const String& machine)
{
    // Create the pattern match sets
    auto id = std::make_unique<ImportDefinition>(machine);
    id->Load(machine);
    AddMatchSection(id->Sections.Window);
    AddMatchSection(id->Sections.JumpTable);
    AddMatchSection(id->Sections.Controls);
    AddMatchSection(id->Sections.Objects);
    AddMatchSection(id->Sections.Sprites);
    AddMatchSection(id->Sections.Blocks);
    AddMatchSection(id->Sections.Font);
    AddMatchSection(id->Sections.Palette);
    AddMatchSection(id->Sections.Events);
    AddMatchSection(id->Sections.Messages);
    AddMatchSection(id->Sections.Screens);
    AddMatchSection(id->Sections.Map);
}
//---------------------------------------------------------------------------
void Parser::AddMatchSection(ImportDefinition::Matcher& matcher)
{
    // find the section name from the match pattern
    auto lcp = matcher.Pattern.LowerCase();
    auto ep = lcp.Pos("=");
    auto variable = lcp.SubString(1, ep - 1);
    auto pattern = lcp.SubString(ep + 1, lcp.Length());
    String sectionName = "";
    for (int i = 1; i <= pattern.Length(); i++) {
        if (!isalpha(pattern[i])) {
            sectionName = pattern.SubString(1, i - 1).LowerCase();
            break;
        }
    }

    if (sectionName != "") {
        // tokenize the matcher patterns for use during parsing
        matcher.Tokens = Tokenize(pattern, "^");
        matcher.Variable = variable;
        m_MatchSections[sectionName] = matcher;
    } else {
        // TODO: Error
        int a = 0;
    }
}
//---------------------------------------------------------------------------
Tokens Parser::Tokenize(const String& line, const String& separator) const
{
    Tokens tokens;
    auto parts = SplitString(line.Trim(), separator);
    bool first = true;
    Token token;
    for (auto part : parts) {
        if (token.ize(part, first)) {
            // token
            tokens.push_back(token);
        } else {
            // blank line
            // if processing string list, then add to string list
        }
        first = false;
    }
    return tokens;
}
//---------------------------------------------------------------------------
bool Parser::Parse(const String& file, const String& machine)
{
    CreateMatchSets(machine);

    if (m_MatchSections.size() == 0) {
        // ERROR: no pattern matchers created, machine not supported
        return false;
    }

    bool result = true;
    // parse the lines
    // Load the file
    auto lines = Services::File::ReadLines(file);
    // tokens to match for the section
    for (auto line : lines) {
        // are we collecting lines?
        auto lineTokens = Tokenize(line, " ");
        if (!ProcessLine(line, lineTokens.front())) {
            // no, tokenise the current line tokens against the current section tokens
            while (!lineTokens.empty()) {
                // parse the current token
                if (ParseToken(lineTokens.front())) {
                    // if parsed successfully, move to the next one
                    lineTokens.pop_front();
                } else {
                    result = false;
                    return result;
                }
            }
        }
    }
    return result;
}
//---------------------------------------------------------------------------
bool Parser::ParseToken(const Token& token)
{
    switch (token.Type) {
        case Token::ttSection:
        {
            return ProcessSection(token);
        }
        case Token::ttWord:
        case Token::ttNumber:
        case Token::ttAscii:
        {
            return ProcessValue(token);
        }
    }
    return false;
}
//---------------------------------------------------------------------------
bool Parser::ProcessSection(const Token& token)
{
    if (m_CurrentVariable != "") {
        // finish up the previous section processing
        auto secVar   = m_SectionTokens.front().Value;
        auto curvar   = m_Variables[m_CurrentVariable][secVar];
        auto curcount = curvar.size();
        auto reqcount = m_ArrayCounts[m_CurrentVariable][secVar];
        if (m_ArrayCounts[m_CurrentVariable][secVar] > 0 && curcount == reqcount) {
            // finish up processing the array
            //m_SectionTokens.pop_front();
        }

    }
    // do we have a token matcher for the token value (name)?
    auto name = token.Value.LowerCase();
    if (m_MatchSections.count(name) == 1) {
        // get the tokens to match for the new section
        m_SectionTokens = m_MatchSections[name].Tokens;
        if (m_SectionTokens.front().isa(token.Type)) {
            auto varname = m_MatchSections[name].Variable;
            if (varname.Pos("sprite") > 0) {
                int a = 0;
            }
            if (varname[varname.Length()] == 's') {
                if (m_VariableCounts.count(varname) == 0) {
                    m_VariableCounts[varname] = 0;
                }
                m_VariableCounts[varname] = m_VariableCounts[varname] + 1;
                varname += IntToStr(m_VariableCounts[varname]);
            }
            m_CurrentVariable = varname;
            m_SectionTokens.pop_front();
            return true;
        } else {
            // ERROR: Invalid token type found. Should never happen.
            int a = 0;
        }
    }
    // ERROR: Invalid section name
    return false;
}
//---------------------------------------------------------------------------
bool Parser::ProcessValue(const Token& token)
{
    if (m_CurrentVariable.Pos("sprite") > 0) {
        int a = 0;
    }
    // get the current section token
    auto sectionToken = m_SectionTokens.front();
    if (sectionToken.isa(Token::ttVariable) && sectionToken.isa(token.Type)) {
        // replace var= with their respective values
        UpdateParameters();
        sectionToken = m_SectionTokens.front();
        auto secVar = sectionToken.Value;
        // add value to the variable
        m_Variables[m_CurrentVariable][secVar].push_back(token.Value);
        // move to the next section token
        if (sectionToken.isa(Token::ttArray)) {
            sectionToken = m_SectionTokens.front();
            secVar = sectionToken.Value;
            if (m_ArrayCounts.count(m_CurrentVariable) == 0 || m_ArrayCounts[m_CurrentVariable].count(secVar) == 0) {
                // validate the number of items
                int count = 0;
                if (secVar.Pos("[..]") == 0) {
                    // find the size of the array
                    count = 1;
                    auto bl = secVar.Pos('[');
                    auto br = secVar.Pos(']');
                    if (br > bl) {
                        auto size = secVar.SubString(bl + 1, br - bl - 1);
                        auto sizes = SplitString(size, ",");
                        for (auto s : sizes) {
                            count *= StrToInt(s);
                        }
                    }
                }
                m_ArrayCounts[m_CurrentVariable][secVar] = count;
            }
            auto curcount = m_Variables[m_CurrentVariable][secVar].size();
            auto reqcount = m_ArrayCounts[m_CurrentVariable][secVar];
            if (m_ArrayCounts[m_CurrentVariable][secVar] > 0 && curcount == reqcount) {
                // finish up processing the array
                m_SectionTokens.pop_front();
            }
        } else {
            m_SectionTokens.pop_front();
        }
        return true;
    } else {
        // ERROR: Token is not variable that can use the line token
    }
    return false;
}
//---------------------------------------------------------------------------
bool Parser::ProcessLine(const String& line, const Token& token)
{
    if (token.Type == Token::ttSection) {
        m_CollectingLines = false;
        // TODO: Finish up collection
        // ie. Complete event or messages
    }
    if (m_CollectingLines) {
        // add line to collection
        m_LineCollection.push_back(line);
    }
    return m_CollectingLines;
}
//---------------------------------------------------------------------------
void Parser::UpdateParameters()
{
    auto token = m_SectionTokens.front();
    bool replaced = true;
    while (token.Value.Pos("var=") > 0 && replaced) {
        replaced = false;
        auto name = token.Value;
        for (auto var = m_Variables[m_CurrentVariable].begin(); var != m_Variables[m_CurrentVariable].end(); var++) {
            if (name.Pos(var->first) > 0) {
                name = StringReplace(token.Value, "var="+var->first, var->second.front(), TReplaceFlags());
                token.Value = name;
                m_SectionTokens.pop_front();
                m_SectionTokens.push_front(token);
                replaced = true;
            }
        }
        if (!replaced) {
            // variable not found
            int a = 0;
            break;
        }
        // TODO: Breakout if no replacements are occuring - infinite loop!
    }
}
//---------------------------------------------------------------------------

