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
    size_t m_strength;

    typedef std::map<string, string> objectmap;
    objectmap m_attacks;

    //Dialog
    SDialog* m_dialog;

public:

    // *** GETTER *** // 
    string getName();
    int getHp();
    size_t getStrength();
    SDialog* getDialog();
    std::map<string, string> getAttacks();

    // *** SETTER *** //
    void setDialog(SDialog* newDialog);
};

#endif

        
