#ifndef TOKEN_TYPES_HPP
#define TOKEN_TYPES_HPP
#include <string>
namespace spc
{
    class Token
    {
    public:
        enum class Type 
        {
            IntLiteral,
            StringLiteral,
            SpecialLiteral,
            Identifier,
            Punctuation,
            Keyword
        };
        Token(Type t, int l):type(t), line(l){}

        Type type;
        int line;
    };
    typedef Token::Type TType;
    
    class IntLiteralToken : public Token
    {
    public:
        IntLiteralToken(int n, int l):Token(TType::IntLiteral, l), data(n){}
        int data;
    };
    class StringLiteralToken : public Token
    {
    public:
        StringLiteralToken(std::string s, int l):Token(TType::StringLiteral, l), data(s){}
        std::string data;
    };
    class SpecialLiteralToken : public Token
    {
    public:
        SpecialLiteralToken(std::string s, int l):Token(TType::SpecialLiteral, l), data(s){}
        std::string data;
    };

    class KeywordToken : public Token
    {
    public:
        KeywordToken(std::string s, int l):Token(TType::Keyword, l), data(s){}
        std::string data;
        //TODO: classify during construction
    };

    class IdentifierToken : public Token
    {
    public:
        IdentifierToken(std::string s, int l): Token(TType::Identifier, l), data(s){}
        std::string data;
    };
    
    class PunctuationToken : public Token
    {
    public:
        PunctuationToken(std::string s, int l): Token(TType::Punctuation, l), data(s){}
        std::string data;
    };
}
#endif