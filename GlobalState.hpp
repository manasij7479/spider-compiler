#ifndef GLOBAL_STATE_HPP
#define GLOBAL_STATE_HPP
#include <vector>
#include "TokenTypes.hpp"

namespace spc
{
    extern std::vector<Token*> Tokens;
    inline void insertToken(Token* t)
    {
        Tokens.push_back(t);
    }
    inline Token* getToken(int index)
    {
        return Tokens[index];
    }
    
//When possible, make flex generate C++ code, making this unnecessary
//That feature is still experimental and does not properly support multiple scanners yet.
}
#endif