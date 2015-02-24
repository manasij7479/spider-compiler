#ifndef PARSE_UTILS_HPP
#define PARSE_UTILS_HPP
#include <functional>
#include "ParseResult.hpp"
#include "GlobalState.hpp"
#include <iostream>
namespace spc
{
    typedef std::function<ParseResult(int)> ParserFunction;
    ParserFunction LinearChoice(std::vector<ParserFunction> functions, std::string error = "Syntax Error")
    {
        return [&](int index) -> ParseResult
        {            
            for(auto f : functions)
            {
                auto result = f(index);
                if (result)
                    return result;
            }
            return ParseResult(error);
        };
    }
    
    ParserFunction ZeroOrMore(ParserFunction f)
    {
        return [&](int index) -> ParseResult
        {
            auto v = new ASTNodeVector;
            while(true)
            {
                auto result = f(index);
                if (result == false)
                    break;
                else
                {
                    index = result.nextIndex();
                    v->data.push_back(result.get());
                }
            }
            return ParseResult(v, index);
        };
    }
    
}
#endif