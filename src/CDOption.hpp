#ifndef CDOPTION_H
#define CDOPTION_H

#include <iostream>
#include <string>
#include <map>

class CDOption
{ 
private:
    std::string m_sText;
    std::string m_sTarget;

public:
    CDOption(std::string sText, std::string sTarget);

    // *** GETTER *** //
    std::string getText();
    std::string getTargetState();
};
    
#endif
