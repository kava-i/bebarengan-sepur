#ifndef CDSTATE_H
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
    std::string m_sFunction;

    typedef std::map<int, CDOption*> dialogoptions;
    typedef std::map<std::string, CDState*> dialog;
    dialogoptions m_options;
    dialog* m_dialog;

    static std::map<std::string, std::string (CDState::*)()> m_functions;

public:
    CDState(std::string sID, std::string sText, std::string function, dialogoptions states, dialog* dia);

    // *** GETTER *** //
    std::string getText();
    dialogoptions& getOptions();

    static void initializeFunctions();
    std::string callState();

    // *** functions *** //
    std::string standard();
    std::string parsen1();

    void addDialogOption(std::string sStateID, size_t optID);
    void deleteDialogOption(std::string sStateID, size_t optID);


    size_t numOptions();
};
    
#endif
