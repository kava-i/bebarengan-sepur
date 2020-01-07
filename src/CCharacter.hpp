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

    //Dialog
    typedef std::map<std::string, CDState*> dialog;
    dialog m_dialog;

public:
    CCharacter(std::string sName, dialog newDialog);

    // *** GETTER *** // 
    std::string getName();
    dialog getDialog();

    // *** SETTER *** //
    void setDialog(dialog newDialog);

};
    
#endif
