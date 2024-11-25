//---------------------------------------------------------------------------
#ifndef TokenH
#define TokenH
//---------------------------------------------------------------------------
namespace Importer
{
//---------------------------------------------------------------------------
class Token
{
private:
    int         m_Type;
    String      m_Value;

public:
    enum    TokenType    { ttEmpty = 0, ttSection = 1, ttNumber = 2, ttAscii = 4, ttWord = 8, ttString = 16, ttLine = 32, ttVariable = 64, ttArray = 128, ttInvalid = 256 };

                __fastcall  Token();
                __fastcall  Token(const Token& other);

    bool        __fastcall  ize(const String& part, bool first = false, bool incVars = false);
    bool        __fastcall  isa(int type) const;
    bool        __fastcall  isEmpty() const;
    String      __fastcall  toStr() const;

    TokenType   __property  Type     = { read = m_Type                   };
    String      __property  Value    = { read = m_Value, write = m_Value };
};
typedef std::list<Token> Tokens;
//---------------------------------------------------------------------------
} // namespace Importer
//---------------------------------------------------------------------------
#endif
