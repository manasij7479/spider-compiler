#ifndef PARSE_EXPR_HPP
#define PARSE_EXPR_HPP
#include "GlobalState.hpp"
#include "AST.hpp"
#include "ParseResult.hpp"
#include "ParseUtils.hpp"
#include <iostream>
namespace spc
{
    ParseResult ParsePrefixKeyword(int index)
    {
        if (Tokens[index]->type != TType::Keyword
            || getkw(Tokens[index])->data != "'")
                return ParseResult("Line: '" 
                    + std::to_string(Tokens[index]->line)
                    + "' ::Expected " + "'" +" symbol.");
        else return ParseResult(nullptr, index + 1);
    }
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
        auto f = Sequence({ParsePrefixKeyword, parseIdentifierExpr, ZeroOrMore(parseExpr)});
        auto result = f(index);
        if (!result)
            return result;
        auto node = new PrefixCallExpr;
        ASTNodeVector* v = static_cast<ASTNodeVector*>(result.get());
        node->fname = static_cast<IdExpr*>(v->data[1]);
        for (auto x : static_cast<ASTNodeVector*>(v->data[2])->data)
            node->args.push_back(static_cast<Expr*>(x));
        return ParseResult(node, result.nextIndex());
    }
//     ParseResult parsePrefixCallExpr(int index)
//     {
//         auto result = MatchKeyword("'")(index);
//         if (!result)
//             return result;
//         index = result.nextIndex();
//         result = parseIdentifierExpr(index);
//         if(!result)
//             return result;
//         auto node = new PrefixCallExpr;
//         node->fname =  static_cast<IdExpr*>(result.get());
//         index  = result.nextIndex();
//         result = ZeroOrMore(parseExpr)(index);
//         for (auto x : static_cast<ASTNodeVector*>(result.get())->data)
//             node->args.push_back(static_cast<Expr*>(x));
//         return ParseResult(node, result.nextIndex());
//     }
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
    ParseResult ParseEof(int index)
    {
        if (Tokens[index]->type == TType::Eof)
        {
            return ParseResult(nullptr, index); // Special case for EOF, index does not increase.
        }
        else return ParseResult("Line: '" + std::to_string(Tokens[index]->line)+"' ::Expected EOF");
    }
}
#endif