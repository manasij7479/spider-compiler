#ifndef PARSE_STMT_HPP
#define PARSE_STMT_HPP
#include "ParseExpr.hpp"
namespace spc
{
    ParseResult parseStmt();
    ParseResult parseAssignStmt(int index)
    {
        auto stmt = new AssignStmt;
        auto f = Sequence
        (
            {
                hook(parseIdentifierExpr, stmt->lvalue),
                parseEqualSymbol, 
                hook(parseExpr, stmt->rvalue),
                parseSemicolon
            }
        );
        
        auto result = f(index);
        if (!result)
            return result;
        
        return ParseResult(stmt, result.nextIndex());
    }
    ParseResult parseDeclStmt(int index)
    {
        auto d  = new DeclStmt;
        auto f = Sequence({parseAuto, hook(parseAssignStmt, d->stmt)});
        auto result = f(index);
        if (!result)
            return result;
//         d->stmt = static_cast<AssignStmt*>(static_cast<ASTNodeVector*>(result.get())->data[1]);
        return ParseResult(d, result.nextIndex());
    }
}
#endif