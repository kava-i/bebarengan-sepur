#ifndef CDSTATE_H
#define CDSTATE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "CDOption.hpp"

class CDState
{ 
private:
    std::string m_sID;
    std::string m_sText;
    std::string m_sFunction;
    
    std::vector<std::string> m_alternativeTexts;

    //Map of options 
    typedef std::map<int, CDOption*> dialogoptions;
    dialogoptions m_options;

    //Referenc to the complete dialog
    typedef std::map<std::string, CDState*> dialog;
    dialog* m_dialog;

    //Static map of all state-functions
    static std::map<std::string, std::string (CDState::*)()> m_functions;

public:
    CDState(std::string sID, std::string sText, std::string function, std::vector<std::string> alternativeTexts, dialogoptions states, dialog* dia);

    // *** GETTER *** //
    std::string getText();
    dialogoptions& getOptions();

    // *** SETTER *** //
    void setText(size_t text);

    static void initializeFunctions();
    std::string callState();

    // *** functions *** //
    std::string standard();
    std::string parsen1();

    void changeStateText(std::string sStateID, size_t text);
    void addDialogOption(std::string sStateID, size_t optID);
    void deleteDialogOption(std::string sStateID, size_t optID);


    size_t numOptions();
};
    
#endif
