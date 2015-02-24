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
    auto p = spc::parseIntLiteralExpr(0);
    if (!p)
        std::cerr << p.getError() <<std::endl;
    else
        std::cout << "Parsed:" << 
            static_cast<spc::IntLiteralExpr*>(p.get())->i->data;
}