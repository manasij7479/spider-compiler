#ifndef PARSE_EXPR_HPP
#define PARSE_EXPR_HPP
#include "GlobalState.hpp"
#include "AST.hpp"
#include "ParseResult.hpp"
#include "ParseUtils.hpp"
#include <iostream>
namespace spc
{
    ParseResult parseExpr(int index);
    ParseResult parseIntLiteralExpr(int index)
    {
        if (Tokens[index]->type == TType::IntLiteral)
        {
            auto iexp = new IntLiteralExpr;
            iexp->i = getil(Tokens[index]);
            return ParseResult(iexp, index+1);
        }
        else return ParseResult("Line: '" + std::to_string(Tokens[index]->line)+"' ::Expected Int Literal");
    }
    ParseResult parseStringLiteralExpr(int index)
    {
        if (Tokens[index]->type == TType::StringLiteral)
        {
            auto sexp = new StringLiteralExpr;
            sexp->s = getsl(Tokens[index]);
            return ParseResult(sexp, index+1);
        }
        else return ParseResult("Line: '" 
            + std::to_string(Tokens[index]->line)
            + "' ::Expected String Literal");
    }
    ParseResult parseIdentifierExpr(int index)
    {
        if (Tokens[index]->type == TType::Identifier)
        {
            auto idexp = new IdExpr;
            idexp->id = getifr(Tokens[index]);
            return ParseResult(idexp, index+1);
        }
        else return ParseResult("Line: '" 
                + std::to_string(Tokens[index]->line)
                + "' ::Expected Identifier");
    }
    
    /*
     *  prefixcallexpr <-- ' identifier expr* 
     */
    ParseResult parsePrefixCallExpr(int index)
    {
        if (Tokens[index]->type != TType::Keyword
            || getkw(Tokens[index])->data != "'")
                return ParseResult("Line: '" 
                    + std::to_string(Tokens[index]->line)
                    + "' ::Expected ' symbol for prefix call expressions.");
        index++;
        auto result = parseIdentifierExpr(index);
        if(!result)
            return result;
        auto node = new PrefixCallExpr;
        node->fname =  static_cast<IdExpr*>(result.get());
        index  = result.nextIndex();
        while (true)
        {
            result = parseExpr(index);
//             std::cerr << "P"<<node->args.size()<<"\n";
            if (result == false)
                break;
            else
            {
                index = result.nextIndex();
                node->args.push_back(static_cast<Expr*>(result.get()));
            }
        }
        return ParseResult(node, result.nextIndex());
    }
    /*
     * infixcallexpr <- . expr identifier expr*
     */
    ParseResult parseInfixCallExpr(int index)
    {
        return ParseResult("NOT_IMPLEMENTED");
    }
    
    /*
     * expr <- intliteral / stringliteral / identifier / prefixcallexpr
     */
    ParseResult parseExpr(int index)
    {
        return LinearChoice
        (
            {
                parseIntLiteralExpr,
                parseStringLiteralExpr,
                parseIdentifierExpr,
                parsePrefixCallExpr
            },
            "Expected Expression."
        )
        (index);
    }

}
#endif