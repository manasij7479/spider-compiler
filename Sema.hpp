#ifndef SEMA_HPP
#define SEMA_HPP
#include "AST.hpp"
#include <sstream>
namespace spc
{
    class Sema
    {
    public:
        Sema()
        {
            counter = 0;
        }
        //only process the statements from parser
        //invoke the expre process' from them
        void process(Stmt* s)
        {
            switch(s->type)
            {
                case SType::Decl: process(static_cast<DeclStmt*>(s)); break;
                case SType::Assign: process(static_cast<AssignStmt*>(s)); break;
            }
        }
        void process(DeclStmt* ds)
        {
            //TODO insert id into symbol table
            IdExpr* id = ds->getAssignStmt()->getLvalue();
            std::string s = process(ds->getAssignStmt()->getRvalue());
            output("let "+ id->getToken()->data + " " + s);
        }
        void process(AssignStmt* as)
        {
            //type check
            IdExpr* id = as->getLvalue();
            std::string s = process(as->getRvalue());
            output("assign "+ id->getToken()->data + " " + s); 
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
        
        std::string process(Expr* e)
        {
            switch (e->type)
            {
                case EType::Id : return static_cast<IdExpr*>(e)->getToken()->data; break;
                case EType::Int : return "i"+std::to_string(static_cast<IntLiteralExpr*>(e)->getToken()->data); break;
                case EType::String : return static_cast<StringLiteralExpr*>(e)->getToken()->data; break;
                case EType::Call: return process(static_cast<CallExpr*>(e)); break;
            }
        }
        std::string process(CallExpr* ce)
        {
            std::ostringstream os;
            std::string s = getTempName();
            os << "let " << s << ' ';
            os << ce->getCallee()->getToken()->data << ' ';
            for(auto arg : ce->getArgs()->getData())
                os << process(arg) << ' ';
            output(os.str());
            return s;
        }
        void output(std::string s, bool endl = true)
        {
            std::cout << s;
            if (endl)
                std::cout << std::endl;
        }
        std::string getTempName()
        {
            return "t" + std::to_string(counter++);
        }
    private:
        //bool type_check(); //decide on the interface!
        //TODO: Symbol Table, Function Sigs, etc.
        
        int counter;
        
    };
}
#endif