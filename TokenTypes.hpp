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
        Token(Type t):type(t){}

        Type type;
    };
    typedef Token::Type TType;
    
    class IntLiteralToken : public Token
    {
    public:
        IntLiteralToken(int n):Token(TType::IntLiteral), data(n){}
        int data;
    };
    class StringLiteralToken : public Token
    {
    public:
        StringLiteralToken(std::string s):Token(TType::StringLiteral), data(s){}
        std::string data;
    };
    class SpecialLiteralToken : public Token
    {
    public:
        SpecialLiteralToken(std::string s):Token(TType::SpecialLiteral), data(s){}
        std::string data;
    };

    class KeywordToken : public Token
    {
    public:
        KeywordToken(std::string s):Token(TType::Keyword), data(s){}
        std::string data;
        //TODO: classify during construction
    };

    class IdentifierToken : public Token
    {
    public:
        IdentifierToken(std::string s): Token(TType::Identifier), data(s){}
        std::string data;
    };
    
    class PunctuationToken : public Token
    {
    public:
        PunctuationToken(std::string s): Token(TType::Punctuation), data(s){}
        std::string data;
    };
}
#endif