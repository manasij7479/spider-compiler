#ifndef PARSE_RESULT_HPP
#define PARSE_RESULT_HPP
#include "AST.hpp"
namespace spc
{
    class ParseResult
    {
    public:
        ParseResult(std::string s)
            :success(false),
             result(nullptr),
             error(s),index(-1){}
        ParseResult(ASTNode* node, int i)
        {
            success = true;
            result = node;
            index = i;
        }
        
        operator bool()
        {
            return success;
        }
        ASTNode* get()
        {
            return result;
        }
        std::string getError()
        {
            return error;
        }
        int nextIndex()
        {
            return index;
        }
    private:
        bool success;
        ASTNode* result;
        std::string error;
        int index;
    };
}
#endif