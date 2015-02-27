#include <iostream>
#include "GlobalState.hpp"
#include "ParseStmt.hpp"
extern "C" int yylex();
namespace spc
{
    std::vector<Token*> Tokens;
}
int main()
{
    yylex();
    spc::Tokens.push_back(new spc::EOFToken);
    auto p = spc::parseAssignStmt(0);
    if (!p)
        std::cerr << p.getError() <<std::endl;
    else
    {
        std::cout << "Parsed" << std::endl;
        if (p.get() != nullptr)
            p.get()->dump();
    }
}