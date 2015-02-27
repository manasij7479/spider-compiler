#ifndef PARSE_STMT_HPP
#define PARSE_STMT_HPP
#include "ParseExpr.hpp"
namespace spc
{
    ParseResult parseStmt();
    ParseResult parseAssignStmt(int index)
    {
        auto f = Sequence({parseIdentifierExpr, parseEqualSymbol, parseExpr, parseSemicolon});
        auto result = f(index);
        if (!result)
            return result;
        ASTNodeVector* v = static_cast<ASTNodeVector*>(result.get());
        auto stmt = new AssignStmt;
        stmt->lvalue = static_cast<IdExpr*>(v->data[0]);
        stmt->rvalue = static_cast<Expr*>(v->data[2]);
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