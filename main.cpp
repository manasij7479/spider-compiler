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
    spc::Tokens.push_back(new spc::EOFToken);
    auto p = spc::parseExpr(0);
    if (!p)
        std::cerr << p.getError() <<std::endl;
    else
        std::cout << "Parsed" << std::endl;
//             static_cast<spc::StringLiteralExpr*>(p.get())->s->data;
}