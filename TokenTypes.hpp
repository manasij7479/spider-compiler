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
}
#endif