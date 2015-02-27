#ifndef PARSE_SYMBOL_HPP
#define PARSE_SYMBOL_HPP
#include "GlobalState.hpp"
#include "AST.hpp"
#include "ParseResult.hpp"
#include "ParseUtils.hpp"
namespace spc
{
    bool isCorrectSymbol(int index, std::string s)
    {
        return Tokens[index]->type == TType::Symbol
            && getsy(Tokens[index])->data == s;
    }
    
    ParseResult parsePrefixSymbol(int index)
    {
        if (!isCorrectSymbol(index, "'"))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "'" +" symbol.");
        else return ParseResult(nullptr, index + 1);
    }
    ParseResult parseEqualSymbol(int index)
    {
        if (!isCorrectSymbol(index, "="))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "=" +" symbol.");
        else return ParseResult(nullptr, index + 1);
    }
    ParseResult parseOpenParen(int index)
    {
        if (!isCorrectSymbol(index, "("))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "(" +" symbol.");
        else return ParseResult(nullptr, index + 1);
    }
    ParseResult parseCloseParen(int index)
    {
        if (!isCorrectSymbol(index, ")"))
                return ParseResult("Line: '" 
                    + std::to_string(Tokens[index]->line)
                    + "' ::Expected " + ")" +" symbol.");
        else return ParseResult(nullptr, index + 1);
    }
    
    ParseResult parseSemicolon(int index)
    {
        if (!isCorrectSymbol(index, ";"))
                return ParseResult("Line: '" 
                    + std::to_string(Tokens[index]->line)
                    + "' ::Expected " + ";" +" symbol.");
        else return ParseResult(nullptr, index + 1);
    }
    ParseResult parseAuto(int index)
    {
        if (!isCorrectSymbol(index, "auto"))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "auto" +" symbol.");
        else return ParseResult(nullptr, index + 1);
    }
}
#endif