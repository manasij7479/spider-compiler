#ifndef SEMA_HPP
#define SEMA_HPP
#include "AST.hpp"
#include <map>
#include <sstream>
namespace spc
{
    class Sema
    {
    public:
        Sema()
        {
            counter = 0;
            output_stack.push_back(&std::cout);
        }
        //only process the statements from parser
        //invoke the expre process' from them
        void process(Stmt* s)
        {
            switch(s->type)
            {
                case SType::Decl: process(static_cast<DeclStmt*>(s)); break;
                case SType::Assign: process(static_cast<AssignStmt*>(s)); break;
                case SType::If: process(static_cast<IfStmt*>(s)); break;
                case SType::While: process(static_cast<WhileStmt*>(s)); break;
                case SType::Block: process(static_cast<StmtBlock*>(s)); break;
                case SType::FDef: process(static_cast<FunctionDefinition*>(s)); break;
                case SType::FDecl: process(static_cast<FunctionDeclaration*>(s)); break;
                case SType::VCall: process(static_cast<VoidCallStmt*>(s)); break;
            }
        }
        void process(DeclStmt* ds)
        {
            //TODO insert id into symbol table
            IdExpr* id = ds->getAssignStmt()->getLvalue();
            auto p = process(ds->getAssignStmt()->getRvalue());
            m_TypeMap[id->getToken()->data] = p.second;
            output("let "+ id->getToken()->data + " " + p.first);
        }
        void process(AssignStmt* as)
        {
            //type check
            IdExpr* id = as->getLvalue();
            auto p = process(as->getRvalue());
            //check if getType of id is same as p.second
            output("assign "+ id->getToken()->data + " " + p.first); 
        }
        void process(StmtBlock* b)
        {
            output("{");
            for (auto s : b->getData())
                process(s);
            output("}");
        }
        void process(IfStmt* ifs)
        {
            //anything else?
            Expr* e = ifs->getCondition();
            auto p = process(e);
            //check if p.second is bool
            output("if " + p.first);
            Stmt* tb = ifs->getTrueBlock();
            process(tb);
            Stmt* fb = ifs->getFalseBlock();
            if(fb)
            {
                output("not " + p.first);
                output("if _");
                process(fb);
            }
            
        }
        void process(WhileStmt* ws)
        {
            Expr* e = ws->getCondition();
            std::string s = convert_into_function(e);
            output("while " + s);
            process(ws->getBlock());
        }
        
        void process(TypeDefinitionStmt* tds)
        {
            //insert type
            
        }
        void process(FunctionPrototype* fp, bool codegen = false)
        {
            std::ostringstream out;
            out << "function ";
            std::string fname = fp->getName()->getToken()->data;
            std::string rettype = fp->getReturnArg()->getTypeName()->getToken()->data;
            std::vector<std::string> mapdata({rettype});
            out << fname << " ";
            out << fp->getReturnArg()->getName()->getToken()->data << " ";
            out << rettype << " ";
            for (FunctionArg* arg : fp->getArgs())
            {
                std::string argtype = arg->getTypeName()->getToken()->data;
                out << arg->getName()->getToken()->data << " ";
                out << argtype << " ";
                mapdata.push_back(argtype);
            }
            if (codegen)
                output(out.str());
            m_FunctionMap[fname] = mapdata;
        }
        void process(VoidCallStmt* vstmt)
        {
            auto p = process(vstmt->getCallExpr());
            //ignore the result for now
            //needs checking, maybe warnings too if type is not void
        }
        void process(FunctionDeclaration* fd)
        {
            process(fd->getPrototype());
        }
        void process(FunctionDefinition* fd)
        {
            process(fd->getPrototype(), true /*codegen*/);
            process(fd->getBlock());
        }
        std::string convert_into_function(Expr* e) // returns function name
        {
            std::ostringstream temp;
            
            output_stack.push_back(&temp);
            auto p = process(e);
            output_stack.pop_back();
            
            std::string fname = getTempName();
            std::string result = getTempName();
            m_TypeMap[result] = p.second;
            output("function " + fname + " " + result + " " + p.second);
            output("{");
            output(temp.str(), false);
            output("let " + result + " " +  p.first);
            output("}");
            return fname;
        }
        std::pair<std::string, std::string> process(Expr* e)
        {
            switch (e->type)
            {
                case EType::Id : 
                {
                    auto s = static_cast<IdExpr*>(e)->getToken()->data;
                    return {s, getType(s)};
                }
                case EType::Int : return {"i"+std::to_string(static_cast<IntLiteralExpr*>(e)->getToken()->data), "int"};
                case EType::String : return {static_cast<StringLiteralExpr*>(e)->getToken()->data,"string"};
                case EType::Call: return process(static_cast<CallExpr*>(e));
            }
        }
        std::pair<std::string, std::string> process(CallExpr* ce)
        {
            std::ostringstream os;
            std::string s = getTempName();
            os << "let " << s << ' ';
            os << ce->getCallee()->getToken()->data << ' ';
            for(auto arg : ce->getArgs()->getData())
                os << process(arg).first << ' ';
            output(os.str());
            return {s, getReturnType(ce->getCallee()->getToken()->data)};
        }
        void output(std::string s, bool endl = true)
        {
            std::ostream& out = *output_stack.back();
            out << s;
            if (endl)
                out << std::endl;
        }
        std::string getTempName()
        {
            return "t" + std::to_string(counter++);
        }
    private:
        //bool type_check(); //decide on the interface!
        //TODO: Symbol Table, Function Sigs, etc.
        
        int counter;
        std::vector<std::ostream*> output_stack;
        std::map<std::string, std::string> m_TypeMap; 
        // may need a more complicated hierarchical structure
        std::map<std::string, std::vector<std::string>> m_FunctionMap;
        std::string getType(std::string var)
        {
            if (m_TypeMap.find(var) != m_TypeMap.end())
                return m_TypeMap[var];
            else throw std::runtime_error("var : '" + var + "' Not found in table.");
        }
        std::string getReturnType(std::string f)
        {
            if (m_FunctionMap.find(f) != m_FunctionMap.end())
                return m_FunctionMap[f][0];
            else throw std::runtime_error("function : '" + f + "' Not found in table.");
        }
    };
}
#endif