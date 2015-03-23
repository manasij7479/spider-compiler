#ifndef SPC_TYPES_HPP
#define SPC_TYPES_HPP
#include <vector>
namespace spc
{
    class Type
    {
    public:
        Type(){/*not valid*/}
        Type(std::string t):isfunc(false), name(t){}
        Type(std::vector<std::string> args): isfunc(true), argtypes(args){}
        bool isFunction(){return isfunc;}
        std::string getType(){return name;}
        std::vector<std::string> getArgTypes(){return argtypes;}
        bool isCompatible(std::string s)
        {
            if (isfunc)
                return false;
            if (name == "any")
                return true;
            else return s == name;
        }
        bool isCompatible(std::vector<std::string> vs)
        {
            if (!isfunc)
                return false;
            if (vs.size() != argtypes.size())
                return false;
            for (uint i = 0 ; i < argtypes.size(); ++i)
                if (argtypes[i] != vs[i] && argtypes[i] != "any")
                    return false;
            return true;
        }
    private:
        bool isfunc;
        std::string name;
        std::vector<std::string> argtypes;
    };
}
#endif