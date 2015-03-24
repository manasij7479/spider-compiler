#ifndef SEMA_HPP
#define SEMA_HPP
#include "AST.hpp"
#include "SymbolTable.hpp"
#include <map>
#include <sstream>
namespace spc
{
    class Sema
    {
    public:
        Sema(std::ostream* out)
        {
            output_stack.push_back(out);
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
                case SType::Import: process(static_cast<ImportStmt*>(s)); break;
            }
        }
        void process(DeclStmt* ds)
        {
            //TODO insert id into symbol table
            IdExpr* id = ds->getAssignStmt()->getLvalue();
            auto p = process(ds->getAssignStmt()->getRvalue());
//             m_TypeMap[id->getToken()->data] = p.second;
            table.insert(id->getToken()->data, p.second);
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
            std::string rettype;
            if (fp->getReturnArg() != nullptr)
                rettype = fp->getReturnArg()->getTypeName()->getToken()->data;
            else rettype = "void";
            std::vector<std::string> mapdata({rettype});
            out << fname << " ";
            if (fp->getReturnArg() != nullptr)
                out << fp->getReturnArg()->getName()->getToken()->data << " ";
            else out << "_placeholder ";
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
            table.insert(fname, Type(mapdata));
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
        void process(ImportStmt* imp)
        {
            std::string filename = imp->getStr()->getToken()->data;
            output("Placeholder for import '"+filename+"'");
        }
        std::string convert_into_function(Expr* e) // returns function name
        {
            std::ostringstream temp;
            
            output_stack.push_back(&temp);
            auto p = process(e);
            output_stack.pop_back();
            std::string fname = table.getNewName(Type(std::vector<std::string>{p.second.getType()}));
            std::string result = table.getNewName(Type(p.second.getType()));
            
            output("function " + fname + " " + result + " " + p.second.getType());
            output("{");
            output(temp.str(), false);
            output("let " + result + " " +  p.first);
            output("}");
            return fname;
        }
        std::pair<std::string, Type> process(Expr* e)
        {
            switch (e->type)
            {
                case EType::Id : 
                {
                    auto s = static_cast<IdExpr*>(e)->getToken()->data;
                    return {s, table.lookup(s).second};
                }
                case EType::Int : return {"i"+std::to_string(static_cast<IntLiteralExpr*>(e)->getToken()->data), Type("int")};
                case EType::String : return {static_cast<StringLiteralExpr*>(e)->getToken()->data,Type("string")};
                case EType::Call: return process(static_cast<CallExpr*>(e));
            }
        }
        std::pair<std::string, Type> process(CallExpr* ce)
        {
            std::ostringstream os;
            std::string fname = ce->getCallee()->getToken()->data;
            std::string s = table.getNewName(getReturnType(fname));
            auto&& args = getArgTypeList(fname);
            if (getReturnType(fname) != "void")
                os << "let " << s << ' ';
            
            os << fname << ' ';
//             for(auto arg : ce->getArgs()->getData())
            if (args.size() != ce->getArgs()->getData().size())
                throw std::runtime_error("Argument size mismatch, expected '"+std::to_string(args.size())+"' got '"+std::to_string(ce->getArgs()->getData().size()));
            for(int i = 0 ; i < ce->getArgs()->getData().size(); ++i)
            {
                auto p = process(ce->getArgs()->getData()[i]);
                if (Type(args[i]).isCompatible(p.second.getType()) == false)
                    throw std::runtime_error("Type Mismatch, expected '"+args[i]+"' got '"+p.second.getType());
                os << p.first << ' ';
            }
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
    private:
        //bool type_check(); //decide on the interface!
        //TODO: Symbol Table, Function Sigs, etc.
        
        std::vector<std::ostream*> output_stack;
        SymbolTable table;
        std::string getReturnType(std::string f)
        {
            auto p = table.lookup(f);
            if (!p.first)
                throw std::runtime_error("Function: '"+f+"' does not exist.");
            if (!p.second.isFunction())
                throw std::runtime_error("'"+f+"' is not a function.");
            return p.second.getArgTypes()[0];
        }
        std::vector<std::string> getArgTypeList(std::string f)
        {
            auto p = table.lookup(f);
            if (!p.first)
                throw std::runtime_error("Function: '"+f+"' does not exist.");
            if (!p.second.isFunction())
                throw std::runtime_error("'"+f+"' is not a function.");
            auto&& result = p.second.getArgTypes();
            result.erase(result.begin());
            return result;
        }
    };
}
#endif