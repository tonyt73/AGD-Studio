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
bool Parser::CreateMatchSets(const String& machine)
{
    // Create the pattern match sets
    auto id = std::make_unique<ImportDefinition>(machine);
    bool result = id->Load(machine);
    if (result) {
        result &= AddMatchSection("window"         , id->Sections.Window         );
        result &= AddMatchSection("jumptable"      , id->Sections.JumpTable      );
        result &= AddMatchSection("controlset"     , id->Sections.ControlSet     );
        result &= AddMatchSection("objects"        , id->Sections.Objects        );
        result &= AddMatchSection("sprites"        , id->Sections.Sprites        );
        result &= AddMatchSection("blocks"         , id->Sections.Blocks         );
        result &= AddMatchSection("font"           , id->Sections.Font           );
        result &= AddMatchSection("palette"        , id->Sections.Palette        );
        result &= AddMatchSection("events"         , id->Sections.Events         );
        result &= AddMatchSection("messagelist"    , id->Sections.Messages       );
        result &= AddMatchSection("screens"        , id->Sections.Screens        );
        result &= AddMatchSection("spriteposition" , id->Sections.SpritePosition);
        result &= AddMatchSection("map"            , id->Sections.Map            );
    } else {
        ErrorMessage("[Importer] Failed to load a file parser definition for machine. " + machine);
    }
    return result;
}
//---------------------------------------------------------------------------
bool Parser::AddMatchSection(const String& variable, ImportDefinition::Matcher& matcher)
{
    // find the section name from the match pattern
    auto lcp = matcher.Pattern.LowerCase();
    String sectionName = "";
    for (int i = 1; i <= lcp.Length(); i++) {
        if (!isalpha(lcp[i])) {
            sectionName = lcp.SubString(1, i - 1).LowerCase();
            break;
        }
    }

    if (sectionName != "") {
        // tokenize the matcher patterns for use during parsing
        matcher.Tokens = Tokenize(lcp, " ", true);
        matcher.Variable = variable.LowerCase();
        m_MatchSections[sectionName] = matcher;
    } else {
        ErrorMessage("[Importer] Section '" + variable + "' match pattern in parser definition file is invalid.");
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
Tokens Parser::Tokenize(const String& line, const String& separator, bool incVars) const
{
    Tokens tokens;
    // section names must start on pos 1 and be an alpha character only
    bool couldBeSectionName = line.Length() > 1 && isalpha(line[1]);
    auto parts = SplitString(line.Trim(), separator);
    Token token;
    for (auto part : parts) {
        if (token.ize(part, couldBeSectionName, incVars)) {
            tokens.push_back(token);
        }
        if (incVars && token.isa(Token::ttInvalid)) {
            ErrorMessage("Importer definition match pattern is invalid");
            ErrorMessage("[Importer] Line: " + line);
        }
        couldBeSectionName = false;
    }
    return tokens;
}
//---------------------------------------------------------------------------
bool Parser::Parse(const String& file, const String& machine)
{
    if (CreateMatchSets(machine)) {
        // Load the file
        InformationMessage("[Importer] Importing AGD : " + file);
        InformationMessage("[Importer] Import Machine: " + machine);
        auto lines = Services::File::ReadLines(file);
        // parse the lines
        auto lc = 1;
        for (auto line : lines) {
            auto lineTokens = ProcessLine(line);
            // no, tokenise the current line tokens against the current section tokens
            while (!lineTokens.empty()) {
                // parse the current token
                if (ParseToken(lineTokens.front())) {
                    // if parsed successfully, move to the next one
                    lineTokens.pop_front();
                } else {
                    ErrorMessage("[Importer] Failed to parse line in file: " + file);
                    ErrorMessage("[Importer] Line: " + IntToStr(lc) + ": " + line);
                    return false;
                }
            }
            lc++;
        }
        InformationMessage("[Importer] Import completed successfully");
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool Parser::ParseToken(const Token& token)
{
    if (token.isa(Token::ttSection) && ProcessSection(token)) {
        return true;
    }
    if (ProcessValue(token)) {
        return true;
    }
    ParseError("Invalid token type found in AGD file.", token);
    return false;
}
//---------------------------------------------------------------------------
bool Parser::ProcessSection(const Token& token)
{
    auto name = token.Value.LowerCase();
    if (m_SectionTokens.size() > 0 && m_SectionTokens.front().isa(Token::ttArray)) {
        // we stop processing arrays here.
        PopSection();
        // keep processing if more tokens exists
        if (m_SectionTokens.size() > 0) {
            // false means we'll fall through to processing value tokens
            // the occurence of this for now is the ENDMAP word match
            return false;
        }
    }
    // do we have a token matcher for the token value (name)?
    if (m_MatchSections.count(name) == 1) {
        // get the tokens to match for the new section
        m_SectionTokens = m_MatchSections[name].Tokens;
        // are the compatible?
        if (m_SectionTokens.front().isa(token.Type)) {
            auto varname = m_MatchSections[name].Variable;
            // variable names with an 's' indicate an array (multiple sections named SPRITE or BLOCK etc)
            if (varname[varname.Length()] == 's') {
                // so we set an array counter for the variable
                if (m_VariableCounts.count(varname) == 0) {
                    m_VariableCounts[varname] = 0;
                }
                m_VariableCounts[varname] = m_VariableCounts[varname] + 1;
                // add the instance count to the variables name (ie. SPRITE1, SPRITE2 etc)
                varname += IntToStr(m_VariableCounts[varname]);
            }
            // change to the new variable
            m_CurrentVariable = varname.LowerCase();
            // pop the section token
            PopSection();
            InformationMessage("[Importer] Starting Section: " + varname);
            return true;
        } else {
            ParseError("Invalid token type found in section match pattern.", token, m_SectionTokens.front());
            return false;
        }
    }
    ParseError("Invalid section name.", token);
    return false;
}
//---------------------------------------------------------------------------
bool Parser::ProcessValue(const Token& token)
{
    if (m_SectionTokens.size() == 0) return true;
    // get the current section token
    auto sectionToken = m_SectionTokens.front();
    // replace variable references with their respective values
    sectionToken = ReplaceVariableReferencesWithValues(sectionToken);
    // check it is a variable and excepts the same type as the line token
    auto secVar = SanitizeName(sectionToken.Value);
    if (sectionToken.isa(token.Type)) {
        if (sectionToken.isa(Token::ttVariable)) {
            // set(single)/add(array) value from line token to the section variable
            SetVariable(secVar, token.Value);
            // are we processing an array?
            if (sectionToken.isa(Token::ttArray)) {
                // yes, then we keep the section token until all array elements are read
                if (m_ArrayCounts.count(m_CurrentVariable) == 0 || m_ArrayCounts[m_CurrentVariable].count(secVar) == 0) {
                    // validate the number of items
                    int count = 0;
                    // find the size of the array
                    auto bl = sectionToken.Value.Pos('[');
                    auto br = sectionToken.Value.Pos(']');
                    if (br > bl) {
                        count = 1;
                        auto size = sectionToken.Value.SubString(bl + 1, br - bl - 1);
                        auto sizes = SplitString(size, ",");
                        for (auto s : sizes) {
                            count *= StrToInt(s);
                        }
                    } else {
                        ParseError("Mismatched array brackets in match pattern.", sectionToken);
                        return false;
                    }
                    m_ArrayCounts[m_CurrentVariable][secVar] = count;
                }
                // do we have all the array elements required?
                auto curcount = m_Variables[m_CurrentVariable][secVar].size();
                auto reqcount = m_ArrayCounts[m_CurrentVariable][secVar];
                if (m_ArrayCounts[m_CurrentVariable][secVar] > 0 && (curcount == reqcount || reqcount == 1)) {
                    // yes, move to the next section token
                    PopSection();
                }
            } else {
                // no, single variable, move to the next section token
                InformationMessage("[Importer] Variable set: " + secVar + " = " + token.Value);
                PopSection();
            }
        } else {
            // consume a word instead of a section at the start of a line
            if (token.isa(Token::ttWord) && token.Value.LowerCase() == secVar) {
                PopSection();
                return true;
            }
            ParseError("Expected a Word token", token, sectionToken);
            return false;
        }
        return true;
    }
    if (sectionToken.isa(Token::ttLine)) {
        // any other tokens, while in line capture mode
        return true;
    }
    ParseError("Tokens mismatch. ", token, sectionToken);
    return false;
}
//---------------------------------------------------------------------------
Tokens Parser::ProcessLine(const String& line)
{
    // tokenize the line
    Tokens tokens = Tokenize(line, " ");
    // is the first token is not a section match and we are processing lines
    if (tokens.size() && m_MatchSections.count(tokens.front().Value) == 0 && m_SectionTokens.front().isa(Token::ttLine)) {
        // then add to the line array
        SetVariable(m_SectionTokens.front().Value, line);
        // a line comsumes all the remaining tokens
        tokens.clear();
    }
    // return our line tokens
    return tokens;
}
//---------------------------------------------------------------------------
Token Parser::ReplaceVariableReferencesWithValues(Token token)
{
    bool replaced = true;
    auto secVar = token.Value.LowerCase();
    while (secVar.Pos("var=") > 0 && replaced) {
        replaced = false;
        // look for the variable name in the list of known variables so far
        for (auto vars = m_Variables.begin(); vars != m_Variables.end(); vars++ ) {
            for (auto var = vars->second.begin(); var != vars->second.end(); var++) {
                // if our current section variable contains a known variable, then we can replace the reference with the variables actual value
                if (secVar.Pos(var->first) > 0) {
                    // replace "var=var.name", with the value "var.value"
                    token.Value = StringReplace(token.Value, "var="+var->first, var->second.front(), TReplaceFlags());
                    secVar = token.Value.LowerCase();
                    replaced = true;
                }
            }
        }
        if (!replaced) {
            ParseError("Variable in Parser match pattern, not found or set.", token);
            break;
        }
    }
    // substitute in the variable list counts {'var name'}
    if (token.Value.Pos("}") > token.Value.Pos("{")) {
        auto hp = token.Value.Pos("{");
        auto dp = token.Value.Pos("}");
        auto varName = SanitizeName(token.Value.SubString(hp + 1, dp - hp - 1));
        auto number = IntToStr(m_VariableCounts[varName]);
        token.Value = StringReplace(token.Value, "{" + varName + "}", number, TReplaceFlags());
    }
    // return the processed token
    return token;
}
//---------------------------------------------------------------------------
void Parser::ParseError(const String& message, Token token)
{
    ErrorMessage("[Importer] " + message);
    ErrorMessage("[Importer] token: " + token.toStr());
}
//---------------------------------------------------------------------------
void Parser::ParseError(const String& message, Token lineToken, Token sectionToken)
{
    ErrorMessage("[Importer] " + message);
    ErrorMessage("[Importer] AGD file token: " + lineToken.toStr());
    ErrorMessage("[Importer] Parser token  : " + sectionToken.toStr());
}
//---------------------------------------------------------------------------
void Parser::PopSection()
{
    auto sectionToken = m_SectionTokens.front();
    if (sectionToken.isa(Token::ttArray)) {
        // replace var= with their respective values
        sectionToken = ReplaceVariableReferencesWithValues(sectionToken);
        // check it is a variable and excepts the same type as the line token
        auto secVar = SanitizeName(sectionToken.Value);
        int curcount = m_Variables[m_CurrentVariable][secVar].size();
        String type = " bytes";
        if (m_SectionTokens.front().isa(Token::ttString|Token::ttLine)) {
            type = " lines";
        }
        InformationMessage("[Importer] Array '" + secVar + "' is " + IntToStr(curcount) + type);
    }
    m_SectionTokens.pop_front();
    if (m_SectionTokens.size() == 0) {
        InformationMessage("[Importer] Finished Section: " + m_CurrentVariable);
    }
}
//---------------------------------------------------------------------------
String Parser::SanitizeName(const String& name)
{
    // variable names are lower case
    auto newName = name.LowerCase();
    // remove the array dimensions
    auto pos = name.Pos("[");
    if (pos > 1) {
        newName = name.SubString(1, pos - 1);
    }
    // sanitized
    return newName;
}
//---------------------------------------------------------------------------
void Parser::SetVariable(const String& var, const String& value)
{
    m_Variables[m_CurrentVariable][SanitizeName(var)].push_back(value);
}
//---------------------------------------------------------------------------

