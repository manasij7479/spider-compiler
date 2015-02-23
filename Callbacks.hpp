#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP
#include "TokenTypes.hpp"
#include "GlobalState.hpp"
#include <stdexcept>
using namespace spc;
void scanInt(std::string str, int line)
{
    Tokens.push_back(new IntLiteralToken(std::stoi(str), line));
}
void scanString(std::string str, int line)
{
    Tokens.push_back(new StringLiteralToken(str, line));
}
void scanSpecial(std::string str, int line)
{
    Tokens.push_back(new SpecialLiteralToken(str, line));
}
void scanIdentifier(std::string str, int line)
{
    Tokens.push_back(new IdentifierToken(str, line));
}
void scanPunctuation(std::string str, int line)
{
    Tokens.push_back(new PunctuationToken(str, line));
}

void scanKeyWord(std::string str, int line)
{
    Tokens.push_back(new KeywordToken(str, line));
}
void reportUnexpected(std::string str, int line)
{
    throw std::runtime_error("Unexpected '"+str+"' in input.");
}

#endif