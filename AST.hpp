#ifndef AST_HPP
#define AST_HPP
#include "TokenTypes.hpp"
namespace spc
{
    struct ASTNode
    {
    };
    struct Expr : public ASTNode
    {
        // ?
    };
    struct IdExpr : public Expr
    {
        IdentifierToken* id;
    };
    struct IntLiteralExpr: public Expr
    {
        IntLiteralToken* i;
    };
    struct StringLiteralExpr: public Expr
    {
        StringLiteralToken* s;
    };
    
    struct PrefixCallExpr : public Expr
    {
        IdentifierToken* fname;
        std::vector<Expr*> args;
    };
    struct InfixCallExpr: public Expr
    {
        Expr* callee;
        IdentifierToken* fname;
        std::vector<Expr*> args;
    };
}
#endif