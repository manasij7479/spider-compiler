#ifndef PARSE_EXPR_HPP
#define PARSE_EXPR_HPP
#include "ParseSymbol.hpp"
#include <iostream>
namespace spc
{
    ParseResult parseExpr(int index);
    ParseResult parseIntLiteralExpr(int index)
    {
        if (getToken(index)->type == TType::IntLiteral)
        {
            return ParseResult(new IntLiteralExpr(getil(getToken(index))), index+1);
        }
        else return ParseResult("Line: '" + std::to_string(getToken(index)->line)+"' ::Expected Int Literal");
    }
    ParseResult parseStringLiteralExpr(int index)
    {
        if (getToken(index)->type == TType::StringLiteral)
        {
            return ParseResult(new StringLiteralExpr(getsl(getToken(index))), index+1);
        }
        else return ParseResult("Line: '" 
            + std::to_string(getToken(index)->line)
            + "' ::Expected String Literal");
    }
    ParseResult parseIdentifierExpr(int index)
    {
        if (getToken(index)->type == TType::Identifier)
        {
            return ParseResult(new IdExpr(getifr(getToken(index))), index+1);
        }
        else return ParseResult("Line: '" 
                + std::to_string(getToken(index)->line)
                + "' ::Expected Identifier");
    }
    
    /*
     * exprlist <- expr*
     */
    ParseResult parseExprList(int index)
    {
        auto f = ZeroOrMore(parseExpr);
        auto result = f(index);
        if (!result)
            return result;
        std::vector<Expr*> data;
        for (auto x : static_cast<ASTNodeVector*>(result.get())->getData())
            data.push_back(static_cast<Expr*>(x));
        return ParseResult(new ExprList(data), result.nextIndex());
    }
    
//     /*
//      *  prefixcallexpr <- ' identifier expr* 
//      */
//     ParseResult parsePrefixCallExpr(int index)
//     {
//         auto f = Sequence({parsePrefixKeyword, parseIdentifierExpr, ZeroOrMore(parseExpr)});
//         auto result = f(index);
//         if (!result)
//             return result;
//         auto node = new CallExpr;
//         ASTNodeVector* v = static_cast<ASTNodeVector*>(result.get());
//         node->fname = static_cast<IdExpr*>(v->data[1]);
//         for (auto x : static_cast<ASTNodeVector*>(v->data[2])->data)
//             node->args.push_back(static_cast<Expr*>(x));
//         return ParseResult(node, result.nextIndex());
//     }
    
    /*
     *  prefixcallexpr <- 'identifier (exprlist)
     */
    ParseResult parsePrefixCallExpr(int index)
    {
        IdExpr* id;
        ExprList* list;
        auto f = Sequence
        (
            {
//                 parsePrefixSymbol, 
                hook(parseIdentifierExpr, id),
                Sequence({parseOpenParen, hook(parseExprList, list), parseCloseParen})
            }
        );
        auto result = f(index);
        if(!result)
            return result;

        return ParseResult(new CallExpr(id, list), result.nextIndex());
    }
    
    /*
     * infixcallexpr <- ' expr . identifier expr* '?
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
                parsePrefixCallExpr, // Would benefit from memoization
                parseIdentifierExpr,
                
            },
            "Expected Expression."
        )
        (index);
    }
    ParseResult ParseEof(int index)
    {
        if (getToken(index)->type == TType::Eof)
        {
            return ParseResult(nullptr, index); // Special case for EOF, index does not increase.
        }
        else return ParseResult("Line: '" + std::to_string(getToken(index)->line)+"' ::Expected EOF");
    }
}
#endif