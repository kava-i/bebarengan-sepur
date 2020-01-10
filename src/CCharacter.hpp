#ifndef CCHARACTER_H
#define CCHARACTER_H

#include <iostream>
#include <string>
#include <map>
#include "CDialog.hpp"

using std::string;

class CCharacter
{ 
private:
    string m_sName;
    string m_sDescription;

    //Dialog
    SDialog* m_dialog;

public:
    CCharacter(string sName, string sDescription, SDialog* newDialog);

    // *** GETTER *** // 
    string getName();
    string getDescription();
    SDialog* getDialog();

    // *** SETTER *** //
    void setDialog(SDialog* newDialog);

};
    
#endif
