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
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseEqualSymbol(int index)
    {
        if (!isCorrectSymbol(index, "="))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "=" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseOpenParen(int index)
    {
        if (!isCorrectSymbol(index, "("))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "(" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseCloseParen(int index)
    {
        if (!isCorrectSymbol(index, ")"))
                return ParseResult("Line: '" 
                    + std::to_string(Tokens[index]->line)
                    + "' ::Expected " + ")" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    
    ParseResult parseOpenBrace(int index)
    {
        if (!isCorrectSymbol(index, "{"))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "{" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseCloseBrace(int index)
    {
        if (!isCorrectSymbol(index, "}"))
                return ParseResult("Line: '" 
                    + std::to_string(Tokens[index]->line)
                    + "' ::Expected " + "}" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    
    ParseResult parseSemicolon(int index)
    {
        if (!isCorrectSymbol(index, ";"))
                return ParseResult("Line: '" 
                    + std::to_string(Tokens[index]->line)
                    + "' ::Expected " + ";" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    
    ParseResult parseAlpha(int index)
    {
        if (!isCorrectSymbol(index, "@"))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "@" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    
    ParseResult parseAuto(int index)
    {
        if (!isCorrectSymbol(index, "auto"))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "auto" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseIf(int index)
    {
        if (!isCorrectSymbol(index, "if"))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "if" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseElse(int index)
    {
        if (!isCorrectSymbol(index, "else"))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "else" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseWhile(int index)
    {
        if (!isCorrectSymbol(index, "while"))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "while" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    ParseResult parseType(int index)
    {
        if (!isCorrectSymbol(index, "type"))
            return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected " + "type" +" symbol.");
        else return ParseResult(new ASTNode(), index + 1);
    }
    
}
#endif