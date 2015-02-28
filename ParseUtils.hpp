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
            std::vector<ASTNode*> data;
            while(true)
            {
                auto result = f(index);
                if (result == false)
                    break;
                else
                {
                    index = result.nextIndex();
                    data.push_back(result.get());
                }
//                 std::cerr << "STAR\n";
            }
            return ParseResult(new ASTNodeVector(data), index);
        };
    }
    
    ParserFunction Sequence(const std::vector<ParserFunction>& functions)
    {
        return [=](int index) -> ParseResult
        {
            
            std::vector<ASTNode*> data;
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
                    data.push_back(result.get());
                }
//                 std::cerr << "SEQ\n";
            }
            return ParseResult(new ASTNodeVector(data), index);
        };
    }
    template<typename ResultType>
    // ResultType must derive from ASTNode
    ParserFunction hook(ParserFunction f, ResultType*& result)
    {
        return [&](int index) -> ParseResult
        {
            auto temp = f(index);
            if(!temp)
            {
                result = nullptr;
                return temp;
            }
            result = static_cast<ResultType*>(temp.get());
//             result->dump(0, std::cerr);
            return temp;
        };
    }
    //TODO: hook with a function argument
    //FIXME: hook segfaults in ZeroOrMore in ParseExprList

}
#endif