#ifndef CDSTATE_Hf
#define CDSTATE_H

#include <iostream>
#include <string>
#include <map>
#include "CDOption.hpp"

class CDState
{ 
private:
    std::string m_sID;
    std::string m_sText;

    std::map<size_t, CDOption*> m_options;

public:
    CDState(std::string sID, std::string sText, std::map<size_t, CDOption*> states);

    // *** GETTER *** //
    std::string getText();
    std::map<size_t, CDOption*> getOptions();
};
    
#endif
