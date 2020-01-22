#include "func.hpp"

/**
* @param[in] str string to be splitet
* @param[in] delimitter 
* @return vector
*/
std::vector<std::string> func::split(std::string str, std::string delimiter)
{ 
    std::vector<std::string> vStr;

    size_t pos=0;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        if(pos!=0)
            vStr.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    vStr.push_back(str);

    return vStr;
}

/**
* @param[in, out] str string to be modified
*/
void func::convertToLower(std::string &str)
{
    std::locale loc1("de_DE.UTF8");
    for(unsigned int i=0; i<str.length(); i++)
        str[i] = tolower(str[i], loc1);
}
