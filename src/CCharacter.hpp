#ifndef CCHARACTER_H
#define CCHARACTER_H

#include <iostream>
#include <string>
#include <map>
#include "CDState.hpp"

class CCharacter
{ 
private:
    std::string m_sName;
    std::string m_sDescription;

    //Dialog
    typedef std::map<std::string, CDState*> dialog;
    dialog* m_dialog;

public:
    CCharacter(std::string sName, std::string sDescription, dialog* newDialog);

    // *** GETTER *** // 
    std::string getName();
    std::string getDescription();
    dialog* getDialog();

    // *** SETTER *** //
    void setDialog(dialog* newDialog);

};
    
#endif
