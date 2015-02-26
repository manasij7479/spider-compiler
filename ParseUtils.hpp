#ifndef PARSE_UTILS_HPP
#define PARSE_UTILS_HPP
#include <functional>
#include "ParseResult.hpp"
#include "GlobalState.hpp"
#include <iostream>
namespace spc
{
    typedef std::function<ParseResult(int)> ParserFunction;
    ParserFunction LinearChoice(const std::vector<ParserFunction>& functions, std::string error = "Syntax Error")
    {
        return [&](int index) -> ParseResult
        {   ParseResult result(error);
            for(auto f : functions)
            {
                result = f(index);
                if (result)
                    return result;
            }
            return ParseResult(result.getError() + "\n from: " + error);
        };
    }
    
    ParserFunction ZeroOrMore(const ParserFunction& f)
    {
        return [=](int index) -> ParseResult
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
//                 std::cerr << "STAR\n";
            }
            return ParseResult(v, index);
        };
    }
    
    ParserFunction Sequence(const std::vector<ParserFunction>& functions)
    {
        return [=](int index) -> ParseResult
        {
            
            auto v = new ASTNodeVector;
            for(auto f : functions)
            {
                auto result = f(index);
                if (!result)
                {
                    return result;
                }
                else
                {
                    index = result.nextIndex();
                    v->data.push_back(result.get());
                }
//                 std::cerr << "SEQ\n";
            }
            return ParseResult(v, index);
        };
    }
}
#endif