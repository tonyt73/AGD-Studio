//---------------------------------------------------------------------------
#include "AgdStudio.pch.h"
//---------------------------------------------------------------------------
#include "Token.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace Importer;
__fastcall Token::Token()
: m_Type(ttEmpty)
, m_Value("")
{
}
//---------------------------------------------------------------------------
__fastcall Token::Token(const Token& other)
: m_Type(other.Type)
, m_Value(other.Value)
{
}
//---------------------------------------------------------------------------
bool __fastcall Token::ize(const String& part, bool first)
{
    Type = ttEmpty;
    Value = "";

    if (part.Trim() != "") {
        auto number = StrToIntDef(part, -1);
        if (number != -1) {
            Type = ttNumber;
            Value = part;
        } else if (part.Length() == 3 && part[1] == '\'' && part[3] == '\'') {
            Type = ttAscii;
            Value = part;
        } else if (part[1] == '"') {
            Type = ttString;
            Value = part;
        } else {
            bool isAlpha = true;
            // check all characters are alphanumeric
            for (auto chr : part) isAlpha = isAlpha && (isalpha(chr) || isdigit(chr));
            if (isAlpha) {
                if (first) Type = ttSection;
                Type |= ttWord;
                Value = part.LowerCase();
            } else if (part.Pos("<") == 1 && part.Pos(">") > 0 && part.Pos(">") >= part.Length() - 2) {
                // is a variable definition (from the parser definition file)
                m_Type = ttVariable;
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
                if (Value.Pos("[") > 0 && Value.Pos("]") > Value.Pos("[")) {
                    // is also an array
                    Type |= ttArray;
                }
            } else {
                Type = ttInvalid;
                Value = part;
            }
        }
    }
    return Type != ttEmpty;
}
//---------------------------------------------------------------------------
bool __fastcall Token::isa(int type) const
{
    return (m_Type & type) != 0;
}
//---------------------------------------------------------------------------
bool __fastcall Token::isEmpty() const
{
    return Type == ttEmpty;
}
//---------------------------------------------------------------------------
String __fastcall Token::toStr() const
{
    String type = "";
    if (Type & ttSection) type += "ttSection "; // the first word of a line
    if (Type & ttNumber ) type += "ttNumber ";  // decimal or hexidecimal number
    if (Type & ttAscii  ) type += "ttAscii ";   // An ascii character within single quotes '<code>'
    if (Type & ttWord   ) type += "ttWord ";    // an alphanumeric single word
    if (Type & ttString ) type += "ttString ";  // text within double quotes "this is a string"
    if (Type & ttLine   ) type += "ttLine ";    // an entire line of text
    if (Type & ttArray  ) type += "ttArray ";   // array of the above types
    if (Type & ttInvalid) type += "ttInvalid "; // unknown token type

    type = StringReplace(type.Trim(), " ", "|", TReplaceFlags() << rfReplaceAll);
    String value = ", Value: " + Value;
    return "Type: " + type + value;
}
//---------------------------------------------------------------------------
