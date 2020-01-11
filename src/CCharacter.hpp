#ifndef CCHARACTER_H
#define CCHARACTER_H

#include <iostream>
#include <string>
#include <map>
#include "CPerson.hpp"
#include "CDialog.hpp"

using std::string;
using std::map;

class CCharacter : public CPerson
{ 
private:
    string m_sDescription;

public:
    CCharacter(string sName, string sDescription, SDialog* newDialog, objectmap attacks);

    // *** GETTER *** // 
    string getDescription();

};
    
#endif
