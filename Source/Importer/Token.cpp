//---------------------------------------------------------------------------
#include "AGD Studio.pch.h"
//---------------------------------------------------------------------------
#include "Token.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Importer;
Token::Token()
: m_Type(ttEmpty)
, m_Value("")
{
}
//---------------------------------------------------------------------------
Token::Token(const Token& other)
: m_Type(other.Type)
, m_Value(other.Value)
{
}
//---------------------------------------------------------------------------
bool Token::ize(const String& part, bool first, bool incVars)
{
    if (part.Trim() != "") {
        Value = part;
        m_Type = ttInvalid;
        auto number = StrToIntDef(part, -1);
        if (number != -1) {
            m_Type = ttNumber;
        } else if (part.Length() == 3 && part[1] == '\'' && part[3] == '\'') {
            m_Type = ttAscii;
        } else if (part[1] == '"') {
            m_Type = ttString;
        } else {
            bool isAlpha = true;
            // check all characters are alphanumeric
            for (auto chr : part) isAlpha = isAlpha && (isalpha(chr) || isdigit(chr));
            if (isAlpha) {
                m_Type = ttWord;
                m_Type |= first ? ttSection : 0;
                Value = part.LowerCase();
            } else if (incVars && part[1] == '<' && part[part.Length()] == '>' ) {
                // is a variable definition (from the parser definition file)
                m_Type = ttVariable | ttArray;
                auto varparts = SplitString(part.SubString(2, part.Pos(">") - 2), ":");
                auto vartypes = SplitString(varparts[0], ",");
                for (auto vartype : vartypes) {
                    if (vartype == "ascii") {
                        m_Type |= ttAscii;
                    } else if (vartype == "number") {
                        m_Type |= ttNumber;
                    } else if (vartype == "string") {
                        m_Type |= ttString;
                    } else if (vartype == "line") {
                        m_Type |= ttLine;
                    } else if (vartype == "word") {
                        m_Type |= ttWord;
                    }
                }
                // set variable name
                Value = varparts[1];
            }
        }
    }
    return m_Type != ttEmpty;
}
//---------------------------------------------------------------------------
bool Token::isa(int type) const
{
    return (m_Type & type) != 0;
}
//---------------------------------------------------------------------------
bool Token::isEmpty() const
{
    return m_Type == ttEmpty;
}
//---------------------------------------------------------------------------
String Token::toStr() const
{
    String type = "";
    if (m_Type & ttSection) type += "ttSection "; // the first word of a line
    if (m_Type & ttNumber ) type += "ttNumber ";  // decimal or hexidecimal number
    if (m_Type & ttAscii  ) type += "ttAscii ";   // An ascii character within single quotes '<code>'
    if (m_Type & ttWord   ) type += "ttWord ";    // an alphanumeric single word
    if (m_Type & ttString ) type += "ttString ";  // text within double quotes "this is a string"
    if (m_Type & ttLine   ) type += "ttLine ";    // an entire line of text
    if (m_Type & ttArray  ) type += "ttArray ";   // array of the above types
    if (m_Type & ttInvalid) type += "ttInvalid "; // invalid token type

    type = StringReplace(type.Trim(), " ", "|", TReplaceFlags() << rfReplaceAll);
    String value = ", Value: " + Value;
    return "Type: " + type + value;
}
//---------------------------------------------------------------------------
