#ifndef CDOPTION_H
#define CDOPTION_H

#include <iostream>
#include <string>
#include <map>

class CDOption
{ 
private:
    std::string m_sID;
    std::string m_sText;
    std::string m_sTarget;
    bool m_active;

public:
    CDOption(std::string sID, std::string sText, std::string sTarget, bool active);

    // *** GETTER *** //
    std::string getText();
};
    
#endif
