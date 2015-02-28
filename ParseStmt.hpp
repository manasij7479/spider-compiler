#ifndef PARSE_STMT_HPP
#define PARSE_STMT_HPP
#include "ParseExpr.hpp"
namespace spc
{
    ParseResult parseStmt();
    ParseResult parseAssignStmt(int index)
    {
        IdExpr* lv;
        Expr* rv;
        auto f = Sequence
        (
            {
                hook(parseIdentifierExpr,lv),
                parseEqualSymbol, 
                hook(parseExpr, rv),
                parseSemicolon
            }
        );
        
        auto result = f(index);
        if (!result)
            return result;
        
        return ParseResult(new AssignStmt(lv, rv), result.nextIndex());
    }
    ParseResult parseDeclStmt(int index)
    {
        AssignStmt* as;
        auto f = Sequence({parseAuto, hook(parseAssignStmt, as)});
        auto result = f(index);
        if (!result)
            return result;
        return ParseResult(new DeclStmt(as), result.nextIndex());
    }
}
#endif