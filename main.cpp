#include <iostream>
#include "GlobalState.hpp"
#include "ParseStmt.hpp"
#include "Sema.hpp"
extern "C" int yylex();

int main()
{
    yylex();
    spc::insertToken(new spc::EOFToken);
    auto p = spc::ZeroOrMore(spc::parseStmt)(0);
    
    if (!p)
        std::cerr << p.getError() <<std::endl;
    else
    {
//         std::cout << "Parsed" << std::endl;
//         if (p.get() != nullptr)
//             p.get()->dump();
        spc::ASTNodeVector* v = static_cast<spc::ASTNodeVector*>(p.get());
        std::vector<spc::ASTNode*> data = v->getData();
        spc::Sema s;
        for (auto node : data)
        {
//             static_cast<spc::Stmt*>(node)->dump();
            s.process(static_cast<spc::Stmt*>(node));
        }
    }
}
