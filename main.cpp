#include <iostream>
#include "GlobalState.hpp"
#include "ParseStmt.hpp"
#include "Sema.hpp"
#include <cstdio>
extern "C" int yylex();
extern "C" FILE*   yyin;
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Expected Filename or - (for stdin).";
        return 1;
    }
    if (std::string(argv[1]) == "-")
        yylex();
    else
    {
        yyin = std::fopen(argv[1], "r");
        if (!yyin)
        {
            std::cerr << "Can not open file: " << argv[1];
            return 1;
        }
        yylex();
    }
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
    return 0;
}
