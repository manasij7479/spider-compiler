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
    
    struct ExprList : public Expr
    {
        std::vector<Expr*> data;
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "Expression List\n";
            for (auto node : data)
                if(node)
                    node->dump(tab+1, out);
                else
                {
                    tabs(tab+1);
                    out << "NULL" << std::endl;
                }
        }
    };
    
    struct CallExpr : public Expr
    {
        IdExpr* fname;
        ExprList* args;
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "Prefix Call Expression\n";
            fname->dump(tab+1, out);
            args->dump(tab+1, out);
        }
    };
    
    struct Stmt : public ASTNode
    {
        
    };
    
    struct AssignStmt : public Stmt
    {
        IdExpr* lvalue;
        Expr* rvalue;
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "Lvalue\n";
            lvalue->dump(tab+1, out);
            tabs(tab);
            out << "Rvalue\n";
            rvalue->dump(tab+1, out);
        }
    };
}
#endif