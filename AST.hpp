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
            tabs(tab, out);
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
            tabs(tab, out);
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
            tabs(tab, out);
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
            tabs(tab, out);
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
            tabs(tab, out);
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
            tabs(tab, out);
            out << "AssignStmt\n";
            tabs(tab, out);
            out << "Lvalue\n";
            lvalue->dump(tab+1, out);
            tabs(tab, out);
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
            tabs(tab, out);
            out << "DeclStmt\n";
            stmt->dump(tab+1, out);
        }
    };
    
    class IfStmt : public Stmt
    {
    public:
        IfStmt(Expr* c, Stmt* t, Stmt* f): condition(c), trueblock(t), falseblock(f){}
    private:
        Expr* condition;
        Stmt* trueblock;
        Stmt* falseblock;
    public:
        auto getCondition(){return condition;}
        auto getTrueBlock(){return trueblock;}
        auto getFalseBlock(){return falseblock;}
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab, out);
            out << "IfStmt\n";
            condition->dump(tab+1, out);
            trueblock->dump(tab+1, out);
            if (falseblock)
                falseblock->dump(tab+1, out);
        }
    };
    
    class WhileStmt : public Stmt
    {
    public:
        WhileStmt(Expr* c, Stmt* b): condition(c), block(b){}
    private:
        Expr* condition;
        Stmt* block;
    public:
        auto getCondition(){return condition;}
        auto getBlock(){return block;}
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab, out);
            out << "WhileStmt\n";
            condition->dump(tab+1, out);
            block->dump(tab+1, out);
        }
    };
    
    class StmtBlock : public Stmt
    {
    public:
        StmtBlock(std::vector<Stmt*> d):data(d){}
    private:
        std::vector<Stmt*> data;
    public:
        auto getData(){return data;}
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab, out);
            out << "StmtBlock\n";
            for (auto s : data)
                s->dump(tab+1, out);
        }
    };
    
    class TypeDefinition : public ASTNode
    {
    public:
        TypeDefinition(std::vector<TypeDefinition*> d, IdExpr* i, bool alpha): data(d), id(i), is_array(alpha){}
    private:
        IdExpr* id; // exists if builtin or named
        std::vector<TypeDefinition*> data;
        bool is_array;
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout)
        {
            tabs(tab, out);
            out << "TypeDefinition\n";
            tabs(tab, out);
            if (id)
                id->dump(tab+1, out);
            else
            {
                tabs(tab);
                out << "Array: " << is_array<<"\n";
                for(auto td: data)
                {
                    td->dump(tab+1, out);
                }
            }
        }
    };
    
    class TypeDefinitionStmt: public Stmt
    {
    public:
    private:
        IdExpr* id;
        TypeDefinition* def;
    };
}
#endif