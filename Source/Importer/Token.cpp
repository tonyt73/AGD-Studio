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
            for (auto chr : part) {
                isAlpha = isAlpha && isalpha(chr);
            }
            if (isAlpha) {
                if (first) {
                    Type = ttSection;
                }
                Type |= ttWord;
                Value = part.LowerCase();
            } else if (part.Pos("<") == 1 && part.Pos(">") >= part.Length() - 2) {
                // is a variable definition
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
                    } else if (vartype == "lines") {
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
    if (Type & ttSection) type += "ttSection ";
    if (Type & ttNumber ) type += "ttNumber ";
    if (Type & ttAscii  ) type += "ttAscii ";
    if (Type & ttWord   ) type += "ttWord ";
    if (Type & ttString ) type += "ttString ";
    if (Type & ttLine   ) type += "ttLine ";
    if (Type & ttArray  ) type += "ttArray ";
    if (Type & ttLoop   ) type += "ttLoop ";
    if (Type & ttInvalid) type += "ttInvalid ";

    type = StringReplace(type.Trim(), " ", "|", TReplaceFlags() << rfReplaceAll);
    String value = ", Value: " + Value;
    return "Type: " + type + value;
}
//---------------------------------------------------------------------------
