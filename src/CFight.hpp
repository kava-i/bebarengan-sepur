#ifndef CFIGHT_H
#define CFIGHT_H

#include <iostream>
#include <map>
#include "CPerson.hpp"
#include "CAttack.hpp"

using std::string;

class CFight
{
protected:
    string m_sName;
    string m_sDescription;

    CPerson* m_player;
    CPerson* m_opponent;

public:

    CFight(string sName, string sDescription, CPerson* player, CPerson* opponent);

    typedef std::pair<string, string> event;
    void initializeFight();
    event fightRound(string sPlayerChoice);
    string turn(string selectedAttack, CPerson* attacker, CPerson* defender);
    string createFightingAgainst();
};

#endif

 
