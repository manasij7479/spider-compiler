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
}
#endif