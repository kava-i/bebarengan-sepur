#ifndef CPERSON_H
#define CPERSON_H

#include <iostream>
#include <map>
#include "CDialog.hpp"

using std::string;

class CPerson
{
protected:
    string m_sName;
    string m_sID;

    //Stats
    int m_hp;
    size_t strength;

    //Dialog
    SDialog* m_dialog;

public:

    // *** GETTER *** // 
    string getName();
    int getHp();
    size_t getStrength();
    SDialog* getDialog();

    // *** SETTER *** //
    void setDialog(SDialog* newDialog);
}

        
