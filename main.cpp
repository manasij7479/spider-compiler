#include <iostream>
#include "GlobalState.hpp"
#include "ParseExpr.hpp"
extern "C" int yylex();
namespace spc
{
    std::vector<Token*> Tokens;
}
int main()
{
    yylex();
    auto p = spc::parseStringLiteralExpr(0);
    if (!p)
        std::cerr << p.getError() <<std::endl;
    else
        std::cout << "Parsed:" << 
            static_cast<spc::StringLiteralExpr*>(p.get())->s->data;
}