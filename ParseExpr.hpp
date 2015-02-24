#ifndef PARSE_EXPR_HPP
#define PARSE_EXPR_HPP
#include "GlobalState.hpp"
#include "AST.hpp"
#include "ParseResult.hpp"
namespace spc
{
    ParseResult parseIntLiteralExpr(int index)
    {
        if (Tokens[index]->type == TType::IntLiteral)
        {
            auto iexp = new IntLiteralExpr;
            iexp->i = static_cast<IntLiteralToken*>(Tokens[index]);
            return ParseResult(iexp, index+1);
        }
        else return ParseResult("Expected Int Literal");
    }
}
#endif