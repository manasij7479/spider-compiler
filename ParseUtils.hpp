#ifndef PARSE_UTILS_HPP
#define PARSE_UTILS_HPP
#include <functional>
#include "ParseResult.hpp"
#include "GlobalState.hpp"
namespace spc
{
    typedef std::function<ParseResult(int)> ParserFunction;
    ParserFunction LinearChoice(std::vector<ParserFunction> functions)
    {
        return [&](int index) -> ParseResult
        {
            return ParseResult("NOT_IMPLEMENTED");
        };
    }
}
#endif