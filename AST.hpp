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
    class ASTNode
    {
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab, out);
            out<<"<EMPTY NODE>\n";
        }
    };
    class ASTNodeVector : public ASTNode
    {
    public:
        ASTNodeVector(std::vector<ASTNode*> d):data(d){}
    private:
        std::vector<ASTNode*> data;
    public:
        auto getData(){return data;}
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
    class Expr : public ASTNode
    {
        // ?
    };
    
    
    class IdExpr : public Expr
    {
    public:
        IdExpr(IdentifierToken* id_):id(id_){}
    private:
        IdentifierToken* id;
    public:
        auto getToken(){return id;}
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "Identifier: " << id->data << "\n";
        }
    };
    class IntLiteralExpr: public Expr
    {
    public:
        IntLiteralExpr(IntLiteralToken* it):i(it){}
    private:
        IntLiteralToken* i;
    public:
        auto getToken(){return i;}
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "Int Literal: " << i->data << "\n";
        }
    };
    class StringLiteralExpr: public Expr
    {
    public:
        StringLiteralExpr(StringLiteralToken* st):s(st){}
    private:
        StringLiteralToken* s;
    public:
        auto getToken(){return s;}
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "String Literal: " << s->data << "\n";
        }
    };
    
    class ExprList : public Expr
    {
    public:
        ExprList(std::vector<Expr*> el): data(el){}
    private:
        std::vector<Expr*> data;
    public:
        auto getData(){return data;}
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
    
    class CallExpr : public Expr
    {
    public:
        CallExpr(IdExpr* id, ExprList* el):fname(id), args(el){}
    private:
        IdExpr* fname;
        ExprList* args;
    public:
        auto getCaller(){return fname;}
        auto getArgs(){return args;}
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "Prefix Call Expression\n";
            fname->dump(tab+1, out);
            args->dump(tab+1, out);
        }
    };
    
    class Stmt : public ASTNode
    {
        
    };
    
    class AssignStmt : public Stmt
    {
    public:
        AssignStmt(IdExpr* lv, Expr* rv):lvalue(lv), rvalue(rv){}
    private:
        IdExpr* lvalue;
        Expr* rvalue;
    public:
        auto getLvalue(){return lvalue;}
        auto getRvalue(){return rvalue;}
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
    
    class DeclStmt : public Stmt
    {
        //there will be semantic difference
    public:
        DeclStmt(AssignStmt* as):stmt(as){}
    private:
        AssignStmt* stmt;
    public:
        auto getAssignStmt(){return stmt;}
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab);
            out << "NEW Lvalue\n";
            stmt->getLvalue()->dump(tab+1, out);
            tabs(tab);
            out << "Rvalue\n";
            stmt->getRvalue()->dump(tab+1, out);
        }
    };
    
}
#endif