#ifndef AST_HPP
#define AST_HPP
#include "TokenTypes.hpp"
#include <iostream>
#include <vector>
namespace spc
{
    class Sema;
    void tabs(int t, std::ostream& out = std::cout);
    
    class ASTNode
    {
    public:
        ASTNode();
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    protected:
        Sema* sema;
    };
    class ASTNodeVector : public ASTNode
    {
    public:
        ASTNodeVector(std::vector<ASTNode*> d):data(d){}
    private:
        std::vector<ASTNode*> data;
    public:
        auto getData(){return data;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
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
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    class IntLiteralExpr: public Expr
    {
    public:
        IntLiteralExpr(IntLiteralToken* it):i(it){}
    private:
        IntLiteralToken* i;
    public:
        auto getToken(){return i;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    class StringLiteralExpr: public Expr
    {
    public:
        StringLiteralExpr(StringLiteralToken* st):s(st){}
    private:
        StringLiteralToken* s;
    public:
        auto getToken(){return s;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class ExprList : public Expr
    {
    public:
        ExprList(std::vector<Expr*> el): data(el){}
    private:
        std::vector<Expr*> data;
    public:
        auto getData(){return data;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class CallExpr : public Expr
    {
    public:
        CallExpr(IdExpr* id, ExprList* el);
    private:
        IdExpr* fname;
        ExprList* args;
    public:
        auto getCaller(){return fname;}
        auto getArgs(){return args;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
      
    class Stmt : public ASTNode
    {
        
    };
    
    class AssignStmt : public Stmt
    {
    public:
        AssignStmt(IdExpr* lv, Expr* rv);
    private:
        IdExpr* lvalue;
        Expr* rvalue;
    public:
        auto getLvalue(){return lvalue;}
        auto getRvalue(){return rvalue;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class DeclStmt : public Stmt
    {
        //there will be semantic difference
    public:
        DeclStmt(AssignStmt* as);
    private:
        AssignStmt* stmt;
    public:
        auto getAssignStmt(){return stmt;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class IfStmt : public Stmt
    {
    public:
        IfStmt(Expr* c, Stmt* t, Stmt* f);
    private:
        Expr* condition;
        Stmt* trueblock;
        Stmt* falseblock;
    public:
        auto getCondition(){return condition;}
        auto getTrueBlock(){return trueblock;}
        auto getFalseBlock(){return falseblock;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class WhileStmt : public Stmt
    {
    public:
        WhileStmt(Expr* c, Stmt* b);
    private:
        Expr* condition;
        Stmt* block;
    public:
        auto getCondition(){return condition;}
        auto getBlock(){return block;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class StmtBlock : public Stmt
    {
    public:
        StmtBlock(std::vector<Stmt*> d):data(d){}
    private:
        std::vector<Stmt*> data;
    public:
        auto getData(){return data;}
        virtual void dump(int tab=0, std::ostream& out = std::cout);
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
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class TypeDefinitionStmt: public Stmt
    {
    public:
        TypeDefinitionStmt(IdExpr* i, TypeDefinition* td);
    private:
        IdExpr* id;
        TypeDefinition* def;
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
    class ReturnStmt : public Stmt
    {
    public:
        ReturnStmt(Expr* e): expr(e){}
    private:
        Expr* expr;
    public:
        virtual void dump(int tab=0, std::ostream& out = std::cout);
    };
    
}
#endif