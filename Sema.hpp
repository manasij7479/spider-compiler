#ifndef SEMA_HPP
#define SEMA_HPP
#include "AST.hpp"
namespace spc
{
    class Sema
    {
    public:
        //only process the statements from parser
        //invoke the expre process' from them
        void process(CallExpr* ce)
        {
            //check if ce->fname is a function
            //check if the arguments are of the correct type
        }
        void process(Expr* e)
        {
            //gen 3-code
            //store the result type somewhere
        }
        void process(DeclStmt* ds)
        {
            //process expr
            //insert id into symbol table
        }
        void process(AssignStmt* as)
        {
            //precess expr
            //type check
        }
        void process(IfStmt* ifs)
        {
            //codegen
            //anything else?
        }
        void process(WhileStmt* ws)
        {
            //codegen
            //anything else?
        }
        
        void process(TypeDefinitionStmt* tds)
        {
            //insert type
            
        }
        //void process(FunctionDefinitionStmt* fd);
        
        
        
    private:
        //bool type_check(); //decide on the interface!
        //TODO: Symbol Table, Function Sigs, etc.
        
    };
}
#endif