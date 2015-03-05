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
        void output(std::string s)
        {
            std::cout << s << std::endl;
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