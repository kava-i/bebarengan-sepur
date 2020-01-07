#ifndef CDOPTION_H
#define CDOPTION_H

#include <iostream>
#include <string>
#include <map>

class CDOption
{ 
private:
    size_t m_ID;
    std::string m_sText;
    std::string m_sTarget;
    bool m_active;

public:
    CDOption(size_t sID, std::string sText, std::string sTarget, bool active);

    // *** GETTER *** //
    std::string getText();
    std::string getTargetState();
};
    
#endif
