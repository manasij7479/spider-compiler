#ifndef PARSE_EXPR_HPP
#define PARSE_EXPR_HPP
#include "GlobalState.hpp"
#include "AST.hpp"
#include "ParseResult.hpp"
#include "ParseUtils.hpp"
#include <iostream>
namespace spc
{
    ParseResult parsePrefixSymbol(int index)
    {
        if (Tokens[index]->type != TType::Symbol
            || getsy(Tokens[index])->data != "'")
                return ParseResult("Line: '" 
                    + std::to_string(Tokens[index]->line)
                    + "' ::Expected " + "'" +" symbol.");
        else return ParseResult(nullptr, index + 1);
    }
    
    ParseResult parseOpenParen(int index)
    {
        if (Tokens[index]->type != TType::Symbol
            || getsy(Tokens[index])->data != "(")
                return ParseResult("Line: '" 
                    + std::to_string(Tokens[index]->line)
                    + "' ::Expected " + "(" +" symbol.");
        else return ParseResult(nullptr, index + 1);
    }
    ParseResult parseCloseParen(int index)
    {
        if (Tokens[index]->type != TType::Symbol
            || getsy(Tokens[index])->data != ")")
                return ParseResult("Line: '" 
                    + std::to_string(Tokens[index]->line)
                    + "' ::Expected " + ")" +" symbol.");
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
     * exprlist <- ( expr* )
     */
    ParseResult parseExprList(int index)
    {
        auto f = Sequence({parseOpenParen, ZeroOrMore(parseExpr), parseCloseParen});
        auto result = f(index);
        if (!result)
            return result;
        auto list = new ExprList;
        ASTNodeVector* v = static_cast<ASTNodeVector*>(result.get());
        for (auto x : static_cast<ASTNodeVector*>(v->data[1])->data)
            list->data.push_back(static_cast<Expr*>(x));
        return ParseResult(list, result.nextIndex());
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
     *  prefixcallexpr <- 'identifier exprlist
     */
    ParseResult parsePrefixCallExpr(int index)
    {
        auto f = Sequence({parsePrefixSymbol, parseIdentifierExpr, parseExprList});
        auto result = f(index);
        if(!result)
            return result;
        auto call = new CallExpr;
        auto resultvec = static_cast<ASTNodeVector*>(result.get());
        call->fname = static_cast<IdExpr*>(resultvec->data[1]);
        call->args = static_cast<ExprList*>(resultvec->data[2]);
        return ParseResult(call, result.nextIndex());
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