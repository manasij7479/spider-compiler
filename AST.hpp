#ifndef AST_HPP
#define AST_HPP
#include "TokenTypes.hpp"
#include <iostream>
namespace spc
{
    void tabs(int t, std::ostream& out = std::cout)
    {
        while(t--)
            out << '\t';
    }
    struct ASTNode
    {
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab, out);
            out<<"<EMPTY NODE>\n";
        }
    };
    struct ASTNodeVector : public ASTNode
    {
        std::vector<ASTNode*> data;
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab, out);
            out << "Node Vector\n";
            for (auto node : data)
                if(node != nullptr)
                    node->dump(tab+1, out);
                else
                {
                    tabs(tab+1, out);
                    out << "NULL\n";
                }
        }
    };
    struct Expr : public ASTNode
    {
        // ?
    };
    struct IdExpr : public Expr
    {
        IdentifierToken* id;
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "Identifier: " << id->data << "\n";
        }
    };
    struct IntLiteralExpr: public Expr
    {
        IntLiteralToken* i;
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "Int Literal: " << i->data << "\n";
        }
    };
    struct StringLiteralExpr: public Expr
    {
        StringLiteralToken* s;
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "String Literal: " << s->data << "\n";
        }
    };
    
    struct PrefixCallExpr : public Expr
    {
        IdExpr* fname;
        std::vector<Expr*> args;
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "Prefix Call Expression\n";
            fname->dump(tab+1, out);
            for (auto node : args)
                node->dump(tab+1, out);
        }
    };
    struct InfixCallExpr: public Expr
    {
        //Put a keyword/symbol to avoid left rec, don't smudge the grammar
        Expr* callee;
        IdExpr* fname;
        std::vector<Expr*> args;
    };
}
#endif