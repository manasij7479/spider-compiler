#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP
#include "TokenTypes.hpp"
#include <iostream>
#include <stdexcept>

void scanInt(std::string str, int line)
{
    std::cout << "INT: " << str <<std::endl;
}
void scanString(std::string str, int line)
{
    std::cout << "STR: " << str <<std::endl;
}
void scanSpecial(std::string str, int line)
{
    std::cout << "SPC: " << str <<std::endl;
}
void scanIdentifier(std::string str, int line)
{
    std::cout << "IDF: " << str <<std::endl;
}
void scanPunctuation(std::string str, int line)
{
    std::cout << "PUN " << str << std::endl;
}

void scanKeyWord(std::string str, int line)
{
    std::cout << "KEY: " << str <<std::endl;
}
void reportUnexpected(std::string str, int line)
{
    throw std::runtime_error("Unexpected '"+str+"' in input.");
}

#endif