#include <iostream>
#include <stdexcept>
void scanInt(std::string str)
{
    std::cout << "INT: " << str <<std::endl;
}
void scanString(std::string str)
{
    std::cout << "STR: " << str <<std::endl;
}
void scanSpecial(std::string str)
{
    std::cout << "SPC: " << str <<std::endl;
}
void scanIdentifier(std::string str)
{
    std::cout << "IDF: " << str <<std::endl;
}
void scanOpenParen()
{
    std::cout << "OPENPAREN\n";
}
void scanCloseParen()
{
    std::cout << "CLOSEPAREN\n";
}

void scanOpenBrace()
{
    std::cout << "OPENBRACE\n";
}
void scanCloseBrace()
{
    std::cout << "CLOSEBRACE\n";
}

void scanKeyWord(std::string str)
{
    std::cout << "KEY: " << str <<std::endl;
}
void reportUnexpected(std::string str)
{
    throw std::runtime_error("Unexpected '"+str+"' in input.");
}