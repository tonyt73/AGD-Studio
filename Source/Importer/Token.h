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
    int         m_Type;     // the combination of types the token represents
    String      m_Value;    // the value the token contains
                            //  importers store definitions/patterns here
                            //  the imported file contains values
public:
    enum        TokenType   { ttEmpty = 0, ttSection = 1, ttNumber = 2, ttAscii = 4, ttWord = 8, ttString = 16, ttLine = 32, ttVariable = 64, ttArray = 128, ttInvalid = 256 };

                Token();
                Token(const Token& other);

    bool        ize(const String& part, bool first = false, bool incVars = false);
    bool        isa(int type) const;
    bool        isEmpty() const;
    String      toStr() const;

    TokenType   __property  Type     = { read = m_Type                   };
    String      __property  Value    = { read = m_Value, write = m_Value };
};
typedef std::list<Token> Tokens;
//---------------------------------------------------------------------------
} // namespace Importer
//---------------------------------------------------------------------------
#endif
